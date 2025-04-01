package nsu.game.state;

import nsu.controller.UserController;
import nsu.display.Camera;
import nsu.entity.GameObject;
import nsu.entity.Player;
import nsu.graphics.SpriteLibrary;
import nsu.level.Tile;
import nsu.obj_core.*;
import nsu.input.Input;
import nsu.level.Level;

import java.util.ArrayList;
import java.util.List;

public abstract class State {
    protected Level stateLevel;
    protected final List<GameObject> gameObjects;
    protected Input input;
    protected SpriteLibrary spriteLibrary;
    protected Camera camera;

    public State(Size windowSize, Input input) {
        this.input = input;
        gameObjects = new ArrayList<>();
        spriteLibrary = new SpriteLibrary();
        camera = new Camera(windowSize);
    }

    public void update(){
        gameObjects.forEach(gameObject -> {
            if (gameObject.isAlive()) {
                gameObject.update();
            }
        });
        camera.update(this);
        input.clearMouseClick();
    }


    public List<GameObject> getGameObjects() {
        return gameObjects;
    }

    public Level getLevel(){
        return stateLevel;
    }

    public Camera getCamera() {
        return camera;
    }
}
