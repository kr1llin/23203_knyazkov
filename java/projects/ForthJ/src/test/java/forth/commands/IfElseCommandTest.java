package forth.commands;

import forth.CommandExecutionException;
import forth.ExecutionContext;
import forth.Interpreter;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class IfElseCommandTest {
    ExecutionContext ctx;
    Interpreter interpreter;

    @BeforeEach
    void init() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);
    }

    @Test
    /* After if should point at first token after else */
    void ifFalseSkipsToElse() {
        ctx.setTokens(List.of("if", "10", "else", "20", "then"));
        ctx.getStack().push(0);
        interpreter.changeContext(ctx);
        interpreter.executeOne();
        assertEquals(3, ctx.getCurrentTokenIndex());
    }

    @Test
    void unbalancedIf() {
        assertThrows(CommandExecutionException.class, () -> interpreter.executeLine("0 if 100"));
    }

    @Test
    void unbalancedElse() {
        assertThrows(CommandExecutionException.class, () -> interpreter.executeLine("1 if 100 else "));
    }
}