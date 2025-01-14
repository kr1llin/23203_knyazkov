#include "Bullet.hpp"
// #include "CollisionInterface.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

constexpr float INIT_PLAYER_SPEED = 700;
const float INIT_PLAYER_POSITION_X = sf::VideoMode::getDesktopMode().width / 2;
const float INIT_PLAYER_POSITION_Y = sf::VideoMode::getDesktopMode().height - sf::VideoMode::getDesktopMode().height / 8;


const std::string PLAYER_TEXTURE_FILE = "/home/krillin/code/nsu/23203_knyazkov/lab3/Assets/player.png";

class Player{
public:
    Player();
    sf::Sprite getSprite();
    sf::RectangleShape getRectangle();

    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight(); 
    void startShooting();
    void stopShooting();
    
    bool hasHitAlien(const PlayerBullet& bullet);
    // void checkCollisions(CollisionInterface& collisionObject) override;
    bool checkCollision(float x, float y);
    bool isDead() const {return m_isDead;}
    void kill() {m_isDead = true;}
    std::vector<PlayerBullet> &getBullets() { return m_bullets; }
    void hitAlien() const{}

    //to be called from update() of the Engine
    void update(float elapsed_time);
    void draw(sf::RenderWindow &window);
private:
    sf::Vector2f m_Position;

    sf::Sprite m_Sprite;
    sf::Texture m_Texture;

    bool m_isDead = false;
    bool m_leftPressed = false;
    bool m_rightPressed = false;
    bool m_zPressed = false;
    int m_timeSinceLastBullet;

    float m_Speed; //pixels per seconds

    std::vector<PlayerBullet> m_bullets;

    void shoot();
    void updateBullets(float deltaTime);    
    void drawBullets(sf::RenderWindow &window);
};
