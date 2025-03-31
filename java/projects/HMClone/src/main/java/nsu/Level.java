//package nsu;
//
//import javafx.geometry.Point2D;
//import javafx.scene.layout.Pane;
//
//import java.util.ArrayList;
//import java.util.List;
//
//public class Level {
//    private InputHandler inputHandler = new InputHandler(this);
//
//    private final double tileSize = 100;
//    private final Pane container;
//    private Player player;
//    private final List<GameObject> objects = new ArrayList<>();
//    private final double worldWidth;
//    private final double worldHeight;
//
//    public Level(Pane container, double width, double height) {
//        this.container = container;
//        this.worldWidth = width;
//        this.worldHeight = height;
//    }
//
//    public void loadFromFile(String filename) {
//        clearLevel();
//        String[] levelData = LevelLoader.loadLevel(filename);
//        createObjectsFromArray(levelData, tileSize);
//    }
//
//    private void createObjectsFromArray(String[] layout, double tileSize) {
//        for (int y = 0; y < layout.length; y++){
//            char[] row = layout[y].toCharArray();
//            for (int x = 0; x < row.length; x++){
//                Point2D position = new Point2D(x * tileSize, y * tileSize);
//                switch (row[x]) {
//                    case 'P' -> addPlayer(position);
//                    case 'E' -> addEnemy(position);
//                    case '#' -> addWall(position);
//                }
//            }
//        }
//    }
//
//    public InputHandler getInputHandler(){
//        return inputHandler;
//    }
//
//    private void addPlayer(Point2D position) {
//        player = new Player(worldWidth, worldHeight);
//        addObject(player, position);
//    }
//
//    private void addEnemy(Point2D position) {
//        Enemy enemy = new Enemy(position);
//        addObject(enemy, position);
//    }
//
//    private void addWall(Point2D position) {
//        Wall wall = new Wall(tileSize);
//        addObject(wall, position);
//    }
//
//    public void addObject(GameObject obj, Point2D position) {
//        obj.setPosition(position);
//        objects.add(obj);
//        container.getChildren().add(obj.getView());
//    }
//
//    public void update() {
//        objects.forEach(GameObject::update);
//        handleCollisions();
//        cleanupObjects();
//    }
//
//    private void handleCollisions() {
//        for (GameObject a : objects) {
//            for (GameObject b : objects) {
//                if (a != b && a.isColliding(b)) {
//                    a.handleCollision(b);
//                    b.handleCollision(a);
//                }
//            }
//        }
//    }
//    private void cleanupObjects() {
//        objects.removeIf(obj -> {
//            if (!obj.isAlive()) {
//                container.getChildren().remove(obj.getView());
//                return true;
//            }
//            return false;
//        });
//    }
//
//    private void clearLevel() {
//        objects.clear();
//        container.getChildren().clear();
//    }
//
//    public Player getPlayer() { return player; }
//
//}
