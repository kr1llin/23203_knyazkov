#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class ICollidable {
public:
  virtual ~ICollidable() {};
  virtual sf::Vector2f GetPosition() = 0;
  virtual sf::Vector2f GetSize() = 0;
  // virtual sf::FloatRect getBounds() = 0;

  // to notify object that it collided with another object
  virtual void ProcessCollision(ICollidable *other) = 0;
};
