package forth.commands;

import forth.CommandExecutionException;
import forth.ExecutionContext;
import forth.Command;

public class DotCommand implements Command {
    @Override
    public void execute(ExecutionContext context) {
        if (context.getStack().isEmpty()) {
            throw new CommandExecutionException(".", "Stack is empty");
        }
        int value = context.getStack().pop();
        context.addToMessageBuffer(value + " ");
    }
}