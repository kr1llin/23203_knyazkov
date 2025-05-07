package nsu.graphics;

import nsu.game.Game;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class AnimationManager {
    private static class AnimationState {
        SpriteSet spriteSet;
        BufferedImage currentAnimationSheet;
        int currentFrameTime;
        int frameIndex;

        AnimationState(SpriteSet spriteSet, String initialAnimation) {
            this.spriteSet = spriteSet;
            this.currentAnimationSheet = (BufferedImage) spriteSet.get(initialAnimation);
            this.frameIndex = 0;
            this.currentFrameTime = 0;
        }
    }

    private SpriteSet spriteSet;
    private BufferedImage currentAnimationSheet;
    private final SpriteLibrary spriteLibrary;
    private final Map<UUID, AnimationState> animations = new HashMap<>();

    private int currentFrameTime;
    private int updatesPerFrame; // how many updates we want one frame to live (better to keep it in config file?)
    private int frameIndex; // which frame we're one

//    public AnimationManager(SpriteSet spriteSet) {
//        this.spriteSet = spriteSet;
//        this.updatesPerFrame = 20;
//        this.frameIndex = 0;
//        this.currentFrameTime = 0;
//        playAnimation("idle");
//    }

    public AnimationManager(SpriteLibrary spriteLibrary){
        this.spriteLibrary = spriteLibrary;
    }

    public void registerObject(UUID objectID, String initAnimation){
//        animations.put(objectID, new AnimationState(
//                spriteLibrary.get
//        ))
    }

    public Image getSprite() {
        return currentAnimationSheet.getSubimage(
                frameIndex * SpriteLibrary.SPRITE_SIZE,
                0,
                SpriteLibrary.SPRITE_SIZE,
                SpriteLibrary.SPRITE_SIZE
        );
    }

    public void update(){
        currentFrameTime++;

        if (currentFrameTime >= updatesPerFrame) {
            currentFrameTime = 0;
            frameIndex++;

            if (frameIndex >= currentAnimationSheet.getWidth() / SpriteLibrary.SPRITE_SIZE) {
                frameIndex = 0;
            }
        }
    }

    // for now, we're assuming that it has correct name (TOCHANGE!)
    public void playAnimation(String name) {
        this.currentAnimationSheet = (BufferedImage) spriteSet.get(name);
    }

}
