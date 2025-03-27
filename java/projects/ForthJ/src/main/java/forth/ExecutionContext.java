package forth;

import javax.naming.ldap.Control;
import java.io.IOException;
import java.util.*;

public class ExecutionContext {

    public ExecutionContext() throws IOException {
    }

    public Stack<Integer> getStack() {
        return stack;
    }

    public void setTokens(List<String> tokens) {
        this.tokens = tokens;
    }

    public void setStack(ForthStack other){stack = other;}

    public List<String> getTokens() {
        return tokens;
    }
    public void addToken(String tkn) {
        tokens.add(tkn);
    }
    public CommandFactory getFactory() {return factory;}

    public int getCurrentTokenIndex() {
        return currentTokenIndex;
    }

    public void setCurrentTokenIndex(int index) {
        this.currentTokenIndex = index;
    }

    public ControlContext getControlContext() {
        if (controlStack.isEmpty()){
            return null;
        }
        return controlStack.peek();
    }
    public ControlContext popControlContext() {
        if (controlStack.isEmpty()){
            return null;
        }
        return controlStack.pop();
    }

    public Stack<ControlContext> getControlStack(){
        return controlStack;
    }
    public void setControlStack(Stack<ControlContext> stack){
        controlStack = stack;
    }
    public String getMessageBuffer(){ return messageBuffer.toString(); }

    public void addToMessageBuffer(String str) {
        messageBuffer.append(str);
    }
    public void clearMessageBuffer(){
        messageBuffer.setLength(0);
    }

    public void incrementIndex() {
        currentTokenIndex++;
    }

    /**
     * @param i   - index
     * @param l   - limit
     * @param doI - doIndex
     */
    public void pushControlContext(int i, int l, int doI) {
        controlStack.push(new ControlContext(i, l, doI));
    }

    private StringBuilder messageBuffer = new StringBuilder();
    private ForthStack stack = new ForthStack<Integer>(Integer.MAX_VALUE);
    private List<String> tokens = new ArrayList<String>(); // tokens for current execution
    private int currentTokenIndex;
    private Stack<ControlContext> controlStack = new Stack<ControlContext>();

    private final CommandFactory factory = CommandFactory.getInstance();


}
