package nsu.ai.states;

import nsu.entity.Enemy;
import nsu.entity.Player;

public class Attack implements AiState{
    private int attackCooldown = 40;
    private int timeSinceLastAttack = 0;

    @Override
    public void update(Enemy enemy, Player player) {
        enemy.changeDirectionTo(player.getPosition());

        timeSinceLastAttack++;

        if(timeSinceLastAttack >= attackCooldown){
            enemy.shootAt(player.getPosition());
            timeSinceLastAttack = 0;
        }
    }

    @Override
    public void maybeTransition(Enemy enemy, Player player) {
        if (!enemy.isPlayerInAttackRange(player)){
            enemy.setVelocity(1);
            enemy.setState(new Moving());
        }
        if (!player.isAlive()){
            enemy.setState(new Idle());
        }

    }
}
