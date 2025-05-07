package nsu.display;

import nsu.entity.GameObject;
import nsu.game.state.LevelState;
import nsu.game.state.State;
import nsu.obj_core.Position;
import nsu.obj_core.Size;

import java.awt.*;
import java.util.Optional;

public class Camera {
    private Position position;
    private Size windowSize;

    private Optional<GameObject> objectWithFocus;

    public Camera(Size windowSize) {
        this.position = new Position(0,0);
        this.windowSize = windowSize;
    }

    public void focusOn(GameObject object){
        this.objectWithFocus = Optional.of(object);
    }

    public void update(LevelState state){
        if (objectWithFocus.isPresent()) {
            Position objectPosition = objectWithFocus.get().getPosition();

            this.position.setX(objectPosition.getX() + (double) objectWithFocus.get().getSize().getWidth() /2 - (double) windowSize.getWidth() / 2);
            this.position.setY(objectPosition.getY() + (double) objectWithFocus.get().getSize().getHeight() /2 - (double) windowSize.getHeight() / 2);

            clampWithinBounds(state);
        }
    }

    public Size getWindowSize() {
        return windowSize;
    }

    public Position screenToWorld(Position screenPosition) {
        return new Position(
                screenPosition.getX() + this.getPosition().getX(),
                screenPosition.getY() + this.getPosition().getY()
        );
    }

    private void clampWithinBounds(LevelState state) {
        if (position.getX() < 0) {
            position.setX(0);
        }

        if (position.getY() < 0){
            position.setY(0);
        }

        if (position.getX() + windowSize.getWidth() > state.getWorld().getWidth()){
            position.setX(state.getWorld().getWidth() - windowSize.getWidth());
        }

        if (position.getY() + windowSize.getHeight() > state.getWorld().getHeight()){
            position.setY(state.getWorld().getHeight() - windowSize.getHeight());
        }
    }

    public Position getPosition() {
        return position;
    }
}
