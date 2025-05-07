package nsu.game.state;

import javafx.scene.input.KeyCode;
import nsu.display.Display;
import nsu.input.Input;

import java.awt.event.KeyEvent;
import java.io.IOException;

public class GameOverState extends State {

    public GameOverState(GameStateManager stateManager, Display display, Input input) {
        super(stateManager, display, input);
        name = StateName.ST_GAMEOVER;
    }

    @Override
    public void update() {

    }

    @Override
    public void handleInput() throws IOException {
        if (input.isPressed(KeyEvent.VK_BACK_SPACE)) {
            stateManager.changeState(new LevelState(stateManager, display, input));
        }
    }

    @Override
    public void enter() {

    }

    @Override
    public void exit() {

    }
}
