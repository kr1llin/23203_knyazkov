package nsu.logic;

public class PeerData {
    public int port;

    public synchronized int getProgress(){
        //return downloadedPieces / totalPieces * 100
        return 0;
    }
}
