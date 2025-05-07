package nsu.obj_core.collission;

import nsu.entity.GameObject;
import nsu.obj_core.Position;
import nsu.obj_core.Vector2D;

import java.awt.*;

public class CollisionUtils {
    public static Vector2D getCollisionNormal(GameObject a, GameObject b) {
        Position aCenter = a.getPosition().add((int)a.getSize().getWidth() /2, (int)a.getSize().getHeight() /2);
        Position bCenter = b.getPosition().add((int)b.getSize().getWidth() /2, (int)b.getSize().getHeight() /2);

        Vector2D delta = aCenter.subtract(bCenter);

        double overlapX = ((double) a.getSize().getWidth() /2 + (double) b.getSize().getWidth() /2) - Math.abs(delta.getX());
        double overlapY = ((double) a.getSize().getHeight() /2 + (double) b.getSize().getHeight() /2) - Math.abs(delta.getY());

        if (overlapX < overlapY) {
            return new Vector2D(delta.getX() > 0 ? 1 : -1, 0);
        }
        else {
            return new Vector2D(0, delta.getY() > 0 ? 1 : -1);
        }
    }

    static String getCollisionSide(GameObject a, GameObject b) {
        CollisionBox aRect = a.getCollisionBox();
        CollisionBox bRect = b.getCollisionBox();

        double aCenterX = aRect.getBounds().getX();
        double bCenterX = bRect.getBounds().getX();
        double dx = aCenterX - bCenterX;

        double aCenterY = aRect.getBounds().getY();
        double bCenterY = bRect.getBounds().getY();
        double dy = aCenterY - bCenterY;

        double penetrationX = (aRect.getBounds().getWidth() + bRect.getBounds().getWidth()) / 2 - Math.abs(dx);
        double penetrationY = (aRect.getBounds().getHeight() + bRect.getBounds().getHeight()) / 2 - Math.abs(dy);

        if (penetrationX < penetrationY) {
            return (dx < 0) ? "right" : "left";
        } else {
            return (dy < 0) ? "down" : "up";
        }
    }

    static void resolveOverlap(GameObject entity, GameObject other) {
        Rectangle entityRect = entity.getCollisionBox().getBounds();
        Rectangle boxRect = other.getCollisionBox().getBounds();

        double overlapLeft = entityRect.getX() + entityRect.getWidth() - boxRect.getX();
        double overlapRight = boxRect.getX() + boxRect.getWidth() - entityRect.getX();
        double overlapX = Math.min(overlapLeft, overlapRight);

        double overlapTop = entityRect.getY() + entityRect.getHeight() - boxRect.getY();
        double overlapBottom = boxRect.getY() + boxRect.getHeight() - entityRect.getY();
        double overlapY = Math.min(overlapTop, overlapBottom);

        if (Math.abs(overlapX) < Math.abs(overlapY)) {
            if (entityRect.getCenterX() < boxRect.getCenterX()) {
                entity.setPositionX(entityRect.getX() - overlapX);
            } else {
                entity.setPositionX(entityRect.getX() + overlapX);
            }
        } else {
            if (entityRect.getCenterY() < boxRect.getCenterY()) {
                entity.setPositionY(entityRect.getY() - overlapY);
            } else {
                entity.setPositionY(entityRect.getY() + overlapY);
            }
        }
    }
}