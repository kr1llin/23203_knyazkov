package nsu.entity;

import nsu.controller.Controller;
import nsu.display.Camera;
import nsu.graphics.AnimationManager;
import nsu.graphics.SpriteLibrary;
import nsu.obj_core.Motion;

import java.awt.*;

public abstract class MovingEntity extends GameObject {
    protected final Controller controller;
    protected final Motion motion;
    private final AnimationManager animationManager;
    private final Camera camera;

    public MovingEntity(Controller controller, SpriteLibrary spriteLibrary, Camera camera) {
        super();
        this.controller = controller;
        this.motion = new Motion(2);
        this.camera = camera;
        animationManager = new AnimationManager(spriteLibrary.getUnit("player"));
    }

    @Override
    public void update(){
        motion.update(controller);
        position.apply(motion);
        rotation.apply(controller.getMousePosition(), this.position, camera);
        decideAnimation();
        animationManager.update();
    }

    private void decideAnimation(){
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
