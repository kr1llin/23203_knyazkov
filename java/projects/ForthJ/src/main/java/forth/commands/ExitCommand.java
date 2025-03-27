package forth.commands;

import forth.Command;
import forth.CommandExecutionException;
import forth.ControlContext;
import forth.ExecutionContext;

import java.util.Objects;

/* exit from loop */
//public class ExitCommand implements Command{
//        @Override
//        public void execute(ExecutionContext context) {
//            ControlContext controlContext = context.getControlContext();
//            if (controlContext == null) {
//                throw new CommandExecutionException("Exit", "No control context");
//            }
//
//            while (controlContext.getIndex() < context.getTokens().size() && !Objects.equals(context.getTokens().get(controlContext.getIndex()), "loop")){
//                controlContext.incrementIndex();
//            }
//            if (!Objects.equals(context.getTokens().get(controlContext.getIndex()), "loop")) {
//                throw new CommandExecutionException("exit", "no loop");
//            }
//        }
//    }
