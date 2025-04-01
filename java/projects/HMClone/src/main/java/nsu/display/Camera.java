package nsu.display;

import nsu.entity.GameObject;
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

    public void update(State state){
        if (objectWithFocus.isPresent()) {
            Position objectPosition = objectWithFocus.get().getPosition();

            this.position.setX(objectPosition.getX() - windowSize.getWidth() / 2);
            this.position.setY(objectPosition.getY() - windowSize.getHeight() / 2);

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

    private void clampWithinBounds(State state) {
        if (position.getX() < 0) {
            position.setX(0);
        }

        if (position.getY() < 0){
            position.setY(0);
        }

        if (position.getX() + windowSize.getWidth() > state.getLevel().getWidth()){
            position.setX(state.getLevel().getWidth() - windowSize.getWidth());
        }

        if (position.getY() + windowSize.getHeight() > state.getLevel().getHeight()){
            position.setY(state.getLevel().getHeight() - windowSize.getHeight());
        }
    }

    public Position getPosition() {
        return position;
    }
}
