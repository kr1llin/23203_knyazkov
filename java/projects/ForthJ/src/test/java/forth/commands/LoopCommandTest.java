package forth.commands;//package forth;
import forth.CommandExecutionException;
import forth.ExecutionContext;
import forth.Interpreter;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class LoopCommandTest {
    ExecutionContext ctx;
    Interpreter interpreter;

    @BeforeEach
    void init() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);
    }

    @Test
        /* Do "do-loop" commands manipulate with ControlContext? */
    void checkControlContext() throws IOException {
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
    /* add lots of 1 in one loop and drop them in another */
    void lotOfLoops() throws IOException {
        interpreter.executeLine("100000 0 do 1 loop");
        interpreter.executeLine("100000 0 do drop loop");
        assertTrue(ctx.getStack().isEmpty());

    }
    @Test
    void loopThrowsExceptionWhenNoControlContext() {
        ctx.setTokens(List.of("loop"));
        LoopCommand loopCmd = new LoopCommand();
        assertThrows(CommandExecutionException.class, () -> loopCmd.execute(ctx));
    }

    @Test
    /* The inner loop should add 3 new control contexts */
    void nestedLoops() throws IOException {
        interpreter.executeLine("2 0 do 2 0 do");

        assertEquals(2, interpreter.getContext().getControlStack().size());
//
//        new LoopCommand().execute(interpreter.getContext());
//        assertEquals(1, interpreter.getContext().getControlStack().size());
//
//        new LoopCommand().execute(interpreter.getContext());
//        assertEquals(3, interpreter.getContext().getControlStack().size());

    }
}
