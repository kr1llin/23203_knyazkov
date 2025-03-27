package bloomfilter;

public class primeHash implements HashFunction{
    @Override
    public int hash(String s) {
        int hash = 7;
        for (int i = 0; i < s.length(); i++){
            hash = hash*31 + s.charAt(i);
        }
        return hash;
    }
}
