package nsu.display;

import nsu.entity.GameObject;
import nsu.game.Game;
import nsu.game.state.*;
import nsu.level.Tile;
import nsu.obj_core.Position;
import nsu.obj_core.Size;
import org.jetbrains.annotations.NotNull;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.io.IOException;

public class RenderModule {
    public void render(State state, Graphics graphics) {
        Graphics2D g2d = (Graphics2D) graphics;
        AffineTransform originalTransform = g2d.getTransform();

        // ADD TRANSFORMATION METHOD TO OBJECTS (every object has it's own transformations)
        state.getGameObjects().forEach(gameObject -> {
            try {
                renderLevel(state, graphics);
                AffineTransform transform = getAffineTransform(state, gameObject);
                g2d.setTransform(transform);
                g2d.drawImage(gameObject.getSprite(), 0, 0, null);
                g2d.setTransform(originalTransform);

//                graphics.drawImage(
//                        gameObject.getSprite(),
//                        gameObject.getPosition().intX() - camera.getPosition().intX() - gameObject.getSize().getWidth() / 2,
//                        gameObject.getPosition().intY() - camera.getPosition().intY() -  gameObject.getSize().getHeight() / 2,
//                        null
//                );
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
    }

    @NotNull
    private static AffineTransform getAffineTransform(State state, GameObject gameObject) {
        Camera camera = state.getCamera();

        double screenX = gameObject.getPosition().getX() - camera.getPosition().getX();
        double screenY = gameObject.getPosition().getY() - camera.getPosition().getY();

        int height = gameObject.getSize().getHeight();
        int width = gameObject.getSize().getWidth();

        AffineTransform transform = new AffineTransform();
        transform.translate(screenX, screenY);
        transform.rotate(Math.toRadians(gameObject.getRotation().getRotationAngle()) + Math.PI / 2); // sprite looks up (we assume that all sprites are faced up)
        transform.translate(-width / 2.0, -height / 2.0);
        return transform;
    }

    private void renderLevel(State state, Graphics graphics) {
        Tile[][] tiles = state.getLevel().getTiles();
        Camera camera = state.getCamera();
        for (int x = 0; x < tiles.length; x++) {
            for (int y = 0; y < tiles[0].length; y++) {
                graphics.drawImage(
                        tiles[x][y].getSprite(),
                        x * Game.SPRITE_SIZE - camera.getPosition().intX(),
                        y * Game.SPRITE_SIZE - camera.getPosition().intY(),
                        null
                );
            }
        }
    }
}
