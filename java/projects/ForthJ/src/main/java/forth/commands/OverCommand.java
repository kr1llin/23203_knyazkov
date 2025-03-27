package forth.commands;
import forth.Command;
import forth.ConsoleInterface;
import forth.ExecutionContext;

import java.io.IOException;

public class OverCommand implements Command {
    @Override
    public void execute(ExecutionContext context) throws IOException {
        Integer top = context.getStack().pop();
        Integer second = context.getStack().pop();

        context.getStack().push(second);
        context.getStack().push(top);
        context.getStack().push(second);
    }
}
