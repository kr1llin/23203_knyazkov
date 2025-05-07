package nsu.obj_core;

import nsu.controller.Controller;

import java.util.HashSet;
import java.util.Set;

public class Motion {
    private Vector2D vector;
    private double velocity;
    private Position mousePos;

    private boolean movingLeft = true;
    private boolean movingRight= true;
    private boolean movingUp = true;
    private boolean movingDown = true;

    private final Set<String> blockedSides = new HashSet<>();

    public void blockSide(String side) {
        blockedSides.add(side);
    }

    public void unblockSide(String side) {
        blockedSides.remove(side);
    }

    public Motion(double velocity) {
        this.vector = new Vector2D(0, 0);
        this.velocity = velocity;
    }

    public void update(Controller controller){
        int dx = 0, dy = 0;

        if (controller.isRequestingUp() && !blockedSides.contains("up")) {
            dy--;
        }

        if (controller.isRequestingDown() && !blockedSides.contains("down")) {
            dy++;
        }
        if (controller.isRequestingLeft() && !blockedSides.contains("left")) {
            dx--;
        }
        if (controller.isRequestingRight() && !blockedSides.contains("right")) {
            dx++;
        }

        if (controller.cursorMoved()){
            mousePos = controller.getMousePosition();
        }

        vector = new Vector2D(dx, dy);
        vector.normalize();
        vector.multiply(velocity);
        clearMoving();
    }

    public void update(){
        if (blockedSides.contains("down") || blockedSides.contains("up")) {
            vector.setY(0);
        }
        if (blockedSides.contains("right") || blockedSides.contains("left")) {
            vector.setX(0);
        }

        vector.multiply(velocity);
    }

    public void clearMoving(){
        blockedSides.clear();
    }

    public boolean isMoving() {
        return vector.length() > 0;
    }
    public Vector2D getVector() {
        return vector;
    }

    public void setVector(Vector2D direction) {
        vector = direction;
        vector.normalize();
    }

    public Set<String> getBlockedSides(){
        return blockedSides;
    }

    public void setX(int X){
        vector = new Vector2D(X, vector.getY());
    }

    public void setY(int Y){
        vector = new Vector2D(vector.getX(), Y);
    }

    public void stopLeft(){
        movingLeft = false;
    }

    public void stopRight(){
        movingRight = false;
    }

    public void stopUp(){
        movingUp = false;
    }

    public void stopDown(){
        movingDown = false;
    }

    public void startLeft() {
        movingLeft = true;
    }
    public void startRight() {
        movingRight = true;
    }
    public void startUp() {
        movingUp = true;
    }
    public void startDown() {
        movingDown = true;
    }

    public void setVelocity(double v) {
        velocity = v;
    }
}

