package nsu.controller;

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
}
