package forth.commands;

import forth.CommandExecutionException;
import forth.ExecutionContext;
import forth.Interpreter;
import forth.StackException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.math.BigInteger;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class StackTest {
    ExecutionContext ctx;
    Interpreter interpreter;

    @BeforeEach
    void init() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);
    }

    @Test
    void bigNumber() {
        assertDoesNotThrow(() -> interpreter.executeLine("2147483647"));
        assertDoesNotThrow(() -> interpreter.executeLine("-2147483648"));

        assertThrows(CommandExecutionException.class,
                () -> interpreter.executeLine("2147483648"));

        assertThrows(CommandExecutionException.class,
                () -> interpreter.executeLine("-2147483649"));

        assertThrows(NumberFormatException.class,
                () -> interpreter.executeLine("12ab"));
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
//        for (long i = 0; i < Integer.MAX_VALUE; i++){
//            ctx.getStack().push(10);
//        }
//        assertThrows(StackException.class, () -> ctx.getStack().push(10));
    }
}
