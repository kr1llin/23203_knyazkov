package nsu.game;

import nsu.graphics.SpriteLibrary;
import nsu.input.Input;
import nsu.controller.UserController;
import nsu.display.Display;
import nsu.entity.GameObject;
import nsu.game.state.*;
import nsu.entity.Player;
import nsu.obj_core.Size;

import java.util.ArrayList;
import java.util.List;

public class Game {
    public static int SPRITE_SIZE = 64;

    private final Display display;
    private Input input;
    private State state;

    public Game(int width, int height){
        input = new Input();
        display = new Display(width, height, input);
        state = new LevelState(new Size(width, height), input);
    }

    public void update(){
        state.update();
    }

    public void render(){
        display.render(state);
    }

}
