package bloomfilter;

import java.util.ArrayList;

import static jdk.internal.org.jline.utils.Colors.s;

interface MyHash{
    int hash(String s);
}

public class BloomFilter {
    public int maybeContains(String s){
        int isContains = 1;
        for (MyHash h : hashFunctions){
            isContains &= h.hash(s);
        }
        return isContains;
    }

    public void add(String s){
        if (maybeContains(s) == 1){
            System.out.println("Maybe contains");
        }
        else{
            for (h : hashFunctions){
                bits[h(s)] = 1;
            }
        }
    }

    int hashWithParams(String s, int a, int p ){
        int result = 0;
        for (char c : s){
            result += ((result + c) * a) % p;
        }
        return result;
    }

    private final int bitsNum = 96;
    private int[] bits = new int[bitsNum / 32];
    private final int hashFunctionsNumber = 3;

    private final int[] hardcodedPrimes = new int[hashFunctionsNumber];
    {
        hardcodedPrimes[0] = 3;
        hardcodedPrimes[1] = 5;
        hardcodedPrimes[2] = 7;
    }
    ArrayList<MyHash> hashFunctions = new ArrayList<MyHash>();
    {
        for (int i = 0; i < hashFunctionsNumber; i++){
            final int x = hardcodedPrimes[i];
            hashFunctions.add((s) -> {return hashWithParams(s, x, bitsNum);});
//            hashFunctions.add(new MyHash() {
//                    @Override
//                    public int hash (String s) {
//                        return hashWithParams(s, x, bitsNum);
//                    }
//            });

        }
    }
}
