#pragma once 

#include "Alien.hpp"
#include "Bullet.hpp"
// #include "CollisionInterface.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>

constexpr float INIT_INVADERS_SPEED = INIT_ALIEN_SPEED;
constexpr int INIT_INVADERS_ROWS =  4;
const float INIT_INVADERS_X = 0;
const float INIT_INVADERS_Y = 0;

class Invaders{
public:
  Invaders() : m_rowsCount(INIT_INVADERS_ROWS), m_timeSinceLastBullet(0){
    initAliens();
  }

  void initAliens();
  const std::vector<std::unique_ptr<BasicAlien>>& getAliens() const;
  bool hasChangedDirection();
  void moveAliensDown();
  std::vector<AlienBullet> &getBullets() { return m_bullets; }

  bool checkCollision(float x, float y);
  void update(float dtAsSeconds);
  void draw(sf::RenderWindow &window);

private:
  int m_rowsCount;
  bool m_direction{}; // 0 for right, 1 for left
  float m_y{};

  std::vector<std::unique_ptr<BasicAlien>> m_aliens;
  std::vector<AlienBullet> m_bullets;
  sf::Vector2f m_position;

  float m_speed{}; // pixels per seconds
  int m_timeSinceLastBullet;

  std::vector<std::unique_ptr<BasicAlien>> getBottomAliens();
  void makeABottomAlienShoot(const std::vector<std::unique_ptr<BasicAlien>> &bottomAliens);
  void updateBullets(float deltaTime);
};
