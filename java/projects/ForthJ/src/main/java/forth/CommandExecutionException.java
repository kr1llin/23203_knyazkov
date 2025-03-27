package forth;

public class CommandExecutionException extends CommandException {

    public CommandExecutionException(String commandName, String message) {
        super("Error in command '" + commandName + "': " + message);
        this.commandName = commandName;
    }
    private final String commandName;

    public String getCommandName() {
        return commandName;
    }

}