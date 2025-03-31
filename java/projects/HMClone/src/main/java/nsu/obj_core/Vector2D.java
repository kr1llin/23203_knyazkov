package nsu.obj_core;

public class Vector2D {
    private double x, y;

    public Vector2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public void multiply(double velocity){
        x *= velocity;
        y *= velocity;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double length(){
        return Math.sqrt(x*x + y*y);
    }

    public void normilize(){
        if (length() != 0) {
            x = x == 0 ? 0 : x / length();
            y = y == 0 ? 0 : y / length();
        }
    }
}
