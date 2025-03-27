package forth.commands;

import forth.Command;
import forth.CommandExecutionException;
import forth.ExecutionContext;

import java.util.List;
//
//public class IFCommand implements Command {
//    @Override
//    public void execute(ExecutionContext context) {
//        int condition = context.getStack().pop();
//        if (condition == 0) {
//            int offset = 1;
//            List<String> tokens = context.getTokens();
//            for (int i = context.getCurrentTokenIndex(); i < tokens.size(); i++) {
//                String token = tokens.get(i);
//                if (token.equals("if")) offset++;
//                else if (token.equals("then")) {
//                    offset--;
//                    if (offset == 0) {
//                        context.setCurrentTokenIndex(i + 1);
//                        break;
//                    }
//                } else if (token.equals("else") && offset == 1) {
//                    context.setCurrentTokenIndex(i + 1);
//                    break;
//                }
//            }
//        }
//        // continue execution
//    }
//}
//
//public class IFCommand implements Command {
//    @Override
//    public void execute(ExecutionContext context) {
//        int condition = context.getStack().pop();
//        if (condition == 0) {
//            int ifDepth = 1;
//            List<String> tokens = context.getTokens();
//            int currentIndex = context.getCurrentTokenIndex();
//
//            while (currentIndex < tokens.size()) {
//                String token = tokens.get(currentIndex);
//                if (token.equals("if")) {
//                    ifDepth++;
//                } else if (token.equals("else") && ifDepth == 1) {
//                    context.setCurrentTokenIndex(currentIndex + 1);
//                    return;
//                } else if (token.equals("then")) {
//                    ifDepth--;
//                    if (ifDepth == 0) {
//                        context.setCurrentTokenIndex(currentIndex + 1);
//                        return;
//                    }
//                }
//                currentIndex++;
//            }
//
//            throw new CommandExecutionException("If", "Unbalanced If: missing then or else");
//        }
//    }
//}


/**
 * <h3>>Conditional logic (if)</h3>
 * <p>
 * If the popped int is 0, this method searches for the corresponding
 * "else" or "then" token to skip the current "if" block.
 * It also handles nested "if"'s  (by tracking the depth of "if" and "then" tokens: if = ++depth, then = --depth)
 * If no matching "else" or "then" is found, a <b>>CommandExecutionException</b> is thrown.
 * </p>
 */
public class IFCommand implements Command {
    @Override
    public void execute(ExecutionContext context) {
        int condition = context.getStack().pop();
        if (condition == 0) {
            int ifDepth = 1;
            List<String> tokens = context.getTokens();
            int currentIndex = context.getCurrentTokenIndex();

            while (currentIndex < tokens.size()) {
                String token = tokens.get(currentIndex);
                if (token.equalsIgnoreCase("if")) {
                    ifDepth++;
                } else if (token.equalsIgnoreCase("else") && ifDepth == 1) {
                    context.setCurrentTokenIndex(currentIndex + 1);
                    return;
                } else if (token.equalsIgnoreCase("then")) {
                    ifDepth--;
                    if (ifDepth == 0) {
                        context.setCurrentTokenIndex(currentIndex + 1);
                        return;
                    }
                }
                currentIndex++;
            }

            throw new CommandExecutionException("If", "Unbalanced If: missing then or else");
        }
    }
}
