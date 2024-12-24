#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

constexpr float INIT_PLAYER_SPEED = 50;
const float INIT_PLAYER_POSITION_X = sf::VideoMode::getDesktopMode().width / 2;
const float INIT_PLAYER_POSITION_Y = sf::VideoMode::getDesktopMode().height - sf::VideoMode::getDesktopMode().height / 8;


const std::string PLAYER_TEXTURE_FILE = "./Assets/player.png";

class Player {
public:
    Player();
    sf::Sprite getSprite();
    sf::RectangleShape getRectangle();

    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight(); 

    //to be called from update() of the Engine
    void update(float elapsed_time);
    void draw(sf::RenderWindow &window);
private:
    sf::Vector2f m_Position;
    sf::RectangleShape m_Rectangle; //placeholder

    sf::Sprite m_Sprite;
    sf::Texture m_Texture;

    bool m_leftPressed = false;
    bool m_rightPressed = false;
    bool m_zPressed = false;

    float m_Speed; //pixels per seconds
};
