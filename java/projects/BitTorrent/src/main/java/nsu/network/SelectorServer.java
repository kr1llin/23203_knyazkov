package nsu.network;

import nsu.logic.Engine;
import nsu.torrent.TorrentMeta;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class SelectorServer extends Thread {
    // NIO Selector for incoming connections
    // process handshakes (BEP-3) and basic messages

    private static final int BUFFER_SIZE = 5 * 1024;

    private final int port;
    private final InetAddress address;
    ServerSocketChannel serverChannel;
    private final Selector selector;
    private final Map<SocketChannel, PeerConnection> peers = new ConcurrentHashMap<SocketChannel, PeerConnection>();
    private final Engine engine;

    public SelectorServer(String hostname, int port, Engine engine) throws IOException {
        this.port = port;
        this.selector = Selector.open();
        this.engine = engine;
        this.address = InetAddress.getByName(hostname);
    }

    @Override
    public void run() {
        try {
            initServer();
            while (!Thread.interrupted()) {
                selector.select(500); // waiting for connection requests
                processSelectedKeys(); // process all pending connections
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // make server socket
    private void initServer() throws IOException {
        serverChannel = ServerSocketChannel.open();
        serverChannel.bind(new InetSocketAddress(address, port));
        serverChannel.configureBlocking(false);
        serverChannel.register(selector, SelectionKey.OP_ACCEPT);
    }

    // something has shot
    private void processSelectedKeys() throws IOException {
        Set<SelectionKey> selectedKeys = selector.selectedKeys();
        Iterator<SelectionKey> iterator = selectedKeys.iterator();

        while (iterator.hasNext()) {
            SelectionKey key = iterator.next(); // pointer to a channel
            iterator.remove();

            if (key.isValid()) {
                if (key.isAcceptable()) {
                    handleAccept(key);
                }
                if (key.isConnectable()){
                    handleConnect(key);
                }
                 if (key.isReadable()) {
                     handleRead(key);
                 }
                 if (key.isWritable()) {
                    handleWrite(key);
                }
            }
        }
    }

    //
    private void handleAccept(SelectionKey key) throws IOException {
        ServerSocketChannel serv = (ServerSocketChannel) key.channel();
        SocketChannel client = serv.accept(); // null if there are no pending connection
    }

    private void handleConnect(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        if (channel.finishConnect()){
            PeerConnection conn = new PeerConnection(channel, engine, false);
            conn.startHandshake();
            channel.register(selector, SelectionKey.OP_READ);
        }
    }


    private void handleRead(SelectionKey key) {
        SocketChannel channel = (SocketChannel) key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(BUFFER_SIZE);

        try {
            int read = channel.read(buffer);

            // no connection
            if (read == -1) {
                closeChannel(channel);
                return;
            }

            buffer.flip();
            PeerConnection conn = peers.get(channel);
            if (conn != null) {
                engine.processMessageAsync(peers.get(channel), buffer);
            }
        } catch (IOException e) {
            closeChannel(channel);
        }
    }

//    private void handleWrite(SelectionKey key) throws IOException {
//        PeerConnection conn = peers.get((SocketChannel) key.channel());
//        if (conn != null) {
//            conn.writeAvailable();
//        }
//    }

    private void handleWrite(SelectionKey key) throws IOException {
        PeerConnection conn = (PeerConnection) key.attachment();
        SocketChannel channel = (SocketChannel) key.channel();

        synchronized (conn.getWriteQueue()) {
            ByteBuffer buffer = conn.getWriteQueue().peek();
            if (buffer != null) {
                channel.write(buffer);
                if (!buffer.hasRemaining()) {
                    conn.getWriteQueue().poll();
                }
            }

            if (conn.getWriteQueue().isEmpty()) {
                key.interestOps(SelectionKey.OP_READ);
            }
        }
    }

    public void connectToPeer(InetSocketAddress address) throws IOException {
        System.out.println("Trying to connect to socket " + address + " ...");
        SocketChannel channel = SocketChannel.open();
        channel.configureBlocking(false);
        channel.connect(address);

        PeerConnection connection = new PeerConnection(channel, engine, true);
        peers.put(channel, connection);

        channel.register(selector, SelectionKey.OP_CONNECT);
    }


    private void processMessage(SocketChannel channel, ByteBuffer buffer, PeerConnection connection) {
        // process messages after handshake
//            engine.updateProgress();
    }

    private void handleRequest(SocketChannel channel, ByteBuffer buffer) {
        // process piece request
    }

    private void sendPiece(SocketChannel channel, int pieceIndex, int offset, byte[] data) {
        // send piece of data
    }

    private void closeChannel(SocketChannel channel) {
        try {
            peers.remove(channel);
            if (channel.isOpen()) {
                channel.close();
            }
        } catch (IOException e) {
        }
    }

    private void closeServer() throws IOException {
        selector.close();
        if (serverChannel.isOpen()) {
            serverChannel.close();
        }
    }

    public void registerForWrite(PeerConnection connection) {
        SocketChannel channel = connection.getChannel();
        SelectionKey key = channel.keyFor(selector);
        if (key != null) {
            key.interestOps(key.interestOps() | SelectionKey.OP_WRITE); // modify available operations
        }
    }

    public void unregisterWrite(PeerConnection connection) {
        SocketChannel channel = connection.getChannel();
        SelectionKey key = channel.keyFor(selector);
        if (key != null) {
            key.interestOps(key.interestOps() & ~SelectionKey.OP_WRITE);
        }
    }
}
