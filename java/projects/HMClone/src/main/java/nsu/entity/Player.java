package nsu.entity;

import nsu.display.Camera;
import nsu.entity.weapons.Gun;
import nsu.entity.weapons.Shotgun;
import nsu.entity.weapons.Weapon;
import nsu.game.state.LevelState;
import nsu.game.state.State;
import nsu.obj_core.*;
import nsu.controller.Controller;
import nsu.graphics.SpriteLibrary;
import nsu.obj_core.collission.CollisionVisitor;
import nsu.obj_core.listeners.PlayerStatsListener;

import java.awt.geom.AffineTransform;
import java.util.ArrayList;
import java.util.List;

public class Player extends MovingEntity {
    private final Camera camera;
    private List<Weapon> weapons;
    private int weaponIndex = 0;
    private List<PlayerStatsListener> listeners = new ArrayList<>();

    private int timeSinceLastAttack = 0;
    private final int attackCooldown = 20;
    private final int playerHealth = 300;

    public Player(Controller controller, Camera camera, State st) {
        super(controller);
        health = playerHealth;
        weapons = new ArrayList<>();
        setSize(new Size(SpriteLibrary.getSpriteSize(), SpriteLibrary.getSpriteSize()));
        weapons.add(new Gun(this));
        weapons.add(new Shotgun(this));
        this.camera = camera;
    }

    @Override
    public void update(State state) {
        timeSinceLastAttack++;

        if (isAlive()) {
            motion.update(controller);
            position.apply(motion);
            rotation.apply(camera.screenToWorld(controller.getMousePosition()), this.position);

            if (controller.isRequestingOne()) {
                switchWeapon(0);
            } else if (controller.isRequestingTwo()) {
                switchWeapon(1);
            }

            if (controller.isShooting() && timeSinceLastAttack >= attackCooldown) {
                Position mouseWorldPos = camera.screenToWorld(controller.getMousePosition());
                getCurrentWeapon().shootAt(mouseWorldPos);
                timeSinceLastAttack = 0;
            }
        }

    }

    @Override
    public void accept(CollisionVisitor visitor, GameObject other) {
        visitor.visit(this, other);
    }


    public Weapon getCurrentWeapon() {
        return weapons.get(weaponIndex);
    }

    public void switchWeapon(int slot) {
        if (slot >= 0 && slot < weapons.size()) {
            weaponIndex = slot;
        }
        notifyWeaponChanged();
    }

    @Override
    public void decreaseHealth(int by) {
        if (health > 0) {
            this.health -= by;
        } else {
            kill();
        }
        notifyHealthChange();
    }

    @Override
    public void increaseHealth(int by) {
        this.health += by;
        notifyHealthChange();
    }

    @Override
    public AffineTransform getAffineTransform(LevelState state, GameObject gameObject) {
        Camera camera = state.getCamera();

        double screenX = gameObject.getPosition().getX() - camera.getPosition().getX();
        double screenY = gameObject.getPosition().getY() - camera.getPosition().getY();
        double height = gameObject.getSize().getHeight();
        double width = gameObject.getSize().getWidth();

        AffineTransform transform = new AffineTransform();
        transform.translate(screenX, screenY);
        transform.rotate(Math.toRadians(gameObject.getRotation().getRotationAngle()) + Math.PI / 2, 0, 0); // sprite looks up (we assume that all sprites are faced up)
        transform.translate(-width / 2.0, -height / 2.0);
        return transform;
    }

    public List<Weapon> getWeapons() {
        return weapons;
    }

    public void addStatsListener(PlayerStatsListener listener) {
        listeners.add(listener);
    }

    private void notifyHealthChange() {
        for (PlayerStatsListener listener : listeners) {
            listener.onHealthChanged(health);
        }
    }

    private void notifyWeaponChanged() {
        for (PlayerStatsListener listener : listeners) {
            listener.onWeaponChanged(getCurrentWeapon());
        }
    }
}
