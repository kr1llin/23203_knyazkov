package nsu.entity.weapons;

import nsu.entity.Bullet;
import nsu.entity.GameObject;
import nsu.game.state.LevelState;
import nsu.obj_core.collission.CollisionBox;
import nsu.obj_core.collission.CollisionVisitor;
import nsu.obj_core.Position;
import nsu.game.state.State;

import java.awt.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Weapon extends GameObject {
    protected GameObject parent = null;
    protected List<Bullet> bullets = new ArrayList<Bullet>();

    Weapon(GameObject parent){
     this.parent = parent;
    }

    public void shootAt(Position position) {

    }

    @Override
    public void update(State state) {
        ((LevelState)state).getGameObjects().addAll(bullets);
        bullets.clear();
    }

    @Override
    public CollisionBox getCollisionBox() {
        return null;
    }

    @Override
    public void accept(CollisionVisitor visitor, GameObject other) {
    }

}
