//package nsu;
//
//import com.sun.javafx.geom.Point2D;
//import javafx.scene.input.TouchPoint;
//import javafx.scene.layout.Pane;
//
//import java.util.Optional;
//import java.util.function.Supplier;
//
//import static java.lang.Math.clamp;
//
//public class Camera {
//    private final double CAMERA_LERP = 0.1; // Smoothing factor
//    private double x, y;
//    private final double worldWidth, worldHeight;
//    private Supplier<Point2D> targetSupplier;
//
//    public Camera(double width, double height) {
//        worldWidth = width;
//        worldHeight = height;
//    }
//
//    public void update(double viewportWidth, double viewportHeight) {
//        Point2D target = targetSupplier.get();
//        double targetX = target.x - viewportWidth / 2;
//        double targetY = target.y - viewportHeight / 2;
//
////        cameraX += (targetX - cameraX) * CAMERA_LERP;
//
//        x = lerp(x, clamp(targetX, 0, viewportWidth));
//        y = lerp(y, clamp(targetY, 0, viewportHeight));
//    }
//
//    private double lerp(double x, double clamp) {
//        return x + (clamp - x) * CAMERA_LERP;
//    }
//
//    public void apply(Pane root) {
//        root.setTranslateX(-x);
//        root.setTranslateY(-y);
//    }
//
//    public double getX() {
//        return x;
//    }
//
//    public double getY(){
//        return y;
//    }
//
//}