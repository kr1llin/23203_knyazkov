package forth.commands;
import forth.Command;
import forth.ExecutionContext;

public class MultiplyCommand implements Command {
    @Override
    public void execute(ExecutionContext context){
        if (context.getStack().size() < 2){
            throw new RuntimeException("+ requires two elements");
        }
        int a = context.getStack().pop();
        int b = context.getStack().pop();
        context.getStack().push(a*b);
    }
}
