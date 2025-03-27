package forth;

import java.io.IOException;

public interface Command {
    void execute(ExecutionContext context) throws IOException, ForthRuntimeException;
}
