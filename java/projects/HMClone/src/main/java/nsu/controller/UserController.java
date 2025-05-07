package nsu.controller;

import nsu.input.Input;
import nsu.obj_core.Position;

import java.awt.event.KeyEvent;

public class UserController implements Controller {

    private final Input input;

    public UserController(Input input){
        this.input = input;
    }

    @Override
    public boolean isRequestingUp() {
        return input.isPressed(KeyEvent.VK_UP);
    }

    @Override
    public boolean isRequestingDown() {
        return input.isPressed(KeyEvent.VK_DOWN);
    }

    public boolean isRequestingOne() {return input.isPressed(KeyEvent.VK_1);}
    public boolean isRequestingTwo() {return input.isPressed(KeyEvent.VK_2);}

    @Override
    public boolean isRequestingShift() {
        return input.isPressed(KeyEvent.VK_BACK_SPACE);
    }

    @Override
    public boolean isRequestingLeft() {
        return input.isPressed(KeyEvent.VK_LEFT);
    }

    @Override
    public boolean isRequestingRight() {
        return input.isPressed(KeyEvent.VK_RIGHT);
    }



    @Override
    public boolean cursorMoved() {
        return input.isMouseMoved();
    }

    @Override
    public Position getMousePosition() {
        return input.getMousePosition() == null ? new Position(0,0) : input.getMousePosition();
    }

    @Override
    public boolean isShooting(){
        return input.isMouseClicked();
    }

}
