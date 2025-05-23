package nsu.controller;

import nsu.obj_core.Position;

/**
 *
 * Answers to user input
 *
 */
public interface Controller {
    boolean isRequestingUp();
    boolean isRequestingDown();
    boolean isRequestingLeft();
    boolean isRequestingRight();
    boolean isShooting();
    boolean cursorMoved();
    Position getMousePosition();

    boolean isRequestingOne();
    boolean isRequestingTwo();
    boolean isRequestingShift();
}
