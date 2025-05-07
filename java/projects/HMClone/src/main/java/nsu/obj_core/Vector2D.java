package nsu.obj_core;

public class Vector2D {
    private double x, y;

    public Vector2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public static double distance(Position a, Position b) {
        return Math.sqrt(Math.pow(a.getX() - b.getX(), 2) + Math.pow(a.getY() - b.getY(), 2));
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

    public void normalize(){
        double len = length();
        if (len != 0) {
            x /= len;
            y /= len;
        }
    }

    public void setX(double  v) {
        x = v;
    }

    public void setY(double v){
        y =v;
    }

    public void setVector(Vector2D initVect) {
        x = initVect.x;
        y = initVect.y;
    }

}
