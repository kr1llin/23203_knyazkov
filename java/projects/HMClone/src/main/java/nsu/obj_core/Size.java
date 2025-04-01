package nsu.obj_core;

public class Size {
    private int width;
    private int height;

    public Size(int width, int height) {
        this.width = width;
        this.height = height;
    }

    public Size(Size size){
        this.width = size.getWidth();
        this.height = size.getHeight();
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }
}
