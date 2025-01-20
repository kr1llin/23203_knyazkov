#include "Bullet.hpp"
#include "Collidable.hpp"
#include "GameEventListener.hpp"
#include "Object.hpp"
// #include "CollisionInterface.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

//
constexpr int PLAYER_SHOOT_PERIOD = 100;
constexpr float INIT_PLAYER_SPEED = 700;
const sf::Vector2f INIT_PLAYER_SIZE{80, 58};

const float INIT_PLAYER_POSITION_X = sf::VideoMode::getDesktopMode().width / 2;
const float INIT_PLAYER_POSITION_Y = sf::VideoMode::getDesktopMode().height -
                                     sf::VideoMode::getDesktopMode().height / 8;
//

// class Player : public Object, public ICollidable {
class Player : public Object, public ICollidable, public Subject {

public:
  // Player();
  Player() {
    m_id = objID::PLAYER_ID;
    m_size = INIT_PLAYER_SIZE;
    m_position.x = INIT_PLAYER_POSITION_X;
    m_position.y = INIT_PLAYER_POSITION_Y;
  };
  ~Player() = default;

  void update(float deltaTime) override;

  // ICollidable interface
  sf::Vector2f GetPosition() override { return m_position; }
  sf::Vector2f GetSize() override { return m_size; }

  void ProcessCollision(ICollidable *other) override;

  bool isDead() const { return m_isDead; }
  bool isShooting() const { return m_isShooting; }

  void kill() { m_isDead = true; }
  // const Magazine& GetMagazine() {return m_bullets;}
  std::vector<std::shared_ptr<PlayerBullet>> &getBullets() { return m_bullets; }

  void moveLeft();
  void moveRight();
  void stopLeft();
  void stopRight();
  void startShooting();
  void stopShooting();

private:
  bool m_isShooting = false;
  bool m_leftPressed = false;
  bool m_rightPressed = false;
  bool m_zPressed = false;
  int m_timeSinceLastBullet{};

  float m_Speed = INIT_PLAYER_SPEED; // pixels per seconds

  std::vector<std::shared_ptr<PlayerBullet>> m_bullets;
  // Magazine m_bullets;

  void shoot();
};
