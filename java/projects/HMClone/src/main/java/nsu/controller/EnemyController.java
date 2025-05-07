package nsu.controller;

import nsu.ai.states.AiState;
import nsu.obj_core.Position;

public class EnemyController implements Controller{
    private AiState state;

    @Override
    public boolean isRequestingUp() {
        return false;
    }

    @Override
    public boolean isRequestingDown() {
        return false;
    }

    @Override
    public boolean isRequestingLeft() {
        return false;
    }

    @Override
    public boolean isRequestingRight() {
        return false;
    }

    @Override
    public boolean isShooting() {
        return false;
    }

    @Override
    public boolean cursorMoved() {
        return false;
    }

    @Override
    public Position getMousePosition() {
        return null;
    }

    @Override
    public boolean isRequestingOne() {
        return false;
    }

    @Override
    public boolean isRequestingTwo() {
        return false;
    }

    @Override
    public boolean isRequestingShift() {
        return false;
    }
}
