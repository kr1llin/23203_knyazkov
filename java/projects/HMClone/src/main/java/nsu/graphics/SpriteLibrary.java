package nsu.graphics;

import nsu.entity.Bullet;
import nsu.entity.EnemyBullet;
import nsu.entity.PlayerBullet;
import nsu.game.Game;
import nsu.obj_core.Size;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;

public class SpriteLibrary {
    private final static String PATH_TO_UNITS = "/sprites";
    public static int SPRITE_SIZE = 64;


    private Map<String, SpriteSet> units;
    private Map<String, Image> tiles;
    private final Map<Class<?>, SpriteData> classSpriteData;

    private static class SpriteData {
        Color color;
        int width;
        int height;

        SpriteData(Color color, int width, int height) {
            this.color = color;
            this.width = width;
            this.height = height;
        }
    }

    public static int getSpriteSize() {
        return SPRITE_SIZE;
    }

    public SpriteLibrary() {
        units = new HashMap<>();
        tiles = new HashMap<>();
        classSpriteData = new HashMap<>();
        loadSpritesFromDisk();
        registerDefaultClassSprites();
    }

    private void registerDefaultClassSprites() {
        registerClassSprite(Bullet.class, Color.ORANGE, 25, 25);
        registerClassSprite(PlayerBullet.class, Color.ORANGE, 25, 25);
        registerClassSprite(EnemyBullet.class, Color.RED, 25, 25);
    }

    public void registerClassSprite(Class<?> clazz, Color color, int width, int height) {
        classSpriteData.put(clazz, new SpriteData(color, width, height));
    }

    public Image getSprite(Class<?> clazz) {
        String className = clazz.getSimpleName().toLowerCase();

        if (units.containsKey(className)) {
            return units.get(className).get("idle");
        }

        if (tiles.containsKey(className)) {
            return tiles.get(className);
        }

        if (classSpriteData.containsKey(clazz)) {
            SpriteData data = classSpriteData.get(clazz);
            return generateSprite(data.color, data.width, data.height);
        }

        return tiles.getOrDefault("default", null);
    }

    public Size getSpriteSize(Class<?> clazz) {
        String className = clazz.getSimpleName().toLowerCase();

        if (units.containsKey(className)) {
            return new Size(SPRITE_SIZE, SPRITE_SIZE);
        }

        if (classSpriteData.containsKey(clazz)) {
            SpriteData data = classSpriteData.get(clazz);
            return new Size(data.width, data.height);
        }

        return new Size(SPRITE_SIZE, SPRITE_SIZE);
    }

    private Image generateSprite(Color color, int width, int height) {
        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        Graphics2D graphics = image.createGraphics();
        graphics.setColor(color);
        graphics.fillRect(0, 0, width, height);
        graphics.dispose();
        return image;
    }

    private String[] getFolderNames(String basePath) {
        URL resource = SpriteLibrary.class.getResource(basePath);
        assert resource != null;
        File file = new File(resource.getFile());
        return file.list((current, name) -> new File(current, name).isDirectory());
    }

    private String[] getSheetsInFolder(String basePath) {
        URL resource = SpriteLibrary.class.getResource(basePath);
        assert resource != null;
        File file = new File(resource.getFile());
        return file.list((current, name) -> new File(current, name).isFile());
    }

    private void loadSpritesFromDisk() {
        loadUnits();
        loadTiles();
    }

    private void loadTiles() {
        String pathToTiles = "/tiles";
        String[] tileSheets = getSheetsInFolder(pathToTiles);
        for (String sheet : tileSheets) {
            Image image = ImageLoader.loadImage(pathToTiles + "/" + sheet);
            tiles.put(sheet.replace(".png", ""), image);
        }
    }

//    private void loadTiles() {
//        BufferedImage image = new BufferedImage(SPRITE_SIZE, SPRITE_SIZE, BufferedImage.TYPE_INT_RGB);
//        Graphics2D graphics = image.createGraphics();
//
//        graphics.setColor(Color.WHITE);
//        graphics.fillRect(0,0, SPRITE_SIZE, SPRITE_SIZE);
//        graphics.setColor(Color.GREEN);
//        graphics.drawRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
//        graphics.dispose();
//
//        tiles.put("tile", image);
//
//        BufferedImage boxImage = new BufferedImage(SPRITE_SIZE, SPRITE_SIZE, BufferedImage.TYPE_INT_RGB);
//        graphics = boxImage.createGraphics();
//
//        graphics.setColor(Color.DARK_GRAY);
//        graphics.fillRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
//        graphics.setColor(Color.BLACK);
//        graphics.drawRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
//        graphics.dispose();
//
//        tiles.put("box", boxImage);
//    }

    private void loadUnits() {
        String[] folderNames = getFolderNames(PATH_TO_UNITS);

        for (String folderName : folderNames) {
            if (folderName.equalsIgnoreCase("tile")) {
                continue;
            }
            SpriteSet spriteSet = new SpriteSet();
            String pathToFolder = PATH_TO_UNITS + "/" + folderName;
            String[] sheetsInFolder = getSheetsInFolder(pathToFolder);

            for (String sheetName : sheetsInFolder) {
                spriteSet.addSheet(
                        sheetName.substring(0, sheetName.length() - 4), // - .png :P
                        ImageLoader.loadImage(pathToFolder + "/" + sheetName)
                );
            }
            units.put(folderName, spriteSet);
        }
    }

    public SpriteSet getUnit(String name) {
        return units.get(name);
    }

    public Image getTile(String name) {
        return tiles.get(name);
    }

}
