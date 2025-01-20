#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player() : m_Speed(INIT_PLAYER_SPEED) {
  if (!m_Texture.loadFromFile(PLAYER_TEXTURE_FILE)) {
    std::cerr << "Error loading texture from " << PLAYER_TEXTURE_FILE
              << std::endl;
  }
  m_Sprite.setTexture(m_Texture);

  m_Position.x = INIT_PLAYER_POSITION_X;
  m_Position.y = INIT_PLAYER_POSITION_Y;
  m_Sprite.setPosition(m_Position);
  m_timeSinceLastBullet = 0;
}

sf::Sprite Player::getSprite(){
    return m_Sprite;
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

void Player::update(float deltaTime){
    float Width = sf::VideoMode::getDesktopMode().width;
    char step_x = m_rightPressed - m_leftPressed; //1 is right, -1 if left, 0 if nothing
    m_Position.x = std::clamp<float>(m_Position.x + m_Speed*step_x*deltaTime, 0, Width - m_Sprite.getGlobalBounds().width);
    m_Sprite.setPosition(m_Position);
    shoot();
    updateBullets(deltaTime);

}

void Player::updateBullets(float deltaTime) {
    for (int i = m_bullets.size() - 1; i >= 0; i--) {
        m_bullets[i].update(deltaTime);
        // if (hasHitAlien(m_bullets[i])) {
        //     m_bullets.erase(m_bullets.begin() + i);
        // } else 
        if (m_bullets[i].isOffScreen()) {
            m_bullets.erase(m_bullets.begin() + i);
        }
    }
}

// bool Player::hasHitAlien(const PlayerBullet& bullet) {
//     return getInvaders.checkCollision(bullet.getX(), bullet.getY());
// }

// void Player::checkCollisions(CollisionInterface& collisionObject) {
//     return collisionObject.checkCollision(bullet.getX(), bullet.getY());
// }

 bool Player::checkCollision(float x, float y) {
     return x >= m_Position.x && x <= m_Position.x + m_Sprite.getGlobalBounds().width &&
         y >= m_Position.y && y <= m_Position.y + m_Sprite.getGlobalBounds().height;
 }


void Player::draw(sf::RenderWindow& window){
    drawBullets(window);
    window.draw(m_Sprite);
}

void Player::startShooting(){
    m_zPressed = true;
}
void Player::stopShooting(){
    m_zPressed = false;
}

void Player::shoot() {
    if (m_zPressed){
        stopShooting();
     m_bullets.emplace_back(m_Position.x + m_Sprite.getGlobalBounds().width / 2,
                         m_Position.y - m_Sprite.getGlobalBounds().height / 2);
    }
}

void Player::drawBullets(sf::RenderWindow& window) {
    for (const auto& bullet : m_bullets) {
        bullet.draw(window);
    }
}
