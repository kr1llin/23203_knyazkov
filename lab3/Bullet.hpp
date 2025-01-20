#pragma once

#include "Collidable.hpp"
#include "Object.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <memory>

constexpr float INIT_ALIEN_BULLET_SPEED = 700;
constexpr float INIT_PLAYER_BULLET_SPEED = 900;
const sf::Vector2f BULLET_SIZE = {20.0F, 60.0F};

class Bullet : public Object, public ICollidable {
public:
  Bullet(float x, float y, float speed);
  virtual ~Bullet() {}

  void update(float deltaTime) override;
  // virtual void draw(sf::RenderWindow &window) const;

  sf::Vector2f GetPosition() override { return m_position; }
  sf::Vector2f GetSize() override { return m_size; }
  // sf::FloatRect getBounds() override { return m_shape.getGlobalBounds(); }

  void ProcessCollision(ICollidable *other) override;

  bool isAddedToObjects() const {return inObjects;}
  void AddedToObjects() { inObjects = true; }

  bool isOffScreen() const;
  bool isDead() const;

  void move(float dx, float dy);

  float getX() const {return m_position.x;}
  float getY() const {return m_position.y;};

  void die() { m_isDead = true; }

protected:
  bool inObjects = false;
  float m_speed;
};

class PlayerBullet : public Bullet {
public:
  void ProcessCollision(ICollidable *other) override;
  PlayerBullet(float x, float y) : Bullet(x, y, -INIT_PLAYER_BULLET_SPEED) {}
};

class AlienBullet : public Bullet {
public:
  void ProcessCollision(ICollidable *other) override;
  AlienBullet(float x, float y) : Bullet(x, y, INIT_ALIEN_BULLET_SPEED) {}
};


class Magazine : public Object {
  public:
    Magazine(){
      m_id = objID::BULLET_ID;
    };
    
    const std::vector<std::shared_ptr<Bullet>>& getAmmo() const {return m_bullets;}
    void pickUp(Bullet& bullet){m_bullets.push_back(std::make_shared<Bullet>(bullet));}
    void update(float deltaTime) override;

  private:
    std::vector<std::shared_ptr<Bullet>> m_bullets;
};
