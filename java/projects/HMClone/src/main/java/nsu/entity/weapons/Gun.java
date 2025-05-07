package nsu.entity.weapons;

import nsu.entity.*;
import nsu.obj_core.Position;
import nsu.obj_core.Vector2D;

import java.util.Arrays;
import java.util.List;

public class Gun extends Weapon {
    public Gun(GameObject parent) {
        super(parent);
    }

    @Override
    public void shootAt(Position position){

        Bullet bullet = (parent instanceof Player)
                ? new PlayerBullet(parent.getPosition(), position)
                : new EnemyBullet(parent.getPosition(), position);
        bullets.add(bullet);
    }
}
