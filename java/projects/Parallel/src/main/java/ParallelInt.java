import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;




public class ParallelInt {

    public static MyLock getLock() {
        return lock;
    }

    // secret knowlege
    class MyLock {
        AtomicBoolean flag = new AtomicBoolean(false);
    
        void lock(){
            // while (flag.get() != false);
            while (false == flag.compareAndSet(false, true));
        }
    
        void unlock(){
            flag.set(false);
        }
    
        // boolean isLocked(){
        //     return false;
        // }
        // boolean tryLock(){
        //     return false;
        // }
    }

    
    static class MyRunnable implements Runnable{
        @Override
        public void run() {

            try {
                System.out.println("Hello from thread");
            } catch (Exception e) {
            }
            long id = Thread.currentThread().threadId();
//            System.out.println("Hello from thread id  = " + id);

            for (int i = 0; i < NUM_ITERATIONS; ++i){
                //critical section
//                synchronized (monitor) {
//                    X++;
//                }
                lock.lock();
                X++;
                lock.unlock();
                // ATOMIC_X.incrementAndGet();
            }
        }
    }

    static int X = 0;
    static final int NUM_THREADS = 1000;
    static final int NUM_ITERATIONS = 100000;
    static final Object monitor = new Object();
    static final AtomicInteger ATOMIC_X = new AtomicInteger();
    static final MyLock lock = new MyLock();
    
    public static void main(String[] args) throws Exception{
        
        ArrayList<Thread> threads = new ArrayList<>();


        long timestamp = System.currentTimeMillis();
        for (int i = 0; i < NUM_THREADS; i++){
            Thread t = new Thread(new MyRunnable());
            threads.add(t);
        }
        for (int i = 0; i < NUM_THREADS; i++){
            threads.get(i).start();
        }

        for (int i = 0; i < NUM_THREADS; i++){
            threads.get(i).join();
        }
        long time = System.currentTimeMillis() - timestamp;

//        t.join();


        System.out.println("RESULTED ATOMIC X = " + ATOMIC_X.get());
        System.out.println("TIME = " + time);
    }
}


// volatile - если переменная будет изменена, то результат будет виден всем потокам (модель памяти жаба)
//
// 
//
//
//
