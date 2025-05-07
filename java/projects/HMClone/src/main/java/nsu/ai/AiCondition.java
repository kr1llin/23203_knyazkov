package nsu.ai;

import nsu.entity.Enemy;
import nsu.game.state.State;

public interface AiCondition {
    boolean isMet(State state, Enemy currentEnemy);
}
