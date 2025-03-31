package nsu.display;

import nsu.game.Game;
import nsu.game.state.*;
import nsu.level.Tile;

import java.awt.*;
import java.io.IOException;

public class RenderModule {
    public void render(State state, Graphics graphics) {
        state.getGameObjects().forEach(gameObject -> {
            try {
                renderLevel(state, graphics);
                graphics.drawImage(
                        gameObject.getSprite(),
                        gameObject.getPosition().intX(),
                        gameObject.getPosition().intY(),
                        null
                );
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
    }

    private void renderLevel(State state, Graphics graphics) {
        Tile[][] tiles = state.getLevel().getTiles();

        for (int x = 0; x < tiles.length; x++){
            for (int y = 0; y < tiles[0].length; y++){
                graphics.drawImage(
                        tiles[x][y].getSprite(),
                        x * Game.SPRITE_SIZE,
                        y * Game.SPRITE_SIZE,
                        null
                );
            }
        }
    }
}
