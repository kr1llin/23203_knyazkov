package forth;

public class CommandInstantiationException extends CommandException {
    public CommandInstantiationException(String commandName, Throwable cause) {
        super("Failed to instantiate command: " + commandName, cause);
    }
}


