package nsu.entity;

import nsu.game.Game;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;

public class Bullet extends GameObject{
    int BULLET_WIDTH =  10;
    int BULLET_HEIGHT = 5;
    int BULLET_SPEED = 40;

    @Override
    public void update() {
        // bullet takes in constructor player position
        // normilizes direction (unit vector by mouse position)

    }

    @Override
    public Image getSprite() throws IOException {
        BufferedImage image = new BufferedImage(BULLET_WIDTH, BULLET_HEIGHT, BufferedImage.TYPE_INT_RGB);
        Graphics2D graphics = image.createGraphics();

        graphics.setColor(Color.GREEN);
        graphics.fillRect(0,0, BULLET_WIDTH, BULLET_HEIGHT);
        graphics.dispose();
        return image;
    }
}
