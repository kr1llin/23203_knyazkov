package nsu.game.state;

import nsu.controller.UserController;
import nsu.entity.Bullet;
import nsu.entity.GameObject;
import nsu.entity.MovingEntity;
import nsu.entity.Player;
import nsu.input.Input;
import nsu.level.Level;
import nsu.obj_core.Size;

import java.util.ArrayList;
import java.util.List;

public class LevelState extends State{
    public LevelState(Size windowSize, Input input) {
        super(windowSize, input);
        Player player = new Player(new UserController(input), spriteLibrary, camera);
        gameObjects.add(player);
        stateLevel = new Level(new Size(30, 30), spriteLibrary); // should match the size of GAME_WORLD
        camera.focusOn(player);
    }

    @Override
    public void update() {
        super.update();
        List<GameObject> bulletsToAdd = new ArrayList<>();
        gameObjects.forEach(gameObject -> {
            if (gameObject.isShooting()){
                Bullet bullet = new Bullet(gameObject.getPosition());
                bullet.changeDirectionTo(camera.screenToWorld(input.getMousePosition()));
                bulletsToAdd.add(bullet);
                gameObject.stopShooting();
            }
        });
        gameObjects.addAll(bulletsToAdd);
    }
}
