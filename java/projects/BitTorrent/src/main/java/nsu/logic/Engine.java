package nsu.logic;

import nsu.file.TorrentFileManager;
import nsu.network.PeerConnection;
import nsu.network.SelectorServer;
import nsu.torrent.TorrentMeta;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

public class Engine {
    private TorrentMeta meta;
    private SelectorServer server;
    private TorrentFileManager fileManager;

    private final ExecutorService threadPool = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
    private final List<PeerConnection> activeConnections = Collections.synchronizedList(new ArrayList<>());

    public void startServer(String hostname, int port) throws IOException {
        server = new SelectorServer(hostname, port, this);
        server.start();
    }

    public void initTorrentMeta(String torrentPath) throws IOException {
        meta = new TorrentMeta();
        meta.parseTorrentFile(torrentPath);
        fileManager = new TorrentFileManager();
    }

    // connect to peers
    public void startClient(List<String> peers) throws IOException {

        for (String peer : peers) {
            String[] parts = peer.split(":");
            InetSocketAddress address = new InetSocketAddress(
                    parts[0],
                    Integer.parseInt(parts[1])
            );
            server.connectToPeer(address);
        }
    }

//    // when we get connection - immediately send handshake
//    public void handleIncomingConnection(SocketChannel channel) throws IOException {
//        PeerConnection peer = new PeerConnection(channel,  this, true);
//        activeConnections.add(peer);
//        peer.startHandshake();
//    }

    public void onHandshakeComplete(PeerConnection connection) throws IOException {
        activeConnections.add(connection);
        System.out.println("Handshake done with: " + connection.getChannel().getRemoteAddress());

//        if (connection.isInitiator()) {
//            startDownloadProcess(connection);
//        }
    }

    private void startDownloadProcess(PeerConnection connection) {
        // exchange bitfield/interested/unchoke/et
    }

    public int getDataProgress() {
        return fileManager.getProgress();
    }

    public void shutdown() throws InterruptedException {
        if (server != null) {
            server.interrupt();
            server.join(1000);
        }

        activeConnections.forEach(connection -> {
            try {
                connection.disconnect();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        if (fileManager != null) {
//            fileManager.close();
        }
    }

    public TorrentMeta getMeta() {
        return meta;
    }

    public SelectorServer getServer() {
        return server;
    }

    public TorrentFileManager getFileManager() {
        return fileManager;
    }

    public List<PeerConnection> getActiveConnections() {
        return activeConnections;
    }

    public void processMessageAsync(PeerConnection peer, ByteBuffer buffer) {
        threadPool.submit(() -> {
            try {
                peer.processIncommingData(buffer);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
    }

    public byte[] getTorrentInfoHash() {
        return meta.getInfoHash();
    }

    public void removeConnection(PeerConnection connection) throws IOException {
        connection.getChannel().close();
        activeConnections.remove(connection);
    }

    public void savePieceData(int index, int offset, byte[] block) {
    }

    public void updatePieceAvailability(int pieceIndex, PeerConnection peerConnection) {
    }

    public void schedulePieceRequests(PeerConnection peerConnection) {

    }
}
