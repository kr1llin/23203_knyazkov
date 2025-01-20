#pragma once
#include "Collidable.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <vector>

constexpr float THRESHOLD_Y = 5;

class CollisionModule {
public:
  void AddToCollisionList(ICollidable *object);
  void RemoveFromCollisionList(ICollidable *object);
  void CheckCollisionList();
  void ProcessCollisionList();
private:
    std::vector<ICollidable*> m_collisionList;
    bool CheckCollision(ICollidable *a, ICollidable *b);
};
