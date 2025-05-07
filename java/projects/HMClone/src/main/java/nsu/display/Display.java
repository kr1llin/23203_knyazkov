package nsu.display;

import nsu.entity.Player;
import nsu.entity.weapons.Weapon;
import nsu.game.Game;
import nsu.game.state.LevelState;
import nsu.input.Input;
import nsu.game.state.State;
import nsu.obj_core.Size;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferStrategy;
import java.io.File;
import java.io.IOException;

public class Display extends JFrame {
    private final Canvas canvas;
    private final RenderModule renderer;
    private final Size size;

    public Display(int width, int height, Input input) throws IOException, FontFormatException {
        setTitle("CRAZY WIZARD GANG");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setResizable(false);

        this.renderer = new RenderModule();

        size = new Size(width, height);
        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setFocusable(false);
        canvas.addMouseListener(input);
        canvas.addMouseMotionListener(input);

        add(canvas);
        addKeyListener(input);
        pack();

        canvas.createBufferStrategy(3); // to remove flickering

        setLocationRelativeTo(null); // window will pop up centered
        setVisible(true);

        GraphicsEnvironment ge =
                GraphicsEnvironment.getLocalGraphicsEnvironment();
        Font customFont = Font.createFont(Font.TRUETYPE_FONT, new File("/home/krillin/code/nsu/23203_knyazkov/java/projects/HMClone/src/main/resources/fonts/ARCADECLASSIC.TTF"));
        ge.registerFont(customFont);
    }

    public void render(State state) {
        BufferStrategy bufferStrategy = canvas.getBufferStrategy();
        Graphics graphics = bufferStrategy.getDrawGraphics(); // abstract class for drawing (but needs explicit resource release

        graphics.setColor(Color.WHITE);
        graphics.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());

        renderer.render(state, graphics, canvas); // for now, it's just game objects
        renderer.renderUI(state, graphics, canvas);

        graphics.dispose(); // for garbage collector
        bufferStrategy.show();

        Toolkit.getDefaultToolkit().sync();
    }

    public Size getSize(){
        return size;
    }
}

