package nsu.display;

import nsu.entity.Player;
import nsu.entity.weapons.Weapon;
import nsu.game.state.*;
import nsu.graphics.AnimationManager;
import nsu.graphics.SpriteLibrary;
import nsu.level.Tile;
import nsu.level.World;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;

public class RenderModule {
    private SpriteLibrary spriteLibrary;
    private AnimationManager animationManager;

    public RenderModule(){
        spriteLibrary = new SpriteLibrary();
//        animationManager = new AnimationManager();
    }

    public void render(State state, Graphics graphics, JPanel canvas) {
        Graphics2D g2d = (Graphics2D) graphics;
        AffineTransform originalTransform = g2d.getTransform();


        State finalState = state;
        switch (state.getName()){
            case ST_LEVEL -> {
                renderLevel((LevelState)state, graphics);

                ((LevelState)state).getGameObjects().forEach(gameObject -> {
                    if (gameObject.isAlive()) {
                        AffineTransform transform = gameObject.getAffineTransform((LevelState) finalState, gameObject);
                        g2d.setTransform(transform);
                        g2d.drawImage(spriteLibrary.getSprite(gameObject.getClass()), 0, 0, null);
                        g2d.setTransform(originalTransform);
                    }
                });
            }
            case ST_GAMEOVER -> {
                graphics.setColor(Color.BLACK);
                graphics.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
            }
        }

    }

    private void renderLevel(LevelState state, Graphics graphics) {
        World stateLevel = state.getWorld();

        Tile[][] tiles = stateLevel.getTiles();
        Camera camera = state.getCamera();

        for (int x = 0; x < tiles.length; x++) {
            for (int y = 0; y < tiles[0].length; y++) {
                graphics.drawImage(
                        spriteLibrary.getSprite(tiles[x][y].getClass()),
                        x * SpriteLibrary.getSpriteSize() - camera.getPosition().intX(),
                        y * SpriteLibrary.getSpriteSize() - camera.getPosition().intY(),
                        null
                );
            }
        }
    }

    // :)
    void renderUI(State state, Graphics g, JPanel canvas){
        if (state instanceof LevelState levelState){
            Player player = levelState.getPlayer();
            g.setColor(Color.BLACK);
            g.setFont(new Font("ArcadeClassic", Font.BOLD, 35));
            g.drawString("Health_" + player.getHealth(), 20, 60);

            Weapon weapon = player.getCurrentWeapon();
            if (weapon != null) {
                g.drawString("Weapon_" + weapon.getClass().getSimpleName(), 20, 90);
            }

            g.drawString("Enemies_" + ((LevelState) state).getEnemyCounter(), 20, 120);

            g.setColor(Color.WHITE);
            g.setFont(new Font("ArcadeClassic", Font.BOLD, 35));
            g.drawString("Health_" + player.getHealth(), 25, 50);

            if (weapon != null) {
                g.drawString("Weapon_" + weapon.getClass().getSimpleName(), 25, 80);
            }

            g.drawString("Enemies_" + ((LevelState) state).getEnemyCounter(), 25, 110);

        } else if (state instanceof GameOverState) {
            Graphics2D g2d = (Graphics2D) g;
            Composite originalComposite = g2d.getComposite();

            g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.7f));
            g2d.setColor(Color.BLACK);
            g2d.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
            g2d.setComposite(originalComposite);

            g2d.setColor(Color.RED);
            g2d.setFont(new Font("ArcadeClassic", Font.BOLD, 72));

            String gameOverText = "GAME OVER";
            FontMetrics fm = g2d.getFontMetrics();
            int textWidth = fm.stringWidth(gameOverText);

            int x = (canvas.getWidth() - textWidth) / 2;
            int y = canvas.getHeight() / 2;

            g2d.drawString(gameOverText, x, y);

            g2d.setFont(new Font("ArcadeClassic", Font.PLAIN, 36));
            String restartText = "Press  BACKSPACE  to  restart";
            textWidth = g2d.getFontMetrics().stringWidth(restartText);
            x = (canvas.getWidth() - textWidth) / 2;
            y += 60;

            g2d.drawString(restartText, x, y);
        }
        else if (state instanceof VictoryState) {
            Graphics2D g2d = (Graphics2D) g;
            Composite originalComposite = g2d.getComposite();

            g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.7f));
            g2d.setColor(Color.WHITE);
            g2d.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
            g2d.setComposite(originalComposite);

            g2d.setColor(Color.GREEN);
            g2d.setFont(new Font("ArcadeClassic", Font.BOLD, 72));

            String gameOverText = "YOU WON";
            FontMetrics fm = g2d.getFontMetrics();
            int textWidth = fm.stringWidth(gameOverText);

            int x = (canvas.getWidth() - textWidth) / 2;
            int y = canvas.getHeight() / 2;

            g2d.drawString(gameOverText, x, y);

            g2d.setFont(new Font("ArcadeClassic", Font.PLAIN, 36));
            String restartText = "Press  BACKSPACE  to  restart";
            textWidth = g2d.getFontMetrics().stringWidth(restartText);
            x = (canvas.getWidth() - textWidth) / 2;
            y += 60;

            g2d.drawString(restartText, x, y);
        }
    }
}
