package nsu.entity;

import nsu.obj_core.Position;

public class EnemyBullet extends Bullet {
    private final int enemyBulletSpeed = 2;

    public EnemyBullet(Position position, Position direction) {
        super(position, direction);
        speed = enemyBulletSpeed;
    }
}
