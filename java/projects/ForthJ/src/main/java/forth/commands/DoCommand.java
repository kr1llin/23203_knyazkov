package forth.commands;

import forth.*;
import forth.Command;

import static java.lang.Math.max;
import static java.lang.Math.min;

//public class DoCommand implements Command {
//    @Override
//    public void execute(ExecutionContext context) {
//        if (context.getStack().size() > 1) {
//            int limit = context.getStack().pop();
//            int index = context.getStack().pop();
//            context.pushControlContext(index, limit, context.getCurrentTokenIndex() - 1);
//        }
//        else {
//            throw new CommandException("Stack < 2 !");
//        }
//    }
//}

public class DoCommand implements Command {
    @Override
    public void execute(ExecutionContext context) {
        if (context.getStack().size() >= 2) {
            int v1 = context.getStack().pop();
            int v2 = context.getStack().pop();
            int index = min(v1,v2);
            int limit = v1 + v2 - index;
            context.pushControlContext(index, limit, context.getCurrentTokenIndex());
        } else {
            throw new StackException("Stack underflow: required 2 elements for do");
        }
    }
}