package forth;

public class CommandArithmeticException extends CommandException{
    public CommandArithmeticException(String commandName, String message) {
        super("Error calculating " + commandName + "': " + message);
    }

}
