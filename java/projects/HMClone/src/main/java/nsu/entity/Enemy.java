package nsu.entity;

import nsu.ai.states.AiState;
//import nsu.ai.states.Idle;
import nsu.ai.states.Idle;
import nsu.controller.Controller;
import nsu.entity.weapons.Gun;
import nsu.entity.weapons.Weapon;
import nsu.game.state.LevelState;
import nsu.game.state.State;
import nsu.graphics.SpriteLibrary;
import nsu.obj_core.*;
import nsu.obj_core.collission.CollisionVisitor;
import nsu.obj_core.listeners.EnemyListener;

import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.random;

public class Enemy extends MovingEntity {
    private final double enemyVelocity = 2;
    private final int rageRadius = 500;
    private final int attackRange = 320;
    private final int damage = 10;
    private AiState state = new Idle();
    private Player player;
    private Weapon weapon = new Gun(this);

    private List<EnemyListener> listeners = new ArrayList<>();

    public Enemy(Controller controller, Player player, State st) {
        super(controller);
        setSize(new Size(SpriteLibrary.getSpriteSize(), SpriteLibrary.getSpriteSize()));
        motion.setVelocity(enemyVelocity + random());
        this.player = player;
        addListener((LevelState) st);
    }

    public void update(State st) {
        if (player != null && player.isAlive()) {
            state.update(this, player);
            super.update(st);
            state.maybeTransition(this, player);
            motion.clearMoving();
        }

    }

    public Weapon getWeapon() {
        return weapon;
    }

    @Override
    public void accept(CollisionVisitor visitor, GameObject other) {
        visitor.visit(this, other);
    }

    public void setAngerTarget(Player player) {
        this.player = player;
    }

    public void shootAt(Position position) {
        weapon.shootAt(position);
    }

    public boolean isPlayerInRageRadius(Player player) {
        return calculateDistanceTo(player.getPosition()) <= rageRadius;
    }

    public void setState(AiState state) {
        this.state = state;
    }

    public int getDamage() {
        return damage;
    }

    public boolean isPlayerInAttackRange(Player player) {
        return calculateDistanceTo(player.getPosition()) <= attackRange;
    }

    private double calculateDistanceTo(Position position) {
        return Vector2D.distance(this.position, position);
    }

    public void setVelocity(double v) {
        velocity = v;
    }

    int timeSinceLastHit = 0;
    int hitCoolDown = 30;

    public int hit() {
        timeSinceLastHit++;
        if (timeSinceLastHit > hitCoolDown) {
            timeSinceLastHit = 0;
            return damage;
        } else {
            return 0;
        }
    }

    private void notifyDeath() {
        for (EnemyListener listener : listeners) {
            listener.onDeath();
        }
    }

    public void addListener(EnemyListener listener) {
        listeners.add(listener);
    }

    @Override
    public void decreaseHealth(int by) {
        if (health > 0) {
            this.health -= by;
        } else {
            notifyDeath();
            kill();
        }
    }
}
