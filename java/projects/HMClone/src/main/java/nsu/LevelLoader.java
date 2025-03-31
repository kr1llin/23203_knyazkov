//package nsu;
//
//import java.io.IOException;
//import java.nio.file.Files;
//import java.nio.file.Paths;
//
//public class LevelLoader {
//    public static String[] loadLevel(String filename) {
//        try {
//            return Files.readAllLines(Paths.get(filename)).toArray(String[]::new);
//        } catch (IOException e) {
//            System.err.println("Error loading level: " + filename);
//            throw new RuntimeException(e);
//        }
//    }
//}
