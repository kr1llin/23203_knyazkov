package forth;

import forth.commands.IgnoreCommand;
import forth.ClassNameException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import java.io.IOException;

class CommandFactoryTest {

    CommandFactory factory;


    @BeforeEach
    void init() throws IOException {
        factory = new CommandFactory("configFile.properties");
    }

    @Test
    void testConfigFileNotFound() {
        assertThrows(IOException.class, () -> new CommandFactory("WRONG PATH"));
    }

    @Test
    void IgnoreList() {
        assertTrue(factory.getCommand(" ") instanceof IgnoreCommand);
        assertTrue(factory.getCommand(";") instanceof IgnoreCommand);
    }

    @Test
    void ValidClass()  {
        Class<?> clazz = factory.loadClass("java.lang.String");
        assertEquals(String.class, clazz);
    }
    @Test
    void testLoadValidClass()  {
        Class<?> clazz = factory.loadClass("forth.commands.IgnoreCommand");
        assertEquals(IgnoreCommand.class, clazz);
    }


    @Test
    void getCommand() throws IOException {
        assertNull(factory.getCommand("WRONG"));
    }

    @Test
    void loadWrongClass()  {
        assertThrowsExactly(ClassNameException.class, () -> factory.loadClass("WRONG"));
    }

    // if wrong command
}