package nsu.torrent;

import com.dampcake.bencode.*;
import nsu.file.TorrentFileManager;
import org.apache.commons.codec.cli.Digest;
import org.apache.commons.codec.digest.DigestUtils;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Map;

public class TorrentMeta {
    byte[] infoHash;

    Map<String, Object> info;
    long piece_length;
    long numb_of_pieces;
    String name;
    String path;
    String[] pieces; // 20-byte SHA1 hash values
    long length;

    public TorrentMeta(){
        infoHash = "ASDSADAWQASDZCXCASDW".getBytes();
    }
    public byte[] getInfoHash(){
        return infoHash;
    }

    public void parseTorrentFile(String pathToFile) throws IOException {
        Bencode bencode = new Bencode();
        File file = new File(pathToFile);
        byte[] fileContent = Files.readAllBytes(file.toPath());
        Map<String, Object> decoded = bencode.decode(fileContent, Type.DICTIONARY);

        info = (Map<String, Object>) decoded.get("info");
        infoEncode();

        piece_length = (long) info.get("piece length");
        String pieces = (String) info.get("pieces");
        numb_of_pieces = pieces.length() / 20;
        length = (long) info.get("length");
        name = (String) info.get("name");
        path = "/home/krillin/Downloads/Pool/" + name;
    }

    public void infoEncode() {
        Bencode bencode = new Bencode();
        byte[] infoEncoded = bencode.encode(info);
        infoHash = DigestUtils.sha1Hex(infoEncoded).getBytes();
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder hexString = new StringBuilder();
        for (byte b : bytes) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) {
                hexString.append('0');
            }
            hexString.append(hex);
        }
        return hexString.toString().toUpperCase();
    }
}
