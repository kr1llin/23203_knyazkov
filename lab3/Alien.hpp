#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/VideoMode.hpp>

const sf::Vector2 rectSize = sf::Vector2f(70.0f, 70.0f);

constexpr float INIT_ALIEN_SPEED = 5;
const float INIT_ALIEN_POSITION_X = 30;
const float INIT_ALIEN_POSITION_Y = 30;

const std::string ALIEN_TEXTURE_FILE = "/home/krillin/code/nsu/23203_knyazkov/lab3/Assets/alien2.png";


class Alien{
public:
  Alien(float x, float y);
  sf::RectangleShape getRectangle();
  void update(float elapsed_time);
  const sf::Sprite getSprite() const;
  const sf::RectangleShape getRectangle() const;
  sf::FloatRect getBounds() const;
  void move(float dx, float dy);
  float getX() const;
  void draw(sf::RenderWindow& window);

  private:
    sf::Vector2f m_Position;
    sf::RectangleShape m_Rectangle; // placeholder

    sf::Sprite m_Sprite;
    sf::Texture m_Texture;

    float m_Speed; // pixels per seconds
  };
