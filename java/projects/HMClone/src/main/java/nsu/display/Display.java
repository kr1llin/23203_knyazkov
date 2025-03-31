package nsu.display;

import nsu.game.Game;
import nsu.input.Input;
import nsu.game.state.State;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferStrategy;

public class Display extends JFrame {
    private final Canvas canvas;
    private final RenderModule renderer;

    public Display(int width, int height, Input input) {
        setTitle("Hotline Miami Clone");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setResizable(false);

        this.renderer = new RenderModule();

        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setFocusable(false);
        add(canvas);
        addKeyListener(input);
        pack();


        canvas.createBufferStrategy(3); // to remove flickering


        setLocationRelativeTo(null); // window will pop up centered
        setVisible(true);
    }

    public void render(State state) {
        BufferStrategy bufferStrategy = canvas.getBufferStrategy();
        Graphics graphics = bufferStrategy.getDrawGraphics(); // abstract class for drawing (but needs explicit resource release

        graphics.setColor(Color.WHITE);
        graphics.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());

       renderer.render(state, graphics); // for now, it's just game objects

        graphics.dispose(); // for garbage collector
        bufferStrategy.show();

        Toolkit.getDefaultToolkit().sync();
    }

}