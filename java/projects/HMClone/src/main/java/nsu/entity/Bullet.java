package nsu.entity;

import nsu.display.Camera;
import nsu.game.Game;
import nsu.game.state.State;
import nsu.obj_core.Position;
import nsu.obj_core.Size;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.IOException;

public class Bullet extends MovingEntity{
    int BULLET_WIDTH =  25;
    int BULLET_HEIGHT = 25;
    int BULLET_SPEED = 5;

    public Bullet(Position position) {
        super(position, 5);
        size = new Size(BULLET_WIDTH, BULLET_HEIGHT);
    }

    @Override
    public void update() {
        // bullet takes in constructor player position
        // normilizes direction (unit vector by mouse position)
        super.update();
    }

    @Override
    public Image getSprite() {
        BufferedImage image = new BufferedImage(BULLET_WIDTH, BULLET_HEIGHT, BufferedImage.TYPE_INT_RGB);
        Graphics2D graphics = image.createGraphics();

        graphics.setColor(Color.ORANGE);
        graphics.fillRect(0,0, BULLET_WIDTH, BULLET_HEIGHT);
        graphics.dispose();
        return image;
    }
}
