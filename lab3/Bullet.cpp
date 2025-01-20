#include "Bullet.hpp"
#include "Collidable.hpp"
#include "Invaders.hpp"
#include "State.hpp"

Bullet::Bullet(float x, float y, float speed) : m_speed(speed) {
  
  m_position = sf::Vector2f(x, y);
  m_size = BULLET_SIZE;
  m_id = objID::BULLET_ID;
}

void Bullet::move(float dx, float dy) {
  m_position.x += dx * m_speed;
  m_position.y += dy * m_speed;
}
void Bullet::update(float deltaTime) {
  move(0, deltaTime);
  if (isOffScreen()) {
    die();
  }
}

void Bullet::ProcessCollision(ICollidable *other) {
  if (auto *bullet = dynamic_cast<Bullet*>(other)) {
    die();
  }
}

void PlayerBullet::ProcessCollision(ICollidable *other) {
  if (auto *bullet = dynamic_cast<Alien*>(other)) {
    die();
  }
}

void AlienBullet::ProcessCollision(ICollidable *other) {
  if (auto *bullet = dynamic_cast<Player*>(other)) {
    die();
  }
}

bool Bullet::isOffScreen() const {
  float Height = sf::VideoMode::getDesktopMode().height;
  return getY() >= Height || getY() + m_size.y <= 0;
}

bool Bullet::isDead() const { return m_isDead; }


void Magazine::update(float deltaTime){
  for (int i = m_bullets.size() - 1; i >= 0; i--) {
    m_bullets[i]->update(deltaTime);
    if (m_bullets[i]->isDead()) {
      m_bullets.erase(m_bullets.begin() + i);
    }
  }
}
