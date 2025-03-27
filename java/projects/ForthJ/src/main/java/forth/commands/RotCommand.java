package forth.commands;
import forth.Command;
import forth.ConsoleInterface;
import forth.ExecutionContext;

import java.io.IOException;

public class RotCommand implements Command {
    @Override
    public void execute(ExecutionContext context) throws IOException {
        Integer a = context.getStack().pop();
        Integer b = context.getStack().pop();
        Integer c = context.getStack().pop();

        context.getStack().push(a);
        context.getStack().push(c);
        context.getStack().push(b);
    }
}