package forth;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;

public class ConsoleInterfaceTest {
        private final PrintStream originalOut = System.out;
        private ByteArrayOutputStream outputStream; // holds data in array of bytes

        @BeforeEach
        /**
        * redirect standard output stream to test stream
        * **/
        public void setUp() {
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
        public void testPrintStack() {
            ConsoleInterface consoleInterface = new ConsoleInterface();
            Stack<Integer> stack = new Stack<>();

            consoleInterface.printStack(stack);
            assertEquals("Stack is empty\n", outputStream.toString());

            stack.push(1);
            stack.push(2);
            stack.push(3);
            outputStream.reset();
            consoleInterface.printStack(stack);
            assertEquals("Stack: 3 2 1 \n", outputStream.toString());
        }

        @Test
        public void testDisplayMessage() {
            ConsoleInterface consoleInterface = new ConsoleInterface();
            outputStream.reset();
            consoleInterface.displayMessage("Hello, World!");
            assertEquals("< Hello, World!\n", outputStream.toString());
        }
    }