package forth.commands;

import forth.CommandExecutionException;
import forth.ConsoleInterface;
import forth.ExecutionContext;
import forth.Interpreter;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class DotQuoteCommandTest {
    ExecutionContext ctx;
    Interpreter interpreter;

    private final PrintStream originalOut = System.out;
    private ByteArrayOutputStream outputStream; // holds data in array of bytes

    @BeforeEach
    /**
     * redirect standard output stream to test stream
     * **/
    public void setUp() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);

        outputStream = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outputStream));
    }

    @AfterEach
    /**
     * return standard output
     */
    public void reset() {
        System.setOut(originalOut);
    }

    @Test
    public void printTest(){
            ctx.setTokens(Arrays.asList(".\"", " ", "HENLO", " ", "WORLDDD", "\""));
            outputStream.reset();
            interpreter.executeOne();
            assertEquals("< HENLO WORLDDD\n", outputStream.toString());
    }

    @Test
    public void noSemicolon(){
        ctx.setTokens(Arrays.asList(".\"", " ", ";"));
        outputStream.reset();
        assertThrows(CommandExecutionException.class, ()->interpreter.executeOne());
    }
}
