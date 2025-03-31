package nsu.obj_core;

import nsu.controller.Controller;

public class Motion {
    private Vector2D vector;
    private double velocity;

    public Motion(double velocity) {
        this.vector = new Vector2D(0, 0);
        this.velocity = velocity;
    }

    public void update(Controller controller){
        int dx = 0, dy = 0;

        if (controller.isRequestingUp()) {
            dy--;
        }

        if (controller.isRequestingDown()) {
            dy++;
        }
        if (controller.isRequestingLeft()) {
            dx--;
        }
        if (controller.isRequestingRight()) {
            dx++;
        }

        vector = new Vector2D(dx, dy);
        vector.normilize();
        vector.multiply(velocity);
    }

    public boolean isMoving() {
        return vector.length() > 0;
    }
    public Vector2D getVector() {
        return vector;
    }
}

