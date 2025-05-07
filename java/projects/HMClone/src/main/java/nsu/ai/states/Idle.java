package nsu.ai.states;

import nsu.ai.AiTransition;
import nsu.entity.Enemy;
import nsu.entity.Player;
import nsu.game.state.State;

public class Idle implements AiState {

    @Override
    public void update(Enemy enemy, Player player) {
        enemy.stopMoving();
    }

    @Override
    public void maybeTransition(Enemy enemy, Player player) {
        if (enemy.isPlayerInRageRadius(player)) {
            enemy.setState(new Moving());
        }
    }
}
