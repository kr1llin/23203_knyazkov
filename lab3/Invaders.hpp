#include "Alien.hpp"
#include "Bullet.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

constexpr float INIT_INVADERS_SPEED = INIT_ALIEN_SPEED;
constexpr int INIT_INVADERS_ROWS =  4;
const float INIT_INVADERS_X = 0;
const float INIT_INVADERS_Y = 0;

class Invaders{
public:
  Invaders() : m_rowsCount(INIT_INVADERS_ROWS), m_direction(0){
    initAliens();
  }

  void initAliens();
  std::vector<Alien> getAliens() const;
  bool hasChangedDirection();
  void moveAliensDown(float dtAsSeconds);

  void update(float dtAsSeconds);

  void draw(sf::RenderWindow &window);

private:
  int m_rowsCount;
  bool m_direction; // 0 for right, 1 for left
  float m_y;

  std::vector<Alien> m_aliens;
  std::vector<Bullet> m_Bullets;
  sf::Vector2f m_Position;

  sf::Sprite m_Sprite;
  sf::Texture m_Texture;

  float m_Speed; // pixels per seconds
};
