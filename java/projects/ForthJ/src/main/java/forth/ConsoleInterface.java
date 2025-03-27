package forth;

import java.io.Closeable;
import java.io.IOException;
import java.util.Scanner;
import java.util.Stack;

public class ConsoleInterface implements AutoCloseable, Closeable, UserInterface {

//    public static ConsoleInterface getInstance() throws IOException {
//        if (instance == null) {
//            instance = new ConsoleInterface();
//        }
//        return instance;
//    }

    @Override
    public void printStack(Stack<Integer> stack) {
        if (stack.isEmpty()) {
            System.out.println("Stack is empty");
            return;
        }

        System.out.print("Stack: ");
        for (int i = stack.size() - 1; i >= 0; i--) {
            System.out.print(stack.get(i) + " ");
        }
        System.out.println();
    }

    @Override
    public void displayMessage(String message) {
            System.out.println("< " + message);
    }

    public ConsoleInterface() {
        this.scanner = new Scanner(System.in);
    }
    public String readLine() {
        System.out.print("> ");
        return scanner.nextLine().trim();
    }
    ;
    private final Scanner scanner;

    @Override
    public void close() throws IOException {
        scanner.close();
    }
}
