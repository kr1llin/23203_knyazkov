package forth.commands;

import forth.Command;
import forth.ExecutionContext;

public class DupCommand implements Command{
    @Override
    public void execute(ExecutionContext context){
        int top = context.getStack().peek();
        context.getStack().push(top);
    }
}
