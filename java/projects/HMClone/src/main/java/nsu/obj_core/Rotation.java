package nsu.obj_core;

import nsu.display.Camera;

public class Rotation {
    double rotationAngle = 0;

    public double getRotationAngle(){
        return rotationAngle;
    }
    public void apply(Position mousePosition, Position entityPosition, Camera camera){
        if (mousePosition != null) {

            double mouseWorldPositionX = mousePosition.getX() + camera.getPosition().intX();
            double mouseWorldPositionY = mousePosition.getY() + camera.getPosition().intY();

            double dx = mouseWorldPositionX - entityPosition.getX();
            double dy =mouseWorldPositionY - entityPosition.getY();

//            double dx = mousePosition.getX() - entityPosition.getX();
//            double dy = mousePosition.getY() - entityPosition.getY();

            this.rotationAngle = Math.toDegrees(Math.atan2(
                    dy,
                    dx
            ));

            System.out.println("New rotation: " + rotationAngle);
        }
    }
    public void setRotationAngle(double angle){
        rotationAngle = angle;
    }
}
