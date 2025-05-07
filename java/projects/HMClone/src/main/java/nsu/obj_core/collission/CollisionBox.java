package nsu.obj_core.collission;

import java.awt.*;

public class CollisionBox {

    private final Rectangle bounds;

    public CollisionBox(Rectangle bounds){
        this.bounds = bounds;
    }

    public boolean collidesWith(CollisionBox other){
        return other != null && bounds.intersects(other.getBounds());
    }

    public Rectangle getBounds(){
        return bounds;
    }

}
