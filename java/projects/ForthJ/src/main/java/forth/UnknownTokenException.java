package forth;

public class UnknownTokenException extends ForthRuntimeException {

    public UnknownTokenException(String token, int position) {
        super("Unknown token '" + token + "' at position " + position);
        this.token = token;
        this.position = position;
    }
    private String token;
    private int position;
}
