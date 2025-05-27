import nsu.gui.MainMenu;

import javax.swing.*;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<String> peers = Arrays.asList(args).subList(0, args.length);

        SwingUtilities.invokeLater(() ->
                new MainMenu(peers));
    }
}
