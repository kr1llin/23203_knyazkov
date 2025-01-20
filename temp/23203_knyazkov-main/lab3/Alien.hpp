#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/VideoMode.hpp>

constexpr float INIT_ALIEN_SPEED = 100;
const float INIT_ALIEN_POSITION_X = 30;
const float INIT_ALIEN_POSITION_Y = 30;

const std::string ALIEN_TEXTURE_FILE =
    "/home/krillin/code/nsu/23203_knyazkov/lab3/Assets/alien2.png";

class Alien {
public:
  virtual ~Alien() = default;
  virtual void update() = 0;
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual sf::FloatRect getBounds() const = 0;
  virtual sf::Sprite getSprite() const = 0;
  virtual void move(float dx, float dy) = 0;
  virtual void setPosition(float x, float y) = 0;
  virtual float getX() const = 0;
  virtual float getY() const = 0;
};

class BasicAlien : Alien {
public:
  BasicAlien();
  BasicAlien(float x, float y);
  void update() override;
  sf::FloatRect getBounds() const override;
  sf::Sprite getSprite() const override;
  void draw(sf::RenderWindow &window) override;
  void move(float dx, float dy) override;
  void setPosition(float x, float y) override;
  float getX() const override;
  float getY() const override;

private:
  sf::Vector2f m_position;

  sf::Sprite m_sprite;
  sf::Texture m_texture;

  float m_speed; // pixels per seconds
};
