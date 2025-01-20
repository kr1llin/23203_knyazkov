#include "Alien.hpp"
#include "Bullet.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

Alien::Alien() : m_speed(INIT_ALIEN_SPEED) {
  
  m_id = objID::ALIEN_ID; 
  m_size = INIT_ALIEN_SIZE;
}

Alien::Alien(float x, float y) : m_speed(INIT_ALIEN_SPEED){
  m_id = objID::ALIEN_ID; 
  m_size = INIT_ALIEN_SIZE;
  setPosition(x, y);
}

void Alien::setPosition(float x, float y) {
  m_position.x = x;
  m_position.y = y;
}


void Alien::move(float dx, float dy) {
  m_position.x += dx * m_speed;
  m_position.y += dy * m_speed;
}

void Alien::update(float deltaTime) {
}

void Alien::ProcessCollision(ICollidable *other) {
  auto *bullet = dynamic_cast<PlayerBullet *>(other);
  if (bullet) {
    die();
  }
}
