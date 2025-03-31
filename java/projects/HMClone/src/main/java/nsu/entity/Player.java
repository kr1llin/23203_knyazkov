package nsu.entity;

import nsu.controller.Controller;
import nsu.graphics.SpriteLibrary;

public class Player extends MovingEntity {
    public Player(Controller controller, SpriteLibrary spriteLibrary){
        super(controller, spriteLibrary);
    }

    @Override
    public void update() {
        super.update();
    }
}
