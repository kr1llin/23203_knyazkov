package forth.commands;

import forth.Command;
import forth.ExecutionContext;

public class SwapCommand implements Command{
    @Override
    public void execute(ExecutionContext context) {
        int val1 = context.getStack().pop();
        int val2 = context.getStack().pop();
        context.getStack().push(val1);
        context.getStack().push(val2);
    }
}
