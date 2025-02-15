import java.lang.*

public class Forth {
    public static void main(String[] args) throws Exception{
        try {
            CommandFactory factory = new CommandFactory("commands.properties");
            //ForthInterpreter interpreter = new ForthInterpreter(factory);


            if (args.length == 0) {
                System.out.println("Forth Interpreter. Type 'exit' to quit.");
                interpreter.startRepl();
            } else {
                String filePath = args[0];
                interpreter.executeFromFile(filePath);
                System.out.println("Result: " + interpreter.getContext().peek());
            }
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public
}