package forth.commands;

import forth.ExecutionContext;
import forth.Interpreter;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class IFCommandTest {
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

}