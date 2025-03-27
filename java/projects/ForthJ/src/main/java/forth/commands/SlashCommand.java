package forth.commands;
import forth.Command;
import forth.CommandArithmeticException;
import forth.ExecutionContext;
import forth.ForthRuntimeException;

import java.io.IOException;

public class SlashCommand implements Command {
    @Override
    public void execute(ExecutionContext context) throws ForthRuntimeException {
        if (context.getStack().size() < 2){
            throw new ForthRuntimeException("+ requires two elements");
        }
        int b = context.getStack().pop();
        int a = context.getStack().pop();
        if (b != 0) {
            context.getStack().push(a / b);
        }
        else {
            throw new CommandArithmeticException("/", "Div by zero!\n");
        }
    }
}
