//package nsu;
//
//import javafx.geometry.Point2D;
//import javafx.scene.input.KeyCode;
//import javafx.scene.input.KeyEvent;
//import javafx.scene.input.MouseEvent;
//
//public class InputHandler {
//    private Player player;
//    private Level currentLevel;
//    private Camera camera;
//
//    public InputHandler(Level level){
//        currentLevel = level;
//    }
//    public void setPlayer(Player player) {
//        this.player = player;
//    }
//
//    public void handleKeyPress(KeyEvent event) {
//        if (player == null) return;
//        // Handle player movement
//    }
//    public void handleKeyRelease(KeyEvent event) {
//    }
//
//    public void handleMouseMove(MouseEvent event) {
//        if (player == null) return;
//        Point2D worldPos = screenToWorld(event.getX(), event.getY());
//        player.rotateTo(worldPos);
//    }
//
//    public void handleMouseClick(MouseEvent event) {
//        if (player != null && event.isPrimaryButtonDown()) {
////            Bullet bullet = player.shoot(); // animation?
//            Point2D spawnPos = new Point2D(player.getPosition().getX(), player.getPosition().getY());
//            Point2D direction = new Point2D(
//                    event.getX() - player.getPosition().getX(),
//                    event.getY() - player.getPosition().getY()
//            ).normalize();
//            Bullet bullet = new Bullet(direction);
//            currentLevel.addObject(bullet, spawnPos);
//        }
//    }
//
//    private Point2D screenToWorld(double screenX, double screenY) {
//        return new Point2D(
//                screenX, screenY
////                screenX + camera.getX(),
////                screenY + camera.getY()
//        );
//    }
//
//
//}