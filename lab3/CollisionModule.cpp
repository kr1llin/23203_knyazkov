#include "CollisionModule.hpp"
#include <algorithm>
#include <iostream>

void CollisionModule::AddToCollisionList(ICollidable *object) {
  m_collisionList.push_back(object);
}

void CollisionModule::RemoveFromCollisionList(ICollidable *object) {
  m_collisionList.erase(
      std::remove(m_collisionList.begin(), m_collisionList.end(), object),
      m_collisionList.end());
}

void CollisionModule::CheckCollisionList() {
  // check the closest ones
  std::sort(m_collisionList.begin(), m_collisionList.end(),
            [](ICollidable *a, ICollidable *b) {
              return a->GetPosition().y < b->GetPosition().y;
            });
  for (size_t i = 0; i < m_collisionList.size(); ++i) {
    for (size_t j = i + 1; j < m_collisionList.size(); ++j) {
      if (m_collisionList[j]->GetPosition().y -
              m_collisionList[i]->GetPosition().y >
          THRESHOLD_Y) {
        break;
      }
      
      if (CheckCollision(m_collisionList[i], m_collisionList[j])) {
        m_collisionList[i]->ProcessCollision(m_collisionList[j]);
        m_collisionList[j]->ProcessCollision(m_collisionList[i]);
      }
    }
  }
}

bool CollisionModule::CheckCollision(ICollidable* a, ICollidable* b) {
    if (!a || !b) {
        return false;
    }

    const sf::Vector2f& posA = a->GetPosition();
    const sf::Vector2f& sizeA = a->GetSize();
    const sf::Vector2f& posB = b->GetPosition();
    const sf::Vector2f& sizeB = b->GetSize();

    return (posA.x < posB.x + sizeB.x &&
            posA.x + sizeA.x > posB.x &&
            posA.y < posB.y + sizeB.y &&
            posA.y + sizeA.y > posB.y);
}

// void CollisionModule::CheckCollisionList() {
//   for (size_t i = 0; i < m_collisionList.size(); ++i) {
//     for (size_t j = i + 1; j < m_collisionList.size(); ++j) {
//       if (CheckCollision(m_collisionList[i], m_collisionList[j])) {
//         m_collisionList[i]->ProcessCollision(m_collisionList[j]);
//         m_collisionList[j]->ProcessCollision(m_collisionList[i]);
//       }
//     }
//   }
// }
