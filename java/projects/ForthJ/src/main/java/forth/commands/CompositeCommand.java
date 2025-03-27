package forth.commands;
import forth.*;
import forth.Command;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * <h3>Composite command (:)</h3>
 * <p>> Saves old index </p>
 * <p>> Executes it's body (using local interpreter)</p>
 * <p>> Sets new index as old index + 1</p>
 */
public class CompositeCommand implements Command {
    CompositeCommand(List<String> body, ExecutionContext context){
        tokenBody = body;
//        commands = new ArrayList<Command>();
//        for (String token : body){
//            commands.add(context.getFactory().getCommand(token));
//        }
    }
    @Override
    public void execute(ExecutionContext context) throws IOException {
        int oldIndex = context.getCurrentTokenIndex();

        ExecutionContext newContext = new ExecutionContext();
        newContext.setCurrentTokenIndex(0);
        newContext.setTokens(tokenBody);
        newContext.setControlStack(context.getControlStack());

        ForthStack newStack = new ForthStack(Integer.MAX_VALUE);
        newStack.addAll(context.getStack());
        newContext.setStack(newStack);

        Interpreter localInterpreter = new Interpreter(newContext);
        String strBody = String.join("", tokenBody);
        localInterpreter.executeLine(strBody);
        context.setCurrentTokenIndex(oldIndex + 1);
    }

    public List<String> getBody(){
        return tokenBody;
    }

//    private int subIndex = 0;
    private List<String> tokenBody;
//    private final List<Command> commands;
}