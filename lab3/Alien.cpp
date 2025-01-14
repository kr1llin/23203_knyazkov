#include "Alien.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

BasicAlien::BasicAlien() : m_speed(INIT_ALIEN_SPEED) {

  if (!m_texture.loadFromFile(ALIEN_TEXTURE_FILE)) {
    std::cerr << "Error loading texture from " << ALIEN_TEXTURE_FILE
              << std::endl;
  }

  m_sprite.setTexture(m_texture);
}

void BasicAlien::setPosition(float x, float y) {
  m_position.x = x;
  m_position.y = y;

  m_sprite.setPosition(m_position);
}

BasicAlien::BasicAlien(float x, float y) : m_speed(INIT_ALIEN_SPEED) {

  if (!m_texture.loadFromFile(ALIEN_TEXTURE_FILE)) {
    std::cerr << "Error loading texture from " << ALIEN_TEXTURE_FILE
              << std::endl;
  }

  m_sprite.setTexture(m_texture);
  setPosition(x, y);
}

sf::Sprite BasicAlien::getSprite() const { return m_sprite; }

sf::FloatRect BasicAlien::getBounds() const {
  return m_sprite.getGlobalBounds();
}

void BasicAlien::move(float dx, float dy) {
  m_position.x += dx * m_speed;
  m_position.y += dy * m_speed;

  m_sprite.setPosition(m_position);
}

void BasicAlien::update() {
  m_sprite.setPosition(m_position);
}

void BasicAlien::draw(sf::RenderWindow &window) {
  window.draw(m_sprite);
}

float BasicAlien::getX() const { return m_position.x; }

float BasicAlien::getY() const { return m_position.y; }
