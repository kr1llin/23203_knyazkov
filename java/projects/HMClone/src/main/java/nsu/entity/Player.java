package nsu.entity;

import nsu.display.Camera;
import nsu.game.state.State;
import nsu.obj_core.*;
import nsu.controller.Controller;
import nsu.graphics.SpriteLibrary;

import java.awt.geom.AffineTransform;

public class Player extends MovingEntity {
    State state;
    public Player(Controller controller, SpriteLibrary spriteLibrary, Camera camera){
        super(controller, spriteLibrary, camera);
        this.state = state;
    }

    @Override
    public void update() {
        motion.update(controller);
        position.apply(motion);
        rotation.apply(controller.getMousePosition(), this.position, camera);
        if (controller.isShooting()){
            isShooting = true;
        }
        decideAnimation();
        animationManager.update();
    }
    @Override
    public AffineTransform getAffineTransform(State state, GameObject gameObject) {
        Camera camera = state.getCamera();

        double screenX = gameObject.getPosition().getX() - camera.getPosition().getX();
        double screenY = gameObject.getPosition().getY() - camera.getPosition().getY();
        int height = gameObject.getSize().getHeight();
        int width = gameObject.getSize().getWidth();

        AffineTransform transform = new AffineTransform();
        transform.translate(screenX, screenY);
        transform.rotate(Math.toRadians(gameObject.getRotation().getRotationAngle()) + Math.PI / 2, 0, 0); // sprite looks up (we assume that all sprites are faced up)
        transform.translate(-width / 2.0, -height / 2.0);
        return transform;
    }

//    private void moveTowardsCursor(Controller controller){
//        Position mousePosition = controller.getMousePosition();
////        mousePosition = Camera.ScreenToWorldPoint(mousePosition);
////
////        Vector2D direction = new Vector2D(mousePosition.getX() - , mousePosition.getY());
//    }
}
