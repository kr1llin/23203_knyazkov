package nsu.obj_core;

import java.awt.*;

public class Size extends Dimension {
    private double width;
    private double height;

    public Size(int width, int height) {
        this.width = width;
        this.height = height;
    }

    public Size(Size size){
        this.width = size.getWidth();
        this.height = size.getHeight();
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }
}
