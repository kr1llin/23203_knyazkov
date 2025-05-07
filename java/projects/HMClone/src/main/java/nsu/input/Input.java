package nsu.input;

import nsu.obj_core.Position;

import java.awt.event.*;

public class Input implements KeyListener, MouseListener, MouseMotionListener {
    private Position pointerPosition;
    private boolean mouseClicked;
    private boolean mousePressed;

    private boolean[] keysPressed;
    private boolean mouseMoved;
    private Position mousePosition;

    public Input(){
        keysPressed = new boolean[256];
        pointerPosition = new Position(0,0);
    }

    public void clearMouseClick(){
        mouseMoved = false;
        mouseClicked = false;
    }

    public boolean isPressed(int keyCode){
        return keysPressed[keyCode];
    }

    public Position getPointerPosition() {
        return pointerPosition;
    }

    public boolean isMouseClicked() {
        return mouseClicked;
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
        mouseMoved = true;
        mousePosition = new Position(e.getPoint().getX(), e.getPoint().getY());
    }

    @Override
    public void mouseMoved(MouseEvent e) {
        mousePosition = new Position(e.getPoint().getX(), e.getPoint().getY());
        mouseMoved = true;
    }

    public Position getMousePosition() {
        return mousePosition;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    }

    @Override
    public void mousePressed(MouseEvent e) {
        mousePressed = true;
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        mouseClicked = true;
        mousePressed = false;
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }


}
