package nsu;

import com.sun.javafx.geom.Point2D;
import javafx.scene.input.TouchPoint;

import java.util.Optional;
//
//public class Camera {
//    private Point2D position; // make separate object for Position
//    private Point2D windowSize; // make separate object for Size
////    GameObject player;
////    boolean followPlayer = true;
//    private Optional<GameObject> objectWithFocus;
//
//    public Camera(Point2D windowSize){
//        this.position = new Point2D(0,0);
//        this.windowSize = windowSize;
//    }
//
//    public void focusOn(GameObject object){
//        this.objectWithFocus  = Optional.of(object);
//    }
//
//    // make class State
//    public void update(){
//        if (objectWithFocus.isPresent()){
//            Point2D objectPosition = new Point2D((float) objectWithFocus.get().getView().getTranslateX(), (float) objectWithFocus.get().getView().getTranslateY());
//            this.position.x = objectPosition.x - windowSize.x / 2;
//            this.position.y = objectPosition.y - windowSize.y / 2;
//        }
//
//    }
//}
