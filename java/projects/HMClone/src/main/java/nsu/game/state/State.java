package nsu.game.state;

import nsu.display.Camera;
import nsu.display.Display;
import nsu.entity.GameObject;
import nsu.entity.MovingEntity;
import nsu.entity.Player;
import nsu.obj_core.*;
import nsu.input.Input;

import java.awt.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public abstract class State {
    protected GameStateManager stateManager;
    protected Display display;
    protected Input input;
    protected StateName name;


    public State(GameStateManager stateManager, Display display, Input input) {
        this.stateManager = stateManager;
        this.display = display;
        this.input = input;
    }

    public abstract void update();
    public abstract void handleInput() throws IOException;
    public abstract void enter();
    public abstract void exit();
    public StateName getName() {
        return name;
    }
}
