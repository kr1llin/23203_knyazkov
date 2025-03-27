package forth;

import forth.commands.IgnoreCommand;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.util.*;


public class CommandFactory {
    private static final Logger LOGGER = LogManager.getLogger();

    /**<p><b>CommandFactory(String configFile)</b> - loads {@link Command} classes from config file</p>
     *
     * @param configFile -  contains key-value pairs,
     *                   where keys = command names and values = command class names
     */
    CommandFactory(String configFile) throws IOException {
        Properties props = new Properties();
        InputStream input = getClass().getClassLoader().getResourceAsStream(configFile);
        if (input == null) {
            throw new IOException("Config file not found: " + configFile);
        }
        props.load(input);
        props.forEach((key, value) -> commandClasses.put((String) key, loadClass((String) value)));
    }

    public static CommandFactory getInstance() throws IOException {
        if (instance == null) {
            instance = new CommandFactory("configFile.properties");
        }
        return instance;
    }

    Class<?> loadClass(String className) throws ClassNameException {
        try {
            return Class.forName(className);
        } catch (ClassNotFoundException e) {
            throw new ClassNameException(className, e);
        }
    }

    public void registerCommand(String name, Command cmd){
        commandCache.put(name, cmd);
    }

    public boolean inIgnoreList(String name){
        return ignoreList.contains(name);
    }

    /**
     * Retrieves a command instance by its name.
     *
     * @return an instance of {@link Command} corresponding to the given name,
     *         or an instance of {@link IgnoreCommand} if the name is in the ignore list,
     *         or null if no command is found for the given name
     * @throws CommandInstantiationException if there is an error during command instantiation
     */
    public Command getCommand(String name) {
        LOGGER.debug("Trying to get \"{}\" command", name);
        if (inIgnoreList(name)) {
            return new IgnoreCommand();
        }
        //if we already made object
        if (commandCache.containsKey(name)) {
            return commandCache.get(name);
        }
        Class<?> c = commandClasses.get(name);
        if (c == null){
            return null;
        }
        try {
            Command cmd = (Command) c.getDeclaredConstructor().newInstance();
            registerCommand(name, cmd);
            return cmd;
        } catch (IllegalAccessException | InstantiationException | InvocationTargetException |
                 NoSuchMethodException e) {
            LOGGER.debug("Exception getting {} command, exception is {}", name, e.toString());
            throw new CommandInstantiationException(name, e);
        }
    }

    static CommandFactory instance = null;
    private HashMap<String, Class<?>> commandClasses = new HashMap<String, Class<?>>();
    private HashMap<String, Command> commandCache = new HashMap<String, Command>();

    private final List<String> ignoreList = new ArrayList<>(Arrays.asList(" ", ";", ",", "!", "?", "\n", "\t", "\""));

}