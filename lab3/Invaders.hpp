#pragma once 

#include "Alien.hpp"
#include "Bullet.hpp"
#include "GameEventListener.hpp"
#include "Object.hpp"
// #include "CollisionInterface.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>

constexpr float INIT_INVADERS_SPEED = INIT_ALIEN_SPEED;
constexpr int INIT_INVADERS_ROWS =  4;
constexpr float INIT_INVADERS_X = 0;
constexpr float INIT_INVADERS_Y = 0;
constexpr int SHOOT_PERIOD = 1000;

class Invaders : public Object, public Subject {
public:
  Invaders() : m_rowsCount(INIT_INVADERS_ROWS){
    m_id = objID::INVADERS_ID;
    initAliens();
  }

  void initAliens();
  void moveAliensDown();
  std::vector<std::shared_ptr<Alien>>& getAliens();
  // const Magazine &getBullets() { return m_bullets; }
  const std::vector<std::shared_ptr<AlienBullet>> &getBullets() { return m_bullets; }

  void update(float dtAsSeconds) override;

private:
  int m_rowsCount;
  bool m_direction{}; // 0 for right, 1 for left
  float m_y{};

  std::vector<std::shared_ptr<Alien>> m_aliens;
  // Magazine m_bullets;
  std::vector<std::shared_ptr<AlienBullet>> m_bullets; 

  int m_timeSinceLastBullet{};

  bool hasChangedDirection();
  std::vector<std::shared_ptr<Alien>> getBottomAliens();
  void makeABottomAlienShoot(const std::vector<std::shared_ptr<Alien>> &bottomAliens);
  void updateBullets(float deltaTime);
  void RemoveDeadAliens();
};
