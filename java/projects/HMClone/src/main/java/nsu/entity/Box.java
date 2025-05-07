package nsu.entity;

import nsu.obj_core.collission.CollisionBox;
import nsu.obj_core.collission.CollisionVisitor;
import nsu.obj_core.Position;
import nsu.obj_core.Size;
import nsu.game.state.State;

import java.awt.*;
import java.io.IOException;

public class Box extends GameObject {
    final int BOX_SIZE = 64;
    final int BOX_HEALTH = 30;

    public Box(double x, double y) {
        super();
        setHealth(BOX_HEALTH);
        setPosition(new Position(x, y));
        setSize(new Size(BOX_SIZE, BOX_SIZE));
    }

    @Override
    public void update(State state) {

    }

    @Override
    public CollisionBox getCollisionBox() {
        return new CollisionBox(
                new Rectangle(
                        position.intX(),
                        position.intY(),
                        (int) size.getWidth(),
                        (int) size.getHeight()
                )
        );
    }

    @Override
    public void accept(CollisionVisitor visitor, GameObject other) {
        visitor.visit(this, other);
    }
}
