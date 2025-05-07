package nsu.ai.states;

import nsu.entity.Enemy;
import nsu.entity.Player;
import nsu.obj_core.Position;
import nsu.obj_core.Vector2D;

import java.util.Set;

public class Moving implements AiState{

    @Override
    public void update(Enemy enemy, Player player) {
        Set<String> blocked = enemy.getMotion().getBlockedSides();

        Vector2D direction = calculateSafeDirection(enemy, player, blocked);
        enemy.getMotion().setVector(direction);

        enemy.changeDirectionTo(player.getPosition());
//        enemy.getMotion().update(enemy.getController());
//        enemy.getPosition().apply(enemy.getMotion());
    }


    @Override
    public void maybeTransition(Enemy enemy, Player player) {
        enemy.setVelocity(0.05);
        if (enemy.isPlayerInRageRadius(player)){
            enemy.setState(new Attack());
        } else if (!enemy.isPlayerInRageRadius(player)){
            enemy.setState(new Idle());
        }
    }

    private Vector2D calculateSafeDirection(Enemy enemy, Player player, Set<String> blocked) {
        Position target = player.getPosition();
        double dx = target.getX() - enemy.getPosition().getX();
        double dy = target.getY() - enemy.getPosition().getY();

        if (blocked.contains("left") && dx < 0) dx = 0;
        if (blocked.contains("right") && dx > 0) dx = 0;
        if (blocked.contains("up") && dy < 0) dy = 0;
        if (blocked.contains("down") && dy > 0) dy = 0;

       Vector2D vec = new Vector2D(dx, dy);
       vec.normalize();
       vec.multiply(enemy.getVelocity());
       return vec;
    }
}
