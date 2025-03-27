package forth.commands;
import forth.Command;
import forth.CommandExecutionException;
import forth.ConsoleInterface;
import forth.ExecutionContext;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * <h3>Define command (:)</h3>
 * <p>> gets next token as name of composite command</p>
 * <p>> while not the end or ;- builds body of composite commands</p>
 * <p>> if no corresponding ; is found - CommandExecutionException</p>
 */
public class DefineCommand implements Command {
    @Override
    public void execute(ExecutionContext context) throws IOException {
        int end = context.getTokens().size();
        int curInd = context.getCurrentTokenIndex();
        curInd++;
        if (curInd > end){
            throw new RuntimeException("No commands after ':'");
        }
        name = context.getTokens().get(curInd);
        List<String> bodyTokens = new ArrayList<String>();
        curInd++;

        boolean semicolonFound = false;
        while (curInd < end){
            String token = context.getTokens().get(curInd);
            if (token.equals(";")){
                semicolonFound = true;
                context.setCurrentTokenIndex(curInd+1);
                break;
            }
            bodyTokens.add(token);
            curInd++;
        }
        if (!semicolonFound){
            throw new CommandExecutionException(":", "No closing semicolon is found");
        }
        context.setCurrentTokenIndex(curInd);
        Command composite = new CompositeCommand(bodyTokens, context);
        context.getFactory().registerCommand(name, composite);
    }

    public String getName(){
        return name;
    }
    String name;
}
