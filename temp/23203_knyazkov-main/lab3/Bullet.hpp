#pragma once 

#include "Level.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/VideoMode.hpp>

constexpr float INIT_ALIEN_BULLET_SPEED = 700;
constexpr float INIT_PLAYER_BULLET_SPEED = 900;
constexpr float BULLET_SIZE_X = 20.0F;
constexpr float BULLET_SIZE_Y = 60.0F;



class Bullet {
public:
  Bullet(float x, float y, float speed);
  virtual ~Bullet() {}

  virtual void update(float deltaTime);
  virtual void draw(sf::RenderWindow &window) const;
  virtual bool isOffScreen() const;
  sf::FloatRect getBounds() const;
  float getX() const;
  float getY() const;

protected:
  sf::Vector2f m_position;
  sf::RectangleShape m_shape;
  float m_speed;
};

class PlayerBullet : public Bullet{
public:
  PlayerBullet(float x, float y) : Bullet(x, y, INIT_PLAYER_BULLET_SPEED) {}
  void update(float deltaTime) override {
    m_position.y -= m_speed * deltaTime;
    m_shape.setPosition(m_position);
  }
  bool isOffScreen() const override{
  return (*this).getY() <= 0;
}
};

class AlienBullet : public Bullet {
public:
  AlienBullet(float x, float y) : Bullet(x, y, INIT_ALIEN_BULLET_SPEED) {
  }

  void update(float deltaTime) override {
    m_position.y += m_speed * deltaTime;
    m_shape.setPosition(m_position);
    }
};
