package nsu.game.state;

import nsu.controller.UserController;
import nsu.entity.Player;
import nsu.input.Input;
import nsu.level.Level;
import nsu.obj_core.Size;

public class LevelState extends State{
    public LevelState(Input input) {
        super(input);
        gameObjects.add(new Player(new UserController(input), spriteLibrary));
        stateLevel = new Level(new Size(30, 30), spriteLibrary); // should match the size of GAME_WORLD

    }
}
