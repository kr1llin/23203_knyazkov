package nsu.ai;

import nsu.entity.Enemy;
import nsu.game.state.State;

public class AiTransition {
    private String nextState;
    private AiCondition condition;

    public AiTransition(String nextState, AiCondition condition) {
        this.nextState = nextState;
        this.condition = condition;
    }

    public boolean shouldTransition(State state, Enemy enemy){
        return condition.isMet(state, enemy);
    }

    public String getNextState(){
        return nextState;
    }
}
