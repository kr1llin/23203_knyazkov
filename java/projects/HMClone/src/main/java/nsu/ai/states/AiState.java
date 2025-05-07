package nsu.ai.states;

import nsu.game.state.State;
import nsu.entity.Enemy;
import nsu.entity.Player;
import nsu.ai.AiTransition;

public interface AiState {
    void update(Enemy enemy, Player player);

    void maybeTransition(Enemy enemy, Player player);
}