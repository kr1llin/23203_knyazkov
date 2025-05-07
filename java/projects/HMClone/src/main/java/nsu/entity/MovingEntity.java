package nsu.entity;

import nsu.controller.Controller;
import nsu.game.state.State;
import nsu.graphics.AnimationManager;
import nsu.obj_core.*;
import nsu.obj_core.collission.CollisionBox;

import java.awt.*;

public abstract class MovingEntity extends GameObject {
    protected Controller controller = null;
    protected Motion motion = null;
    protected AnimationManager animationManager = null;
    protected double velocity = 5;


    public MovingEntity(Controller controller) {
        super();
        this.controller = controller;
        this.motion = new Motion(velocity);
    }

    public void changeDirectionTo(Position targetWorldPosition) {
        double dx = targetWorldPosition.getX() - position.getX();
        double dy = targetWorldPosition.getY() - position.getY();
        Vector2D delta = new Vector2D(dx, dy);
        double length = delta.length();
        if (length > 0) {
            motion.setVector(new Vector2D(dx, dy
            ));
        }
    }

    public MovingEntity(Position position, int velocity) {
        super(position);
        this.velocity = velocity;
        this.motion = new Motion(velocity);
    }

    @Override
    public void update(State state) {
        motion.update();
        position.apply(motion);
    }


    protected void decideAnimation() {
        if (motion.isMoving()) {
            animationManager.playAnimation("walk");
        } else {
            animationManager.playAnimation("idle");
        }
    }

    @Override
    public CollisionBox getCollisionBox() {
        return new CollisionBox(
                new Rectangle(
                        (int) (position.intX() + motion.getVector().getX()),
                        (int) (position.intY() + motion.getVector().getY()),
                        (int) size.getWidth(),
                        (int) size.getHeight()
                )
        );
    }

    public void stopMoving() {
        motion.setVector(new Vector2D(0, 0));
    }

    public void stopMovingSide(String collisionSide) {
        motion.blockSide(collisionSide);
    }

    public void startMovingSide(String collisionSide) {
        motion.unblockSide(collisionSide);
    }

    public double getVelocity() {
        return velocity;
    }

    public Motion getMotion() {
        return motion;
    }

    public Controller getController() {
        return controller;
    }
}
