package forth.commands;

import forth.ExecutionContext;
import forth.Command;

public class CrCommand implements Command {
    @Override
    public void execute(ExecutionContext context) {
        context.addToMessageBuffer("\n");
    }
}
