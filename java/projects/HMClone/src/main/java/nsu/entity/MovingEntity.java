package nsu.entity;

import nsu.controller.Controller;
import nsu.graphics.AnimationManager;
import nsu.graphics.SpriteLibrary;
import nsu.obj_core.Motion;

import java.awt.*;

public abstract class MovingEntity extends GameObject {
    private Controller controller;
    private Motion motion;
    private AnimationManager animationManager;

    public MovingEntity(Controller controller, SpriteLibrary spriteLibrary) {
        super();
        this.controller = controller;
        this.motion = new Motion(2);
        animationManager = new AnimationManager(spriteLibrary.getUnit("player"));
    }

    @Override
    public void update(){
        motion.update(controller);
        position.apply(motion);
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
