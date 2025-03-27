package forth;

public class ClassNameException extends RuntimeException {
    public ClassNameException(String className, Throwable cause) {
        super("Command class not found: " + className, cause);
    }
}