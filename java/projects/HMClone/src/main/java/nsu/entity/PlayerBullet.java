package nsu.entity;

import nsu.obj_core.Position;
import nsu.obj_core.collission.CollisionBox;

public class PlayerBullet extends Bullet{
    private final int playerBulletSpeed = 2;
    private final int playerBulletDamage = 15;
    public PlayerBullet(Position position, Position direction) {
        super(position, direction);
        damage = playerBulletDamage;
        speed = playerBulletSpeed;
    }
}
