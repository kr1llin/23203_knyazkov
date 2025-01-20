#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

//it also sets render ordering
enum class objID{
  BULLET_ID,
  PLAYER_ID,
  ALIEN_ID,
  INVADERS_ID,
};

class Object{
public:
  Object() = default;
  virtual ~Object() = default;
  virtual void update(float deltaTime) = 0;
  sf::Vector2f getPosition() const { return m_position; }
  sf::Vector2f getSize() const { return m_size; }
  bool isDead() const {return m_isDead;}

  objID getID() const {return m_id;}

protected:
  sf::Vector2f m_position;
  sf::Vector2f m_size;
  objID m_id;
  bool m_isDead = false;
};
