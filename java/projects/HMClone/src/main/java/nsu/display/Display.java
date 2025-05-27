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
    private final JPanel gamePanel;
    private final RenderModule renderer;
    private final Size size;
    private State currentState; // Текущее состояние для рендеринга

    public Display(int width, int height, Input input) throws IOException, FontFormatException {
        setTitle("CRAZY WIZARD GANG");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setResizable(false);

        this.renderer = new RenderModule();
        this.size = new Size(width, height);

        gamePanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                if (currentState != null) {
                    renderer.render(currentState, g, this);
                    renderer.renderUI(currentState, g, this);
                }
            }
        };

        gamePanel.setPreferredSize(new Dimension(width, height));
        gamePanel.setDoubleBuffered(true);
        gamePanel.setFocusable(true);

        gamePanel.addMouseListener(input);
        gamePanel.addMouseMotionListener(input);
        gamePanel.addKeyListener(input);

        add(gamePanel);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);

        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        Font customFont = Font.createFont(Font.TRUETYPE_FONT,
                new File("/home/krillin/code/nsu/23203_knyazkov/java/projects/HMClone/src/main/resources/fonts/ARCADECLASSIC.TTF"));
        ge.registerFont(customFont);
    }

    public void render(State state) {
        this.currentState = state;
        gamePanel.repaint();
    }

    public Size getSize() {
        return size;
    }
}