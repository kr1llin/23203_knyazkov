package nsu.entity;

import nsu.game.state.State;
import nsu.obj_core.collission.CollisionBox;
import nsu.obj_core.collission.CollisionVisitor;
import nsu.obj_core.Position;
import nsu.obj_core.Size;

import java.awt.*;

public class Bullet extends MovingEntity{
    int BULLET_WIDTH =  25;
    int BULLET_HEIGHT = 25;
    static int speed = 2;
    int damage = 5;

    public Bullet(Position position, Position direction) {
        super(position, speed);
        changeDirectionTo(direction);
        size = new Size(BULLET_WIDTH, BULLET_HEIGHT);
    }

    @Override
    public void update(State state) {
        // bullet takes in constructor player position
        // normalizes direction (unit vector by mouse position)
        super.update(state);
    }

    @Override
    public void accept(CollisionVisitor visitor, GameObject other) {
        visitor.visit(this, other);
    }

    public int getDamage(){
        return damage;
    }

    public int getSpeed(){
        return speed;
    }

    boolean hit = false;

    public int hit() {
        if (!hit) {
            hit = true;
            return damage;
        } else {
            return 0;
        }
    }
    public CollisionBox getCollisionBox(){
        return new CollisionBox(
                new Rectangle(
                        (int) (position.intX() + motion.getVector().getX()),
                        (int) (position.intY() + motion.getVector().getY()),
                        (int) size.getWidth() + 5,
                        (int) size.getHeight() + 5
                )
        );
    }

    public void die() {
        isAlive = false;
    }
}
