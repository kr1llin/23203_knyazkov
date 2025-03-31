package nsu;


public abstract class GameObject {
    private Position position;
    private Size size;
}

//import javafx.scene.Node;
//import javafx.geometry.Point2D;
//
//public abstract class GameObject {
//    double world_width, world_height;
//    protected Node view;
//    protected Point2D velocity = new Point2D(0, 0);
//    protected boolean alive = true;
//    public Point2D position;
//    public GameObject(Node view) {
//        this.view = view;
//    }
//
//    public void handleCollision(GameObject other){
//        if (other.getClass().getName() == "Wall"){}
//        else {
//            setAlive(false);
//        }
//    }
//    public void setPosition(Point2D pos){
//        position = pos;
//    }
//
//    public Point2D getPosition(){
//        return position;
//    }
//
//    // the only abstract method
//    public abstract void update();
//
//    public Node getView() { return view; }
//    public boolean isAlive() { return alive; }
//    public void setAlive(boolean alive) { this.alive = alive; }
//    public boolean isDead() { return !alive; }
//    public void setVelocity(Point2D velocity) { this.velocity = velocity; }
//    public Point2D getVelocity() { return velocity; }
//
//
//    public boolean isColliding(GameObject other) {
//        return getView().getBoundsInParent().intersects(other.getView().getBoundsInParent());
//    }
//}