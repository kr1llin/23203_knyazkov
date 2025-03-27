package forth.commands;

import forth.CommandExecutionException;
import forth.CommandFactory;
import forth.ExecutionContext;
import forth.Interpreter;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

class DefineCommandTest {


    ExecutionContext ctx;
    Interpreter interpreter;

    @BeforeEach
    void init() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);
    }

    @Test
    public void noSemicolon() {
        ctx.setTokens(Arrays.asList(":", " ", "testCmd", "body"));
        assertThrows(CommandExecutionException.class, () -> interpreter.executeOne());
    }

    @Test
    /* after define command index should be pointing to the next command*/
    public void registerCommandAndChangeIndex() throws IOException {
        ctx.setTokens(Arrays.asList(":", " ", "sum", "push", "5", ";", "next"));
        interpreter.executeOne();
        assertEquals(5, ctx.getCurrentTokenIndex());

        CompositeCommand cmd = (CompositeCommand) ctx.getFactory().getCommand("sum");
        assertInstanceOf(CompositeCommand.class, cmd);
//        assertEquals("sum", cmd.getName());
    }

    @Test
    public void CommandWithEmptyBody() throws IOException {
        ctx.setTokens(Arrays.asList(":", " ", "emptyCmd", ";", "5", ";", "next"));
        interpreter.executeOne();

        assertEquals(3, ctx.getCurrentTokenIndex());
        CompositeCommand cmd = (CompositeCommand) ctx.getFactory().getCommand("emptyCmd");
        assertInstanceOf(CompositeCommand.class, cmd);
        assertTrue(cmd.getBody().isEmpty());
    }

    @Test
    public void MultipleCommandUpdateState() throws IOException {
        ctx.setTokens(Arrays.asList(":", " ", "cmd1", "push", "10", " ", ";", ":"," ", "cmd2", " ", ";"));
        interpreter.executeOne();
        assertEquals(6, ctx.getCurrentTokenIndex());
        assertNotNull(ctx.getFactory().getCommand("cmd1"));
        interpreter.executeOne();
        interpreter.executeOne();

        assertEquals(ctx.getTokens().size() - 1, ctx.getCurrentTokenIndex());
        assertNotNull(ctx.getFactory().getCommand("cmd2"));
    }
}