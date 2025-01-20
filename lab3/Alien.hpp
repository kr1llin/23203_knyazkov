#include "Collidable.hpp"
#include "Object.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
    
const sf::Vector2f INIT_ALIEN_SIZE{80, 58};
constexpr float INIT_ALIEN_SPEED = 100;
const float INIT_ALIEN_POSITION_X = 30;
const float INIT_ALIEN_POSITION_Y = 30;

// class Alien : public Object, public ICollidable {
class Alien : public Object, public ICollidable {

public:
  Alien();
  Alien(float x, float y);
  virtual ~Alien() {}

  // ICollidable interface
  sf::Vector2f GetPosition() override { return m_position; }
  sf::Vector2f GetSize() override { return m_size; }

  void ProcessCollision(ICollidable *other) override;

  void move(float dx, float dy);
  // virtual void shoot() {}

  void update(float deltaTime) override;
  void setPosition(float x, float y);
  bool isAlive() const { return !m_isDead; }
  void die() { m_isDead = true; }
  void accelerate(){m_speed *= 1.1;}

protected:
  float m_speed = 0;
};

class BasicAlien : public Alien {
  BasicAlien() { m_speed = INIT_ALIEN_SPEED; }
  BasicAlien(float x, float y) : Alien(x, y) { m_speed = INIT_ALIEN_SPEED; }
};

class FastAlien : public Alien {
  FastAlien() { m_speed = INIT_ALIEN_SPEED * 2; }
  FastAlien(float x, float y) : Alien(x, y) { m_speed = INIT_ALIEN_SPEED; }

};



// class BasicAlien : public ICollidable {
// public:
//   BasicAlien(); // just init a texture
//   BasicAlien(float x, float y);
//   virtual ~BasicAlien(){};
//   void update();

// //ICollission
//   sf::Vector2f GetPosition() override { return m_position; }
//   sf::Vector2f GetSize() override { return getBounds().getSize();}
//   sf::FloatRect getBounds() override {return m_sprite.getGlobalBounds();}
//   void ProcessCollision(ICollidable *other) override;
  
// // To be moved to RenderModule
//   sf::Sprite getSprite() const { return m_sprite; }
//   void draw(sf::RenderWindow &window);

//   void move(float dx, float dy);
//   void setPosition(float x, float y);

//   bool isAlive() const { return m_alive; }
//   void die() { m_alive = false; }

// private:
//   sf::Vector2f m_position;
//   sf::Sprite m_sprite;
//   sf::Texture m_texture;

//   bool m_alive;
//   float m_speed; // pixels per seconds
//   sf::Vector2f m_size;

//   void initializeTexture(std::string path);
// };
