package nsu.game.state;

import java.io.IOException;

public class GameStateManager {
    private State currentState;

    public void changeState(State newState){
        currentState = newState;
        currentState.enter();
    }

    public void update() throws IOException {
        currentState.handleInput();
        currentState.update();
    }

    public State getCurrentState(){
        return currentState;
    }
}
