package nsu;

import javafx.geometry.Point2D;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

class Bullet extends GameObject {
    private static final double BULLET_SPEED = 20.0;

    public Bullet(Point2D direction) {
        super(new Circle(10, 10, 10, Color.BLACK));
        setVelocity(direction.normalize().multiply(BULLET_SPEED));
    }

    @Override
    public void update() {
        if (isAlive()) {
            view.setTranslateX(view.getTranslateX() + velocity.getX());
            view.setTranslateY(view.getTranslateY() + velocity.getY());
        }
    }

    public boolean isOutOfBound(double world_width, double world_height){
        double x = this.getView().getTranslateX();
        double y = this.getView().getTranslateY();
        if (x < 0 || x > world_width || y < 0 || y > world_height){
            setAlive(false);
            return true;
        }
        return false;
    }
}