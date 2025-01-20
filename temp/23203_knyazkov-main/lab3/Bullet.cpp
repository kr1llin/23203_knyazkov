#include "Bullet.hpp"


Bullet::Bullet(float x, float y, float speed) : m_speed(speed) {
    m_shape.setSize(sf::Vector2f(BULLET_SIZE_X, BULLET_SIZE_Y));
    m_shape.setFillColor(sf::Color::White);
    m_position = sf::Vector2f(x, y);
    m_shape.setPosition(m_position);
}

void Bullet::update(float deltaTime) {
    m_shape.move(0, -m_speed * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
}

sf::FloatRect Bullet::getBounds() const {
    return m_shape.getGlobalBounds();
}

float Bullet::getX() const{
    return m_shape.getPosition().x;
}

float Bullet::getY() const{
    return m_shape.getPosition().y;
}


bool Bullet::isOffScreen() const {
  float Height = sf::VideoMode::getDesktopMode().height;
  return (*this).getY() >= Height;
}
