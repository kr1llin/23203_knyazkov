package forth.commands;

import forth.ExecutionContext;
import forth.Interpreter;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class StackTest {
    ExecutionContext ctx;
    Interpreter interpreter;

    @BeforeEach
    void init() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);
    }

    @Test
    void checkFullStack() throws IOException {
    
        ctx.getStack().push(10);
        ctx.getStack().push(0);
        ctx.setTokens(List.of("do"));
        DoCommand doCmd = new DoCommand();
        doCmd.execute(ctx);
        assertFalse(ctx.getControlStack().isEmpty());
        ctx.setTokens(List.of("loop"));
        LoopCommand loopCmd = new LoopCommand();
        for (int i = 0; i < 10; i++) {
            loopCmd.execute(ctx);
        }
        assertTrue(ctx.getControlStack().isEmpty());
    }

    @Test
    void stackOverflow(){

    }
}
