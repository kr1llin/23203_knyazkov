package nsu.obj_core.collission;

import nsu.entity.*;

import static nsu.obj_core.collission.CollisionUtils.getCollisionSide;

public class CollisionReleaser implements CollisionVisitor {
    @Override
    public void visit(Player player, GameObject other) {
        if (other instanceof Box){
            String side = getCollisionSide(player, other);
            player.startMovingSide(side);
        }
    }

    @Override
    public void visit(Enemy enemy, GameObject other) {

        if (other instanceof Box){
            String side = getCollisionSide(enemy, other);
            enemy.startMovingSide(side);
        }
    }

    @Override
    public void visit(Bullet bullet, GameObject other) {

    }

    @Override
    public void visit(Box box, GameObject other) {

    }
}
