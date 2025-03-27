package forth;

public class ControlContext {

    ControlContext(int i, int l, int doI) {
        index = i;
        limit = l;
        doIndex = doI;
    }

    public void incrementIndex(){
        index++;
    }
    public int getIndex() {
        return index;
    }
    public int getLimit(){
        return limit;
    }
    public int getDoIndex(){
        return doIndex;
    }

    private int index, limit, doIndex;
}
