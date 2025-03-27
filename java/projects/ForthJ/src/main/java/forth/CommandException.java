package forth;

public class CommandException extends ForthRuntimeException {
    public CommandException(String message) {
        super(message);
    }
    public CommandException(String message, Throwable cause) {
        super(message, cause);
    }
}

