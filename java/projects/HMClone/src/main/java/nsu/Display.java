package nsu;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferStrategy;

public class Display extends JFrame {
    private Canvas canvas;

    public Display(int width, int height) {
        setTitle("Hotline Miami Clone");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setResizable(false);

        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setFocusable(false);
        add(canvas);
        pack();


        canvas.createBufferStrategy(3); // to remove flickering


        setLocationRelativeTo(null); // window will pop up centered
        setVisible(true);
    }

    public void render(Game game) {
        BufferStrategy bufferStrategy = canvas.getBufferStrategy();
        Graphics graphics = bufferStrategy.getDrawGraphics(); // abstract class for drawing (but needs explicit resource release

        graphics.setColor(Color.BLACK);
        graphics.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());

        Rectangle rect = game.getRectangle();
        graphics.setColor(Color.BLUE);
        graphics.fillRect((int) rect.getX(), (int) rect.getY(), (int) rect.getWidth(), (int) rect.getHeight());

        graphics.dispose();
        bufferStrategy.show();

        Toolkit.getDefaultToolkit().sync();
    }

}