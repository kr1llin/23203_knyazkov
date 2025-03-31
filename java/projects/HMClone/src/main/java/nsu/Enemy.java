//package nsu;
//
//import javafx.geometry.Point2D;
//import javafx.scene.paint.Color;
//import javafx.scene.shape.Rectangle;
//import nsu.entity.GameObject;
//
//class Enemy extends GameObject {
//    private double speed = 3.0;
//    private boolean movingRight = false;
//    private boolean movingLeft = false;
//    private boolean movingUp = false;
//    private boolean movingDown = false;
//    private double mouseX;
//    private double mouseY;
//
//    public Enemy(Point2D position) {
//        super(new Rectangle(position.getX(), position.getY(), Color.RED));
//    }
//
//    @Override
//    public void update() {
//        updateMovement();
//        updateRotation();
//    }
//
//    private void updateMovement() {
//        double dx = 0, dy = 0;
//        if (movingRight) dx += speed;
//        if (movingLeft) dx -= speed;
//        if (movingUp) dy -= speed;
//        if (movingDown) dy += speed;
//
//        setVelocity(new Point2D(dx, dy));
//
//        view.setTranslateX(view.getTranslateX() + velocity.getX());
//        view.setTranslateY(view.getTranslateY() + velocity.getY());
//
////        view.setTranslateX(clamp(view.getTranslateX() + velocity.getX(), 0, world_width - view.getScaleX()));
////        view.setTranslateY(clamp(view.getTranslateY() + velocity.getY(), 0, world_height - view.getScaleY()));
//
//    }
//
//    private double clamp(double value, double min, double max) {
//        return Math.max(min, Math.min(value, max));
//    }
//
//    private void updateRotation() {
//        double dx = mouseX - view.getTranslateX();
//        double dy = mouseY - view.getTranslateY();
//        double angle = Math.toDegrees(Math.atan2(dy, dx));
//        view.setRotate(angle);
//    }
//}