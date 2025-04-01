package nsu.entity;


import nsu.display.Camera;
import nsu.game.state.State;
import nsu.obj_core.Position;
import nsu.obj_core.Size;
import nsu.obj_core.Rotation;
import org.jetbrains.annotations.NotNull;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.io.IOException;

public abstract class GameObject {
    protected Position position;
    protected Size size;
    protected Rotation rotation;
    protected boolean isAlive = false;
    protected boolean isShooting = false;

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

    public abstract void update();
    public abstract Image getSprite() throws IOException; // CHANGE: separate graphics loader based on gameObject

    public AffineTransform getAffineTransform(State state, GameObject gameObject)
    {
        Camera camera = state.getCamera();

        double screenX = gameObject.getPosition().getX() - camera.getPosition().getX();
        double screenY = gameObject.getPosition().getY() - camera.getPosition().getY();
        int height = gameObject.getSize().getHeight();
        int width = gameObject.getSize().getWidth();

        AffineTransform transform = new AffineTransform();
        transform.translate(screenX, screenY);
        transform.translate(-width / 2.0, -height / 2.0);
        return transform;
    }

    public void stopShooting() {
        isShooting = false;
    }

    public boolean isAlive() {
        return isAlive;
    }
}

//import javafx.scene.Node;
//import javafx.geometry.Point2D;
//
//public abstract class GameObject {
//    double world_width, world_height;
//    protected Node view;
//    protected Point2D velocity = new Point2D(0, 0);
//    protected boolean alive = true;
//    public Point2D position;
//    public GameObject(Node view) {
//        this.view = view;
//    }
//
//    public void handleCollision(GameObject other){
//        if (other.getClass().getName() == "Wall"){}
//        else {
//            setAlive(false);
//        }
//    }
//    public void setPosition(Point2D pos){
//        position = pos;
//    }
//
//    public Point2D getPosition(){
//        return position;
//    }
//
//    // the only abstract method
//    public abstract void update();
//
//    public Node getView() { return view; }
//    public boolean isAlive() { return alive; }
//    public void setAlive(boolean alive) { this.alive = alive; }
//    public boolean isDead() { return !alive; }
//    public void setVelocity(Point2D velocity) { this.velocity = velocity; }
//    public Point2D getVelocity() { return velocity; }
//
//
//    public boolean isColliding(GameObject other) {
//        return getView().getBoundsInParent().intersects(other.getView().getBoundsInParent());
//    }
//}