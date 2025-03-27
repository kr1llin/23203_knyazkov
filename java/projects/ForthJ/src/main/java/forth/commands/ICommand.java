package forth.commands;

import forth.Command;
import forth.ControlContext;
import forth.ExecutionContext;
import forth.CommandExecutionException;

import java.io.IOException;

/**
 * <h3>>Index command (I)</h3>
 * <p>
 *  Pushes current index in loop (if one is currently active)
 * </p>
 */
public class ICommand implements Command{
    @Override
    public void execute(ExecutionContext context) {
        ControlContext cc = context.getControlContext();
        if (cc == null) {
            throw new CommandExecutionException("I", "No active cycle");
        }
        context.getStack().push(cc.getIndex());
    }

//    @Override
//    public void execute(ExecutionContext context) throws IOException {
//        Integer iterator = context.getControlContext().getIterator();
//        context.addToMessageBuffer(iterator.toString());
//        context.getStack().push(iterator);
//    }

}
