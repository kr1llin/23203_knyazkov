package forth;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Interpreter interpreter = new Interpreter();
        if (args.length > 0){
            interpreter.executeFile(args[0]);
        }
        else {
            interpreter.REPL();
        }
    }
}