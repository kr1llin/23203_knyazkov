package nsu.obj_core;

import nsu.display.Camera;

public class Rotation {
    double rotationAngle = 0;

    public double getRotationAngle(){
        return rotationAngle;
    }
    public void apply(Position mousePosition, Position entityPosition, Camera camera){
        if (mousePosition != null) {

            double mouseWorldPositionX = mousePosition.getX() + (double) camera.getPosition().intX();
            double mouseWorldPositionY = mousePosition.getY() + (double) camera.getPosition().intY();

            double dx = mouseWorldPositionX - entityPosition.getX();
            double dy = mouseWorldPositionY - entityPosition.getY();

//            double dx = mousePosition.getX() - entityPosition.getX();
//            double dy = mousePosition.getY() - entityPosition.getY();

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
