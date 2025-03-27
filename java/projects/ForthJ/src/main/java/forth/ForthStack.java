package forth;

import java.util.Stack;

public class ForthStack<Integer> extends Stack<Integer> {
        private final int maxSize;

        public ForthStack(int maxSize) {
            this.maxSize = maxSize;
        }

        @Override
        public Integer push(Integer item) {
            if (size() >= maxSize) {
                throw new StackException("Stack overflow! Max size is " + maxSize);
            }
            return super.push(item);
        }

        @Override
        public boolean add(Integer item) {
            if (size() >= maxSize) {
                throw new StackException("Stack overflow! Max size is " + maxSize);
            }
            return super.add(item);
        }
}
