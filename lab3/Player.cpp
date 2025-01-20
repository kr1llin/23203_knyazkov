#include "Player.hpp"
#include "Bullet.hpp"
#include "Collidable.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>

void Player::update(float deltaTime) {
  float Width = sf::VideoMode::getDesktopMode().width;
  char step_x =
      m_rightPressed - m_leftPressed; // 1 is right, -1 if left, 0 if nothing
  m_position.x = std::clamp<float>(m_position.x + m_Speed * step_x * deltaTime,
                                   0, Width - m_size.x);
  shoot();
  m_timeSinceLastBullet++;
  // updateBullets(deltaTime);
}

// visitor pattern
void Player::ProcessCollision(ICollidable *other) {
    auto *bullet = dynamic_cast<PlayerBullet *>(other);
  if (!bullet) {
    kill();
  }
}

void Player::startShooting() { m_isShooting = true; }
void Player::stopShooting() { m_isShooting = false; }

void Player::shoot() {
  if (m_isShooting && m_timeSinceLastBullet >= PLAYER_SHOOT_PERIOD) {
    stopShooting();
    PlayerBullet bullet(m_position.x + m_size.x / 2,
                        m_position.y - m_size.y / 2);
    // m_bullets.pickUp(bullet);
    m_bullets.push_back(std::make_shared<PlayerBullet>(bullet));
    m_timeSinceLastBullet = 0;
  }
}

void Player::moveLeft() { m_leftPressed = true; }

void Player::moveRight() { m_rightPressed = true; }

void Player::stopLeft() { m_leftPressed = false; }

void Player::stopRight() { m_rightPressed = false; }
