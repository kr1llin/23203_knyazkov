package nsu.entity;

import nsu.controller.Controller;
import nsu.display.Camera;
import nsu.graphics.AnimationManager;
import nsu.graphics.SpriteLibrary;
import nsu.obj_core.Motion;
import nsu.obj_core.Position;
import nsu.obj_core.Size;
import nsu.obj_core.Vector2D;

import java.awt.*;

public abstract class MovingEntity extends GameObject {
    protected  Controller controller = null;
    protected  Motion motion = null;
    protected  AnimationManager animationManager = null;
    protected  Camera camera = null;
    protected double velocity = 5;

    public MovingEntity(Controller controller, SpriteLibrary spriteLibrary, Camera camera) {
        super();
        this.controller = controller;
        this.motion = new Motion(velocity);
        this.camera = camera;
        animationManager = new AnimationManager(spriteLibrary.getUnit("player"));
    }
    public void changeDirectionTo(Position targetWorldPosition) {
        double dx = targetWorldPosition.getX() - position.getX();
        double dy = targetWorldPosition.getY() - position.getY();
        Vector2D delta = new Vector2D(dx, dy);
        double length = delta.length();
        if (length > 0) {
            motion.setVector(new Vector2D(
                    (dx / length) * velocity,
                    (dy / length) * velocity
            ));
        }
    }

    public MovingEntity(Position position, int velocity) {
        super(position);
        this.velocity = velocity;
        this.motion = new Motion(velocity);
    }

    @Override
    public void update(){
        motion.update();
        position.apply(motion);
//        rotation.apply(controller.getMousePosition(), this.position, camera);
//        if (controller.isShooting()){
//            isShooting = true;
//        }
    }

    protected void decideAnimation(){
        if (motion.isMoving()) {
            animationManager.playAnimation("walk");
        }
        else {
            animationManager.playAnimation("idle");
        }
    }

    @Override
    public Image getSprite()  {
        return animationManager.getSprite();
    }

}
