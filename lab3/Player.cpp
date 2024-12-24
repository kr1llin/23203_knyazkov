#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player(){
    m_Speed = INIT_PLAYER_SPEED;

    //  if (!m_Texture.loadFromFile(PLAYER_TEXTURE_FILE)) {
    //     std::cerr << "Error loading texture from " << PLAYER_TEXTURE_FILE << std::endl;
    // }
    // m_Sprite.setTexture(m_Texture);

    m_Rectangle.setSize(sf::Vector2f(50.0f, 50.0f));
    m_Rectangle.setFillColor(sf::Color::Green);

    m_Position.x = INIT_PLAYER_POSITION_X;
    m_Position.y = INIT_PLAYER_POSITION_Y;
    // m_Sprite.setPosition(m_Position);
    m_Rectangle.setPosition(m_Position);
}

sf::Sprite Player::getSprite(){
    return m_Sprite;
}

sf::RectangleShape Player::getRectangle(){ 
    return m_Rectangle;
}


// To be wrapped around in non-cringey way

void Player::moveLeft(){
    m_leftPressed = true;
}

void Player::moveRight(){
    m_rightPressed = true;
}

void Player::stopLeft(){
    m_leftPressed = false;
}

void Player::stopRight(){
    m_rightPressed = false;
}

void Player::update(float elapsedTime){
    if (m_rightPressed){
        m_Position.x += m_Speed * elapsedTime;
    }

    if (m_leftPressed){
        m_Position.x -= m_Speed*elapsedTime;
    }

    // m_Sprite.setPosition(m_Position);
    m_Rectangle.setPosition(m_Position);
}

void Player::draw(sf::RenderWindow& window){
    window.draw(m_Rectangle);
}
