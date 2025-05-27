package nsu.obj_core.collission;

import nsu.entity.*;

import static nsu.obj_core.collission.CollisionUtils.getCollisionSide;
import static nsu.obj_core.collission.CollisionUtils.resolveOverlap;

public class CollisionHandler implements CollisionVisitor {
    @Override
    public void visit(Player player, GameObject other) {
        if (other instanceof Enemy){
            resolveOverlap(player, other);
            player.decreaseHealth(((Enemy) other).hit());
        }
        else if (other instanceof EnemyBullet) {
            player.decreaseHealth(((Bullet) other).hit());
        }
        else if (other instanceof Box){
            String side = getCollisionSide(player, other);
            System.out.println(side);
            player.stopMovingSide(side);
        }
    }

    @Override
    public void visit(Enemy enemy, GameObject other) {
        if (other instanceof PlayerBullet) {
            enemy.decreaseHealth(((Bullet) other).hit());
        }
        else if (other instanceof Box){
            String side = getCollisionSide(enemy, other);
            resolveOverlap(enemy, other);
            enemy.stopMovingSide(side);
        }
        else if (other instanceof Player){
            resolveOverlap(enemy, other);
        }
        else if (other instanceof Enemy){
            resolveOverlap(enemy, other);
        }
    }

    @Override
    public void visit(Bullet bullet, GameObject other) {
        if (other instanceof Box){
            other.decreaseHealth(bullet.hit());
            bullet.die();
        }
    }

    @Override
    public void visit(Box box, GameObject other) {
        if (other instanceof Enemy){
            box.decreaseHealth(((Enemy) other).hit());
        }
        if (other instanceof Player){
            String side = getCollisionSide(other, box);
            ((Player)other).stopMovingSide(side);
            resolveOverlap(other, box);
        }
    }
}
