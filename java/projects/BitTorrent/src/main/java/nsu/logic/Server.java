package nsu.logic;

import java.io.IOException;
import java.nio.channels.Selector;

public class Server implements Runnable{

    public Server(PeerData peerData){
        this.peerData = peerData;
        // get peers from file??
    }

    public void start(){
        try{
            selector = Selector.open();

        }
        catch (IOException e){
            return;
        }
    }

    @Override
    public void run() {
        start();
    }

    PeerData peerData;
    Selector selector;
}
