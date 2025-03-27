package forth.commands;
import forth.CommandExecutionException;
import forth.ExecutionContext;
import forth.Command;

import java.util.List;

//public class ElseCommand implements Command {
//    @Override
//    public void execute(ExecutionContext context) {
//        int offset = 1;
//        List<String> tokens = context.getTokens();
//        for (int i = context.getCurrentTokenIndex(); i < tokens.size(); i++) {
//            String token = tokens.get(i);
//            if (token.equals("if")) offset++;
//            else if (token.equals("then")) {
//                offset--;
//                if (offset == 0) {
//                    context.setCurrentTokenIndex(i + 1);
//                    break;
//                }
//            }
//        }
//    }
//}

/**
 * <h3>>Conditional logic (else)</h3>
 *
 *<p> Handles "else" block by moving the token pointer to the position after the corresponding "then"
 * Handles nested "if"/"then" blocks. Throws an exception for unbalanced blocks.</p>
 *
 * **/
public class ElseCommand implements Command {
    @Override
    public void execute(ExecutionContext context) {
        int elseDepth = 1;
        List<String> tokens = context.getTokens();
        int currentIndex = context.getCurrentTokenIndex();

        while (currentIndex < tokens.size()) {
            String token = tokens.get(currentIndex);
            if (token.equals("if")) {
                elseDepth++;
            } else if (token.equals("then")) {
                elseDepth--;
                if (elseDepth == 0) {
                    context.setCurrentTokenIndex(currentIndex + 1);
                    return;
                }
            }
            currentIndex++;
        }

        throw new CommandExecutionException("Else", "Unbalanced Else: missing then");
    }
}
