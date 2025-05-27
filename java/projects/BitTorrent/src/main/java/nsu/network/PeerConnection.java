package nsu.network;

import nsu.logic.Engine;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Arrays;
import java.util.UUID;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

// handshake BEP-3
// bitfields exchange
// piece requests
public class PeerConnection {
    private enum State {HANDSHAKE_SENT, HANDSHAKE_RECEIVED, ACTIVE, CLOSED}

    final String peerId;

    private boolean choked = true;
    private boolean handshakeIsDone = false;
    private boolean isInitiator;

    private SocketChannel channel;
    private byte[] infoHash; // expected info hash
    private Engine engine;
    private final BlockingQueue<ByteBuffer> writeQueue = new LinkedBlockingQueue<>();
//    private final ExecutorService writeExecutor = Executors.newSingleThreadExecutor();

    private State state = State.HANDSHAKE_SENT;

    public PeerConnection(SocketChannel channel, Engine engine, boolean isInitiator) {
        this.channel = channel;
        this.engine = engine;
        this.isInitiator = isInitiator;
        peerId = generatePeerId();
        infoHash = engine.getMeta().getInfoHash();
    }

    private String generatePeerId() {
        return UUID.randomUUID().toString().substring(0, 5);
    }

    public void startHandshake() throws IOException {
        if (isInitiator) {
            sendHandshake();
//            engine.getServer().registerForWrite(this);
        }
    }

    // write handshake to channel
    private void sendHandshake() throws IOException {

        ByteBuffer buffer = ByteBuffer.allocate(68);
        buffer.put((byte) 19); //pstrlen
        buffer.put("BitTorrent protocol".getBytes()); // pstr
        buffer.put(new byte[8]); // reserved
        buffer.put(infoHash); // 20-byte SHA1 of the info key in the metainfo file
        buffer.put(peerId.getBytes()); // unique ID for the client
        buffer.flip();
        writeQueue.add(buffer);
//        channel.write(buffer);
        state = State.HANDSHAKE_SENT;
    }

    public void processIncommingData(ByteBuffer buffer) throws IOException {
        if (state == State.CLOSED) return;

        if (!isHandshakeIsDone()) {
            handleHandshakePhase(buffer);

        } else { // if State.ACTIVE
            processMessages(buffer);
        }
    }

    private void handleHandshakePhase(ByteBuffer buffer) throws IOException {
        if (isInitiator) {
            validateHandshake(buffer);
        } else {
            validateHandshake(buffer);
            if (state == State.HANDSHAKE_RECEIVED) {
                sendHandshake();
//                state = State.ACTIVE;
            }
        }
    }

    private void validateHandshake(ByteBuffer buffer) throws IOException {
        // (49+len(pstr)) bytes long
        if (buffer.remaining() < 68) return;

        byte pstrlen = buffer.get();

        if (pstrlen != 19) {
            disconnect();
            return;
        }

        byte[] pstr = new byte[19];
        buffer.get(pstr);

        if (!"BitTorrent protocol".equals(new String(pstr))) {
            disconnect();
            return;
        }

        buffer.position(28);
        byte[] receivedHash = new byte[20];
        if (!Arrays.equals(receivedHash, infoHash)) {
            disconnect();
            return;
        }

        state = isInitiator ? State.ACTIVE : State.HANDSHAKE_RECEIVED;
        engine.onHandshakeComplete(this);
    }

    public void processMessages(ByteBuffer buffer) {
        buffer.position(68);
        ByteBuffer remaining = buffer.slice();
        processProtocolMessages(remaining);
    }

    // BEP-3 message (handleChoke, handleUnchoke, Interested, NotInterested, etc.)
    private void processProtocolMessages(ByteBuffer buffer) {
        while (buffer.remaining() >= 4) {
            int length = buffer.getInt();
            if (length == 0) continue;

            if (buffer.remaining() < length - 1) {
                buffer.rewind();
                return;
            }

            byte messageId = buffer.get();
            handleMessage(messageId, buffer.slice().limit(length - 1));
            buffer.position(buffer.position() + length - 1);
        }
    }

    private void handleMessage(byte messageId, ByteBuffer payload) {
        switch (messageId) {
            case 0:
                handleChoke();
                break;
            case 1:
                handleUnchoke();
                break;
            case 4:
                handleHave(payload.getInt());
                break;
            case 7:
                handlePiece(payload);
                break;
        }
    }

    public void writeAvailable() throws IOException {
        try {
            while (!writeQueue.isEmpty()) {
                ByteBuffer buffer = writeQueue.peek();
                channel.write(buffer);
                writeQueue.poll();
            }
            engine.getServer().unregisterWrite(this);
        } catch (IOException e) {
            disconnect();
        }
    }

    public void requestPiece(int index, int offset, int length) {
        ByteBuffer request = ByteBuffer.allocate(17);
        request.putInt(13);
        request.put((byte) 6);
        request.putInt(index);
        request.putInt(offset);
        request.putInt(length);
        request.flip();
        writeQueue.add(request);
        engine.getServer().registerForWrite(this);
    }

    private void handleChoke() {
        choked = true;
    }

    private void handleUnchoke() {
        choked = false;
        engine.schedulePieceRequests(this);
    }

    private void handleHave(int pieceIndex) {
        engine.updatePieceAvailability(pieceIndex, this);
    }

    private void handlePiece(ByteBuffer payload) {
        int index = payload.getInt();
        int offset = payload.getInt();
        byte[] block = new byte[payload.remaining()];
        payload.get(block);
        engine.savePieceData(index, offset, block);
    }

    public void disconnect() throws IOException {
        state = State.CLOSED;
        try {
            channel.close();
        } catch (IOException ignorr) {
        }
        engine.removeConnection(this);
    }

    public boolean isChoked() {
        return choked;
    }

    public boolean isHandshakeIsDone() {
        return handshakeIsDone;
    }

    public SocketChannel getChannel() {
        return channel;
    }

    public boolean isInitiator() {
        return isInitiator;
    }

    public BlockingQueue<ByteBuffer> getWriteQueue() {
        return writeQueue;
    }
}
