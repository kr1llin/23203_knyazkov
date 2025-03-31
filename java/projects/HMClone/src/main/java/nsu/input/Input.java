package nsu.input;

import nsu.obj_core.Position;

import java.awt.event.*;

public class Input implements KeyListener, MouseMotionListener {

    private boolean[] keysPressed;
    private boolean mouseMoved;
    private Position mousePosition;

    public Input(){
        keysPressed = new boolean[256];
    }

    public boolean isPressed(int keyCode){
        return keysPressed[keyCode];
    }

    public boolean isMouseMoved(){
        return mouseMoved;
    }

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
        keysPressed[e.getKeyCode()] = true;
    }

    @Override
    public void keyReleased(KeyEvent e) {
        keysPressed[e.getKeyCode()] = false;
    }

    @Override
    public void mouseDragged(MouseEvent e) {

    }

    @Override
    public void mouseMoved(MouseEvent e) {
        mousePosition = new Position(e.getX(), e.getY());
        mouseMoved = true;
    }

    public Position getMousePosition() {
        return mousePosition;
    }
}
