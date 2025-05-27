package nsu.game.state;

import nsu.controller.EnemyController;
import nsu.controller.UserController;
import nsu.display.Camera;
import nsu.display.Display;
import nsu.entity.*;
import nsu.graphics.SpriteLibrary;
import nsu.input.Input;
import nsu.level.World;
import nsu.obj_core.*;
import nsu.obj_core.collission.CollisionBox;
import nsu.obj_core.collission.CollisionHandler;
import nsu.obj_core.listeners.EnemyListener;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.atomic.AtomicInteger;


public class LevelState extends State implements EnemyListener {
    String LEVEL0 = "/home/krillin/code/nsu/23203_knyazkov/java/projects/HMClone/src/main/resources/levels/level1.txt";
    Player player = null;
    private final List<GameObject> gameObjects = new CopyOnWriteArrayList<>();
    private final Camera camera;
    private final World world;

    private final AtomicInteger enemyCounter = new AtomicInteger(0);

    public LevelState(GameStateManager stateManager, Display display, Input input) throws IOException {
        super(stateManager, display, input);
        name = StateName.ST_LEVEL;
        world = new World(new Size(30, 30));
        camera = new Camera(display.getSize());
        loadLevelObjectsFromFile(LEVEL0);
    }

    @Override
    public void update() {
        sortObjectsByPosition();
        checkCollisions();

        List<GameObject> toRemove = new ArrayList<>();

        synchronized (gameObjects) {
            for (GameObject obj : gameObjects) {
                if (!obj.isAlive()) {
                    if (obj instanceof Enemy) {
                        enemyCounter.decrementAndGet();
                    }
                    toRemove.add(obj);
                } else {
                    obj.update(this);
                }
            }
            gameObjects.removeAll(toRemove);
        }
//        for (GameObject gameObject : gameObjects) {
//            if (gameObject.isAlive()) {
//                gameObject.update(this);
//            } else {
//                gameObjects.remove(gameObject);
//                if (gameObject instanceof Enemy) {
//                    enemyCounter.decrementAndGet();
//                }
//            }
//        }
//
        camera.update(this);
        input.clearMouseClick();
        checkGameOver();
        checkGameVictory();
    }

    private void checkGameOver() {
        if (!player.isAlive()){
            stateManager.changeState(new GameOverState(stateManager, display, input));
        }
    }

    private void checkGameVictory() {
        if (enemyCounter.get() == 0){
            stateManager.changeState(new VictoryState(stateManager, display, input));
        }
    }

    public int getEnemyCounter() {
        return enemyCounter.get();
    }
    @Override
    public void handleInput(){
//        input.clearMouseClick();
    }

    @Override
    public void enter() {

    }

    @Override
    public void exit() {

    }

//    @Override
//    public void render(){
//        display.render(this);
//    }

    private void sortObjectsByPosition() {
        List<GameObject> sortedList = new ArrayList<>(gameObjects);
        sortedList.sort(Comparator.comparing(gameObject -> gameObject.getPosition().getY()));
        gameObjects.clear();
        gameObjects.addAll(sortedList);
    }

    public World getWorld(){
        return world;
    }

    private void checkCollisions() {
        CollisionHandler handler = new CollisionHandler();
        for (int i = 0; i < gameObjects.size(); i++) {

            for (int j = i + 1; j < gameObjects.size(); j++) {
                GameObject a = gameObjects.get(i);
                GameObject b = gameObjects.get(j);

                CollisionBox aBox = a.getCollisionBox();
                CollisionBox bBox = b.getCollisionBox();

                if ((aBox != null) && (bBox != null) && a.getCollisionBox().collidesWith(b.getCollisionBox())) {
                    a.accept(handler, b);
                    b.accept(handler, a);
                }
            }
        }
    }

    void loadLevelObjectsFromFile(String path) throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
            String line;
            int row = 0;

            while ((line = reader.readLine()) != null) {
                String[] tokens = line.trim().split("");

                for (int col = 0; col < tokens.length; col++) {
                    int objID = Integer.parseInt(tokens[col]);
                    createObjectByID(objID, col, row);
                }
                row++;
            }
        }
    }

    // change to factory
    private void createObjectByID(int id, int x, int y) {
        int posX = x * SpriteLibrary.getSpriteSize();
        int posY = y * SpriteLibrary.getSpriteSize();
        GameObject objectToAdd = null;

        double centerOffsetX = SpriteLibrary.getSpriteSize() / 2.0;
        double centerOffsetY = SpriteLibrary.getSpriteSize() / 2.0;


        switch (id) {
            case 3: {
                objectToAdd = new Box(posX + centerOffsetX, posY + centerOffsetY);
                break;
            }
            case 2: {
                Enemy enemy = new Enemy(new EnemyController(), player, this);
                objectToAdd = enemy;
                objectToAdd.setPosition(new Position(posX + centerOffsetX, posY + centerOffsetY));
                gameObjects.add(enemy.getWeapon());
                enemyCounter.incrementAndGet();
                break;
            }
            case 1: {
                player = new Player(new UserController(input), camera, this);
                player.setPosition(new Position(posX + centerOffsetX, posY + centerOffsetY));
                camera.focusOn(player);
                objectToAdd = player;
                gameObjects.addAll(player.getWeapons());
                break;
            }
        }
        if (objectToAdd != null) {
            gameObjects.add(objectToAdd);
        }
    }

    public Player getPlayer() {
        return player;
    }

    public Camera getCamera() {
        return camera;
    }

    public List<GameObject> getGameObjects() {
        return gameObjects;
    }

    @Override
    public void onDeath() {
//        if (enemyCounter.get() > 0) {
//            enemyCounter.decrementAndGet();
//        }
    }
}
