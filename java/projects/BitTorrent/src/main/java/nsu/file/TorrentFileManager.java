package nsu.file;

public class TorrentFileManager {
    private long total = 1;
    private long left = 1; // total length of the file
    // Check for existing pieces
    // write new pieces

    public TorrentFileManager(){

    }

    public int getProgress(){
        return 100 - (int)(left / total)*100;
    }
}
