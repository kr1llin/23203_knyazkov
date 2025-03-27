package forth.commands;
import forth.Command;
import forth.ExecutionContext;

public class ModCommand implements Command {
    @Override
    public void execute(ExecutionContext context){
        if (context.getStack().size() < 2){
            throw new RuntimeException("% requires two elements");
        }
        int b = context.getStack().pop();
        int a = context.getStack().pop();
        context.getStack().push(a%b);
    }
}
