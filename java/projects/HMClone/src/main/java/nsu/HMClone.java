package nsu;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.geometry.Point2D;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.List;

import com.almasb.fxgl.app.GameApplication;
import com.almasb.fxgl.app.GameSettings;
import com.almasb.fxgl.dsl.FXGL;
import com.almasb.fxgl.entity.Entity;
import com.almasb.fxgl.input.Input;
import com.almasb.fxgl.input.UserAction;
import javafx.scene.input.KeyCode;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import java.util.Map;





// Change level = change scene
//
//public class HMClone extends Application {
//    private double cameraX = 0;
//    private double cameraY = 0;
//    private final double CAMERA_LERP = 0.1; // Smoothing factor
//    private final double WORLD_WIDTH = 2000;
//    private final double WORLD_HEIGHT = 2000;
//
//    private static final Color GRID_COLOR = Color.rgb(200, 200, 200, 0.3);
//    private static final double GRID_MAJOR_LINE_WIDTH = 0.7;
//    private static final double GRID_MINOR_LINE_WIDTH = 0.3;
//
//    private Pane root;
//    private List<Bullet> bullets = new ArrayList<>();
//    private List<GameObject> enemies = new ArrayList<>();
//    private Player player = new Player(WORLD_WIDTH, WORLD_HEIGHT);
//
//
//
//    public void init() {
//        // init resources
//    }
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
////        bullets.removeIf(bullet -> bullet.isOutOfBound(WORLD_WIDTH, WORLD_HEIGHT));
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
//
////    private static class Player extends GameObject {
////        Player(){
////            super(new Rectangle(40, 20, Color.AQUA));
////        }
////    }
//
////    private static class Enemy extends GameObject {
////        Enemy(){
////            super(new Rectangle(40, 20, Color.RED));
////        }
////    }
//
////    private static class Bullet extends GameObject {
////        Bullet(){
////            super(new Circle(10, 10, 10, Color.BLACK));
////        }
////    }
//
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