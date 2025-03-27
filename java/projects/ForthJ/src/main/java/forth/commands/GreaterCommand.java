package forth.commands;
import forth.Command;
import forth.ConsoleInterface;
import forth.ExecutionContext;

import java.io.IOException;

public class GreaterCommand implements Command {
    @Override
    public void execute(ExecutionContext context) throws IOException {
        Integer v1 = context.getStack().pop();
        Integer v2 = context.getStack().pop();
        context.getStack().push((v1 > v2)? 1 : 0);
    }
}