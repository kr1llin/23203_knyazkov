package forth.commands;

import forth.ExecutionContext;

public interface Command {
    void execute(ExecutionContext context);
}
