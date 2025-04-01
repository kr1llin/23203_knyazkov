package forth;
//
//import org.junit.jupiter.api.Test;
//
//import static org.junit.jupiter.api.Assertions.*;
//
//class InterpreterTest {
//
//    @Test
//    void executeLine() {
//    }
//
//    @Test
//    void REPL() {
//    }
//
//    @Test
//    void executeFile() {
//    }
//}

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

import forth.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.junit.jupiter.api.io.TempDir;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.io.File;
import java.io.FileWriter;
import java.util.Arrays;
import java.util.Collections;
import java.util.Stack;

class InterpreterTest {

    ExecutionContext ctx;
    Interpreter interpreter;

    @BeforeEach
    void init() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);
    }

    @Test
    void pushNumberTokenToStack() {
        ctx.setTokens(Arrays.asList("7777"));
        interpreter.executeOne();
        assertEquals(7777, ctx.getStack().pop());
    }

    @Test
    void invalidCommandThrows() {
        ctx.setTokens(Arrays.asList("WRONG"));
        assertThrows(Exception.class, () -> interpreter.executeOne());
    }

    @Test
    void lotOfTokens() {
        int operationsCount = 10000;
        StringBuilder expression = new StringBuilder("1");

        for (int i = 0; i < operationsCount; i++) {
            expression.append(" 1 *");
        }

        interpreter.executeLine(expression.toString());

        assertEquals(1, ctx.getStack().pop());
    }

    @Test
    void executeFromFile() throws IOException {
        Path file = Files.createTempFile("test", ".txt");
        Files.writeString(file, "100 50 -");

        interpreter.executeFile(file.toString());
        assertEquals(50, ctx.getStack().pop());

        Files.delete(file);
    }

    @Test
    void readFileAsString() throws IOException {
        Path file = Files.createTempFile("test", ".txt");
        Files.writeString(file, "TEST TEST TEST");

        String content = interpreter.readFileAsString(file.toString());
        assertEquals("TEST TEST TEST", content);

        Files.delete(file);
    }

    @Test
    void MessageBufferTest() {
        ctx.addToMessageBuffer("Message");
        ctx.setTokens(Collections.emptyList());

        interpreter.executeOne();

        assertTrue(ctx.getMessageBuffer().isEmpty());
    }

}