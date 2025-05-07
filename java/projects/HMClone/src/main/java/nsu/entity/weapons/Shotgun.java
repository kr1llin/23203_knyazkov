package nsu.entity.weapons;

import nsu.entity.*;
import nsu.obj_core.Position;

import java.util.Random;

public class Shotgun extends Weapon {
    private int numOfShells = 5;
    public Shotgun(GameObject parent) {
        super(parent);
    }

    @Override
    public void shootAt(Position position){
        Random random = new Random();
        double dx = position.getX() - this.position.getX();
        double dy = position.getY() - this.position.getY();

        double maxSpreadAngle = Math.toRadians(30);

        for (int i = 0; i < numOfShells; i++) {
            double angle = (random.nextDouble() - 0.5) * 2 * maxSpreadAngle;

            double spreadDx = dx * Math.cos(angle) - dy * Math.sin(angle);
            double spreadDy = dx * Math.sin(angle) + dy * Math.cos(angle);

            Position newPos = new Position(spreadDx, spreadDy);
            bullets.add(((parent instanceof Player)
                    ? new PlayerBullet(parent.getPosition(), newPos)
                    : new EnemyBullet(parent.getPosition(), newPos)));
        }
    }
}