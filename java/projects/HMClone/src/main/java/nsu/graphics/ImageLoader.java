package nsu.graphics;

import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.Objects;

public class ImageLoader {

    public static Image loadImage(String filePath) {
        try {
//            return ImageIO.read(new File(filePath));
            return ImageIO.read(Objects.requireNonNull(ImageLoader.class.getResource(filePath)));
        }
        catch (IOException e) {
            System.out.println("Couldn't load image from path " + filePath);
        }
        return null;
    }
}
