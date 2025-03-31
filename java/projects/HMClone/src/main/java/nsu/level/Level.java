package nsu.level;

import nsu.graphics.SpriteLibrary;
import nsu.obj_core.*;

import java.util.Arrays;

public class Level {
    private Tile[][] tiles;

    public Level(Size size, SpriteLibrary spriteLibrary) {
        tiles = new Tile[size.getWidth()][size.getHeight()];
        initializeTiles(spriteLibrary);
    }

    private void initializeTiles(SpriteLibrary spriteLibrary){
        for (Tile[] row : tiles) {
            Arrays.fill(row, new Tile(spriteLibrary));
        }
    }

    public Tile[][] getTiles() {
        return tiles;
    }
}
