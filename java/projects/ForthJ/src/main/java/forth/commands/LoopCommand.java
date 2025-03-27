package forth.commands;

import forth.*;
import forth.Command;

import java.io.IOException;
import java.util.List;

import static java.lang.Math.abs;


public class LoopCommand implements Command {
    @Override
    public void execute(ExecutionContext context) {
        ControlContext controlContext = context.getControlContext();
        if (controlContext == null) {
            throw new CommandExecutionException("Loop", "No control context (mb missing do?)");
        }

//        context.incrementIndex();
        controlContext.incrementIndex();
        if (controlContext.getIndex() < controlContext.getLimit()) {
            context.setCurrentTokenIndex(controlContext.getDoIndex());
        } else {
            context.popControlContext();
            context.setCurrentTokenIndex(context.getCurrentTokenIndex() + 1);
        }
    }
}


//Push controlContext to the stack
//public class LoopCommand implements Command {
//    @Override
//    public void execute(ExecutionContext context) throws IOException {
//        ControlContext loopContext = context.getControlContext();
//        if (loopContext == null){
//            throw new CommandExecutionException("LoopCommand", "Loop context is empty!");
//        }
//        Interpreter localInterpreter = new Interpreter(context);
//
//        int loopIndex = context.getCurrentTokenIndex();
//        int inc = (loopContext.getIndex() > loopContext.getLimit()) ? -1 : 1;
//        loopContext.setInc(inc);
//        if (abs(loopContext.getDoIndex() - loopIndex) > 1){
//        List<String> loopBody = context.getTokens().subList(loopContext.getDoIndex() + 1, loopIndex - 1);
//        String strBody = String.join("", loopBody);
//        localInterpreter.executeLine(strBody);
//
//        for (loopContext.setIterator(loopContext.getIndex());
//             loopContext.getIterator() != loopContext.getLimit();
//             loopContext.increment()){
//            localInterpreter.executeLine(strBody);
//        }
//        }
//        context.setCurrentTokenIndex(loopIndex + 1);
//    }
//}
