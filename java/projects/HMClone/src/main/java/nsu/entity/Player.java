package nsu.entity;

import nsu.display.Camera;
import nsu.obj_core.*;
import nsu.controller.Controller;
import nsu.graphics.SpriteLibrary;

public class Player extends MovingEntity {
    public Player(Controller controller, SpriteLibrary spriteLibrary, Camera camera){
        super(controller, spriteLibrary, camera);
    }

    @Override
    public void update() {
        super.update();
//        moveTowardsCursor(super.controller);
    }

//    private void moveTowardsCursor(Controller controller){
//        Position mousePosition = controller.getMousePosition();
////        mousePosition = Camera.ScreenToWorldPoint(mousePosition);
////
////        Vector2D direction = new Vector2D(mousePosition.getX() - , mousePosition.getY());
//    }
}
