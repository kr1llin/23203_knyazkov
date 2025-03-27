package forth.commands;
import forth.Command;
import forth.CommandExecutionException;
import forth.ExecutionContext;

import java.util.List;

/**
 * <h3>Print string (.")</h3>
 *
 *     <p>> Perceive tokens after ." as strings to print (until ")</p>
 *     <p>> if it finds tokens that contains " - it split it into token before and after " and prints first part</p>
 *     <p>> if no corresponding " is found - CommandExecutionException</p>
 *     <p>> after executing - sets current index to index after "</p>
 *
 *
 * **/
public class DotQuoteCommand implements Command {
    @Override
    public void execute(ExecutionContext context) {
        List<String> tokens = context.getTokens();
        int currentIndex = context.getCurrentTokenIndex() + 1;
        StringBuilder message = new StringBuilder();
        boolean closingQuoteFound = false;
        int newIndex = currentIndex;

        for (; currentIndex < tokens.size(); currentIndex++) {
            String token = tokens.get(currentIndex);

            if (token.contains("\"")) {
                String[] parts = token.split("\"", 2);
                message.append(parts[0]);

                if (!parts[1].isEmpty()) {
                    throw new CommandExecutionException("DotQuote", "Bad syntax (symbols after \")");
                }

                closingQuoteFound = true;
                newIndex = currentIndex + 1;
                break;
            } else {
                message.append(token);
            }
        }

        if (!closingQuoteFound) {
            throw new CommandExecutionException("DotQuote", "No \" after .\"");
        }

        context.addToMessageBuffer(message.toString());
        context.setCurrentTokenIndex(newIndex);
    }
}