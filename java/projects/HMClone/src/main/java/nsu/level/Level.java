package nsu.level;

import nsu.game.Game;
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

    public double getHeight() {
        return tiles[0].length * Game.SPRITE_SIZE;
    }

    public double getWidth(){
        return tiles.length * Game.SPRITE_SIZE;
    }
}
