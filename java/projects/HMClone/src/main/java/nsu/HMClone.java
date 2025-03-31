package nsu;

import nsu.game.Game;
import nsu.game.GameLoop;


/*
TODO:
    Rotation to mouse
    Camera (and add big level)
    Level + Collision (add health bars to it)
    Enemies
    Weapons types
    Simple AI (aggression area)
    Dialogs
 */

public class HMClone {
    public static void main(String[] args){
        new Thread(new GameLoop(new Game(1000, 1000))).start();
    }
}









//
//
//public class HMClone extends GameApplication {
//    private final int WORLD_WIDTH = 2000;
//    private final int WORLD_HEIGHT = 2000;
//        private static final Color GRID_COLOR = Color.rgb(200, 200, 200, 0.3);
//    private static final double GRID_MAJOR_LINE_WIDTH = 0.7;
//    private static final double GRID_MINOR_LINE_WIDTH = 0.3;
//
//    private Group createGrid() {
//        Group gridGroup = new Group();
//
//        for (double x = 0; x <= WORLD_WIDTH; x += 50) {
//            Line line = new Line(x, 0, x, WORLD_HEIGHT);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MINOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        for (double y = 0; y <= WORLD_HEIGHT; y += 50) {
//            Line line = new Line(0, y, WORLD_WIDTH, y);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MINOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        for (double x = 0; x <= WORLD_WIDTH; x += 100) {
//            Line line = new Line(x, 0, x, WORLD_HEIGHT);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MAJOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        for (double y = 0; y <= WORLD_HEIGHT; y += 100) {
//            Line line = new Line(0, y, WORLD_WIDTH, y);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MAJOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        return gridGroup;
//    }
//
//    @Override
//    protected void initSettings(GameSettings settings) {
//        settings.setWidth(WORLD_WIDTH);
//        settings.setHeight(WORLD_HEIGHT);
//        settings.setTitle("Hotline Miami Clone");
//    }
//
//    @Override
//    protected void initInput() {
//        // while a key is being pressed
//        FXGL.onKey(KeyCode.D, () -> {
//           player.translateX(5);
//            FXGL.inc("pixelMoved", +5);
//        });
//        FXGL.onKey(KeyCode.A, () -> {
//            player.translateX(-5);
//            FXGL.inc("pixelMoved", -5);
//        });
//    }
//
//    @Override
//    protected void initUI() {
//        Text textPixels = new Text();
//        textPixels.setTranslateX(50);
//        textPixels.setTranslateY(100);
//        textPixels.textProperty().bind(FXGL.getWorldProperties().
//                intProperty("pixelMoved").asString());
//        FXGL.getGameScene().addUINode(textPixels);
//    }
//
//    @Override
//    protected void initGameVars(Map<String, Object> vars){
//        vars.put("pixelMoved", 0);
//    }
//
//    private Entity player;
//    @Override
//    protected void initGame() {
//        Group grid = createGrid();
//        getGameScene().addUINode(grid);
//        player = FXGL.entityBuilder()
//                .at(300, 300)
//                .view(new Rectangle(25, 25, Color.AQUA))
//                .buildAndAttach();
//    }
//
//    public static void main(String[] args) {
//        launch(args);
//    }
//}


 //Change level = change scene
// BAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD
//public class HMClone extends Application {
//
//    private final double WORLD_WIDTH = 2000;
//    private final double WORLD_HEIGHT = 2000;
//
//    private static final Color GRID_COLOR = Color.rgb(200, 200, 200, 0.3);
//    private static final double GRID_MAJOR_LINE_WIDTH = 0.7;
//    private static final double GRID_MINOR_LINE_WIDTH = 0.3;
//
//    private Pane root;
//    private Level currentLevel;
//    private Camera camera;
//
//    @Override
//    public void start(Stage primaryStage) {
//        initializeRoot();
//        initializeSystems();
//        loadInitialLevel();
//
//        Scene scene = new Scene(root);
//        setupInput(scene);
//        primaryStage.setScene(scene);
//        primaryStage.show();
//
//        startGameLoop();
//    }
//
//    private void initializeRoot(){
//        root = new Pane();
//        root.setPrefSize(1000, 1000);
//        root.getChildren().add(createGrid());
//    }
//
//    private void initializeSystems() {
//        camera = new Camera(WORLD_WIDTH, WORLD_HEIGHT);
//    }
//
//    private void loadInitialLevel() {
//        currentLevel = new Level(root, WORLD_WIDTH, WORLD_HEIGHT);
//        currentLevel.loadFromFile("/home/krillin/code/nsu/23203_knyazkov/java/projects/HMClone/src/main/resources/levels/level1.txt");
//        currentLevel.getInputHandler().setPlayer(currentLevel.getPlayer());
////        camera.setTarget(currentLevel::getPlayer);
//    }
//
//    private void startGameLoop() {
//        new AnimationTimer() {
//            @Override
//            public void handle(long now) {
//                currentLevel.update();
////                camera.update(root.getWidth(), root.getHeight());
////                camera.apply(root);
//            }
//        }.start();
//    }
//
//    private void setupInput(Scene scene) {
//        scene.setOnKeyPressed(currentLevel.getInputHandler()::handleKeyPress);
//        scene.setOnKeyReleased(currentLevel.getInputHandler()::handleKeyRelease);
//        scene.setOnMouseMoved(currentLevel.getInputHandler()::handleMouseMove);
//        scene.setOnMouseClicked(currentLevel.getInputHandler()::handleMouseClick);
//    }
//
//
//    private Group createGrid() {
//        Group gridGroup = new Group();
//
//        for (double x = 0; x <= WORLD_WIDTH; x += 50) {
//            Line line = new Line(x, 0, x, WORLD_HEIGHT);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MINOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        for (double y = 0; y <= WORLD_HEIGHT; y += 50) {
//            Line line = new Line(0, y, WORLD_WIDTH, y);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MINOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        for (double x = 0; x <= WORLD_WIDTH; x += 100) {
//            Line line = new Line(x, 0, x, WORLD_HEIGHT);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MAJOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        for (double y = 0; y <= WORLD_HEIGHT; y += 100) {
//            Line line = new Line(0, y, WORLD_WIDTH, y);
//            line.setStroke(GRID_COLOR);
//            line.setStrokeWidth(GRID_MAJOR_LINE_WIDTH);
//            gridGroup.getChildren().add(line);
//        }
//
//        return gridGroup;
//    }
//
//    private Parent createContent(){
//        root = new Pane();
//        root.setPrefSize(1000, 1000);
//
//        root.getChildren().add(createGrid());
//
//        player = new Player(WORLD_WIDTH, WORLD_HEIGHT);
//        addGameObject(player, new Point2D(WORLD_WIDTH/2, WORLD_HEIGHT/2));
//
//        // game loop
//        // will be executed every 1/60 of second
//        AnimationTimer timer = new AnimationTimer() {
//            @Override
//            public void handle(long now) {
//                onUpdate();
//            }
//        };
//        timer.start();
//
//        return root;
//    }
//
//    private void updateCamera() {
//        double targetX = player.getView().getTranslateX() - root.getWidth()/2;
//        double targetY = player.getView().getTranslateY() - root.getHeight()/2;
//
//        targetX = Math.max(0, Math.min(targetX, WORLD_WIDTH - root.getWidth()));
//        targetY = Math.max(0, Math.min(targetY, WORLD_HEIGHT - root.getHeight()));
//
//        cameraX += (targetX - cameraX) * CAMERA_LERP;
//        cameraY += (targetY - cameraY) * CAMERA_LERP;
//
//        root.setTranslateX(-cameraX);
//        root.setTranslateY(-cameraY);
//    }
//
//    private void addBullet(Bullet bullet, Point2D position) {
//        bullets.add(bullet);
//        addGameObject(bullet, position);
//    }
//
//    private void addEnemy(GameObject enemy, Point2D position){
//        enemies.add(enemy);
//        addGameObject(enemy, position);
//    }
//
//    private void addGameObject(GameObject object, Point2D position) {
//        object.getView().setTranslateX(position.getX());
//        object.getView().setTranslateY(position.getY());
//        root.getChildren().add(object.getView());
//    }
//
//    private void onUpdate(){
//        player.update();
//        updateCamera();
//
//        // Existing collision and update logic
//        for (Bullet bullet : bullets){
//            for (GameObject enemy : enemies){
//                if (bullet.isColliding(enemy)) {
//                    bullet.setAlive(false);
//                    enemy.setAlive(false);
//                }
//            }
//            bullet.isOutOfBound(WORLD_WIDTH, WORLD_HEIGHT);
//        }
//        bullets.removeIf(GameObject::isDead);
//        enemies.removeIf(GameObject::isDead);
//
//        bullets.forEach(GameObject::update);
//        enemies.forEach(GameObject::update);
//
//        bullets.removeIf(bullet -> bullet.isOutOfBound(WORLD_WIDTH, WORLD_HEIGHT));
//    }
//
//    @Override
//    public void start(Stage primaryStage) throws Exception {
//        primaryStage.setScene(new Scene(createContent()));
//
//        // Input handlers with camera offset
//        Scene scene = primaryStage.getScene();
//
//        scene.setOnKeyPressed(e -> {
//            switch (e.getCode()) {
//                case A -> player.moveLeft();
//                case D -> player.moveRight();
//                case W -> player.moveUp();
//                case S -> player.moveDown();
//                default -> {}
//            }
//        });
//
//        scene.setOnKeyReleased(e -> {
//            switch (e.getCode()) {
//                case A -> player.stopLeft();
//                case D -> player.stopRight();
//                case W -> player.stopUp();
//                case S -> player.stopDown();
//                default -> {}
//            }
//        });
//
//        scene.setOnMouseMoved(event -> {
//            double mouseWorldX = event.getX() + cameraX;
//            double mouseWorldY = event.getY() + cameraY;
//            player.rotateToCursor(mouseWorldX, mouseWorldY);
//        });
//
//        scene.setOnMouseClicked(e -> {
//            if (e.isPrimaryButtonDown()) {
//                double mouseWorldX = e.getX() + cameraX;
//                double mouseWorldY = e.getY() + cameraY;
//
//                double playerX = player.getView().getTranslateX();
//                double playerY = player.getView().getTranslateY();
//                Point2D direction = new Point2D(
//                        mouseWorldX - playerX,
//                        mouseWorldY - playerY
//                ).normalize();
//
//                Bullet bullet = new Bullet(direction);
//
//                double spawnOffset = 30;
//                Point2D spawnPosition = new Point2D(
//                        playerX + direction.getX() * spawnOffset,
//                        playerY + direction.getY() * spawnOffset
//                );
//
//                addBullet(bullet, spawnPosition);
//            }
//        });
//
//        primaryStage.show();
//    }

//    private static class Player extends GameObject {
//        Player(){
//            super(new Rectangle(40, 20, Color.AQUA));
//        }
//    }

//    private static class Enemy extends GameObject {
//        Enemy(){
//            super(new Rectangle(40, 20, Color.RED));
//        }
//    }

//    private static class Bullet extends GameObject {
//        Bullet(){
//            super(new Circle(10, 10, 10, Color.BLACK));
//        }
//    }

//    @Override
//    public void stop(){
//        // release resources
//    }
//
//    public static void main(String[] args) {
//        launch(args); // creates javaFX launcher thread(which actually launch JavaFX application)
//    }
//
//}