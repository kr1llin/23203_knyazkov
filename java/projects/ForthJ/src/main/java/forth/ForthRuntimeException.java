package forth;

public class ForthRuntimeException extends RuntimeException {
    public ForthRuntimeException(String message) {
        super(message);
    }

    public ForthRuntimeException(String message, Throwable cause) {
        super(message, cause);
    }
}