package forth.commands;
import forth.Command;
import forth.ConsoleInterface;
import forth.ExecutionContext;

import java.io.IOException;

public class LessCommand implements Command {
    @Override
    public void execute(ExecutionContext context) throws IOException {
        Integer v1 = context.getStack().pop();
        Integer v2 = context.getStack().pop();
        context.getStack().push((v2 < v1)? 1 : 0);
    }
}