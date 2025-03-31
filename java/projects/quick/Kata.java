
import java.util.Arrays;
import java.util.stream.Collectors;

public class  Kata {
    // public static StringBuilder reverseWord(final String word){
    //     StringBuilder reversed = new StringBuilder(word);
    //     for (int i = 0; i < word.length(); i++){
    //         reversed.setCharAt(i, word.charAt(word.length() - 1 - i));
    //     }
    //     return reversed;
    // }

    // public static String reverseWords(final String original){
    //     int lastWhitespace = 0;
    //     StringBuilder reversed = new StringBuilder();
    //     for (int i = 0; i < original.length(); i++){
    //         if (original.charAt(i) == ' '){
    //             reversed.append(reverseWord(original.substring(lastWhitespace, i)));
    //             reversed.append(' ');
    //             lastWhitespace = i;
    //         }
    //     }
    //     reversed.append(reverseWord(original.substring(lastWhitespace, original.length())));
    //     return reversed.toString();
    // }

    public static String reverseWords(final String original){
        return Arrays.stream(original.split("(?<=\\\\s)|(?=\\\\s+)"))
        .map(str -> new StringBuilder(str).reverse().toString())
        .collect(Collectors.joining());
    }

    

    public static void main(String[] args){
        System.out.println(reverseWords("Hello world!"));
    }
}
