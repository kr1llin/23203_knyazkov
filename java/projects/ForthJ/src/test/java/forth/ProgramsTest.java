package forth;

import org.junit.jupiter.api.Test;
import forth.CommandExecutionException;
import forth.CommandFactory;
import forth.ExecutionContext;
import forth.Interpreter;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;


import java.io.IOException;

public class ProgramsTest {
    ExecutionContext ctx;
    Interpreter interpreter;

    @BeforeEach
    void init() throws IOException {
        ctx = new ExecutionContext();
        interpreter = new Interpreter(ctx);
    }

    @Test
    public void FizzBuzz() throws IOException {
        interpreter = new Interpreter();
        assertDoesNotThrow(() -> interpreter.executeFile("/home/krillin/code/nsu/23203_knyazkov/java/projects/ForthJ/src/main/java/forth/progs/FizzBuzz"));
    }
    @Test
    public void EvenOrNot() throws IOException {
        interpreter = new Interpreter();
        assertDoesNotThrow(() -> interpreter.executeFile("/home/krillin/code/nsu/23203_knyazkov/java/projects/ForthJ/src/main/java/forth/progs/even_or_not.txt"));
    }
    @Test
    public void Fibo() throws IOException {
        interpreter = new Interpreter();
        assertDoesNotThrow(() -> interpreter.executeFile("/home/krillin/code/nsu/23203_knyazkov/java/projects/ForthJ/src/main/java/forth/progs/fibo"));
    }
}
