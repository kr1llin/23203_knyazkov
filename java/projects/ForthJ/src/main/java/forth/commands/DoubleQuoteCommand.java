//package forth.commands;
//
//import forth.Command;
//import forth.ExecutionContext;
//
//import java.util.List;
//
//public class DoubleQuoteCommand implements Command {
//    @Override
//    public void execute(ExecutionContext context) {
//        context.getDotQuoteContext().setEndIndex(context.getCurrentTokenIndex());
//        List<String> stringList = context.getTokens().subList(context.getDotQuoteContext().getBeginIndex() + 1,
//                context.getDotQuoteContext().getEndIndex() - 1);
//        String message = String.join(" ",stringList);
//        context.addToMessageBuffer(message);
//    }
//}