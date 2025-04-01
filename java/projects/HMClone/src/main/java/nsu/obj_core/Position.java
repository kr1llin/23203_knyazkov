package nsu.obj_core;

public class Position {
    private double x;
    private double y;

    public Position(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public int intX() {
        return (int)Math.round(x);
    }

    public int intY(){
       return (int)Math.round(y);
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getY() {
        return y;
    }

    public void apply (Motion movement){
        Vector2D vector = movement.getVector();
        x += vector.getX();
        y += vector.getY();

    }
}
