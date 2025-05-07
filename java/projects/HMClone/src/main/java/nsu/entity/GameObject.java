package nsu.entity;


import nsu.display.Camera;
import nsu.game.state.LevelState;
import nsu.game.state.State;
import nsu.obj_core.*;
import nsu.obj_core.collission.CollisionBox;
import nsu.obj_core.collission.CollisionVisitor;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.io.IOException;

public abstract class GameObject {
    protected Position position;
    protected Size size;
    protected Rotation rotation;
    protected boolean isAlive = false;
    protected boolean isShooting = false;
    protected int health = 100;

    public GameObject(){
        isAlive = true;
        position = new Position(50, 50);
        size = new Size(100, 100);
        rotation = new Rotation();
    }

    public GameObject(Position position){
        isAlive = true;
        this.position = new Position(position);
        this.rotation = new Rotation();
    }

    public void setPosition(Position position) {
        this.position = position;
    }

    public void setSize(Size size) {
        this.size = size;
    }

    public void decreaseHealth(int by){
        this.health -= by;
    }
    public void increaseHealth(int by){
        this.health += by;
    }

    public void setHealth(int health){
        this.health = health;
    }

    public int getHealth(){
        return health;
    }

    public void kill(){
        isAlive = false;
    }

    public Position getPosition() {
        return position;
    }

    public boolean isShooting(){
        return isShooting;
    }

    public Size getSize() {
        return size;
    }

    public Rotation getRotation(){
        return rotation;
    }

    public abstract void update(State state);
    public abstract CollisionBox getCollisionBox();

    abstract public void accept(CollisionVisitor visitor, GameObject other);

    public AffineTransform getAffineTransform(LevelState state, GameObject gameObject)
    {
        Camera camera = state.getCamera();

        double screenX = gameObject.getPosition().getX() - camera.getPosition().getX();
        double screenY = gameObject.getPosition().getY() - camera.getPosition().getY();
        double height = gameObject.getSize().getHeight();
        double width = gameObject.getSize().getWidth();

        AffineTransform transform = new AffineTransform();
        transform.translate(screenX, screenY);
        transform.translate(-width / 2.0, -height / 2.0);
        return transform;
    }

    public void stopShooting() {
        isShooting = false;
    }

    public boolean isAlive() {
        return isAlive && (health > 0);
    }

    public void setPositionX(double v) {
        position.setX(v);
    }

    public void setPositionY(double v) {
        position.setY(v);
    }
}
