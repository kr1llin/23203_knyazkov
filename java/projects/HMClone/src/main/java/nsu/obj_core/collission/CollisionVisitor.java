package nsu.obj_core.collission;

import nsu.entity.*;

public interface CollisionVisitor {
    void visit(Player player, GameObject other);
    void visit(Enemy enemy, GameObject other);
    void visit(Bullet bullet, GameObject other);
    void visit(Box box, GameObject other);
}
