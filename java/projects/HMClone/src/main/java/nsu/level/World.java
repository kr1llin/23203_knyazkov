package nsu.level;

import nsu.game.Game;
import nsu.graphics.SpriteLibrary;
import nsu.obj_core.*;

import java.util.Arrays;

public class World {
    private Tile[][] tiles;

    public World(Size size) {
        tiles = new Tile[(int)size.getWidth()][(int)size.getHeight()];
        initializeTiles();
    }

    private void initializeTiles(){
        for (Tile[] row : tiles) {
            Arrays.fill(row, new Tile());
        }
    }

    public Tile[][] getTiles() {
        return tiles;
    }

    public double getHeight() {
        return tiles[0].length * SpriteLibrary.getSpriteSize();
    }

    public double getWidth(){
        return tiles.length * SpriteLibrary.getSpriteSize();
    }
}
