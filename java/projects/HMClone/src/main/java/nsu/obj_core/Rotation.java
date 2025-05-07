package nsu.obj_core;

public class Rotation {
    double rotationAngle = 0;

    public double getRotationAngle(){
        return rotationAngle;
    }
    public void apply(Position mousePosition, Position entityPosition){
        if (mousePosition != null) {

            double dx = mousePosition.getX() - entityPosition.getX();
            double dy = mousePosition.getY() - entityPosition.getY();

            this.rotationAngle = Math.toDegrees(Math.atan2(
                    dy,
                    dx
            ));

        }
    }
    public void setRotationAngle(double angle){
        rotationAngle = angle;
    }
}
