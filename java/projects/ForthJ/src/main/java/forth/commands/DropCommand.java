package forth.commands;
import forth.Command;
import forth.ConsoleInterface;
import forth.ExecutionContext;

import java.io.IOException;

public class DropCommand implements Command {
    @Override
    public void execute(ExecutionContext context) throws IOException {
        if (!context.getStack().isEmpty()) {
            context.getStack().pop();
        }
    }
}