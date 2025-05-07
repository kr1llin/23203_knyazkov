package nsu.game;

import nsu.graphics.SpriteLibrary;
import nsu.input.Input;
import nsu.controller.UserController;
import nsu.display.Display;
import nsu.entity.GameObject;
import nsu.game.state.*;
import nsu.entity.Player;
import nsu.obj_core.Size;

import java.awt.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Game {
    private final Display display;
    private Input input;
    private GameStateManager stateManager;

    private int width;
    private int height;

    public Game(int width, int height) throws IOException, FontFormatException {
        this.width = width;
        this.height = height;
        input = new Input();
        display = new Display(width, height, input);
        stateManager = new GameStateManager();
        stateManager.changeState(new LevelState(stateManager, display, input));
    }

    public void update() throws IOException {
        stateManager.update();
    }

    public void render(){
        display.render(stateManager.getCurrentState());
    }

}
