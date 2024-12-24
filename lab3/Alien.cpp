#include "Alien.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

Alien::Alien(float x, float y){
  m_Speed = INIT_ALIEN_SPEED;

//   if (!m_Texture.loadFromFile(ALIEN_TEXTURE_FILE)) {
//     std::cerr << "Error loading texture from " << ALIEN_TEXTURE_FILE
//               << std::endl;
//   }

//   m_Sprite.setTexture(m_Texture);

  m_Position.x = x; 
  m_Position.y = y;

  m_Rectangle.setSize(rectSize);
  m_Rectangle.setFillColor(sf::Color(200,255,200));
  m_Rectangle.setPosition(m_Position);

    // m_Sprite.setPosition(m_Position);
    // m_Sprite.setScale(0.3f, 0.3f);
}

const sf::Sprite Alien::getSprite() const{
    return m_Sprite;
}

sf::FloatRect Alien::getBounds() const { 
    return m_Rectangle.getGlobalBounds();
    // return m_Sprite.getGlobalBounds();
}

void Alien::move(float dx, float dy) { 
    m_Position.x += dx * m_Speed;
    m_Position.y += dy * m_Speed;
    
    m_Rectangle.setPosition(m_Position);

    std::cout << "Setted Alien position is " << m_Position.x << " " << m_Position.y << std::endl;
}

void Alien::update(float elapsedTime){
    // if (m_rightPressed){
    //     m_Position.x += m_Speed * elapsedTime;
    // }

    // if (m_leftPressed){
    //     m_Position.x -= m_Speed*elapsedTime;
    // }

    // m_Sprite.setPosition(m_Position);
    m_Rectangle.setPosition(m_Position);
}

const sf::RectangleShape Alien::getRectangle() const{
    return m_Rectangle;
}

void Alien::draw(sf::RenderWindow &window) { 
    // window.draw(m_Sprite); 
    window.draw(m_Rectangle);
}

float Alien::getX() const {
  return m_Position.x;
}

