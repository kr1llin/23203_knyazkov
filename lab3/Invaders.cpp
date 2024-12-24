#include "Invaders.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

float Width = sf::VideoMode::getDesktopMode().width;

std::vector<Alien> Invaders::getAliens() const { return m_aliens; }

void Invaders::draw(sf::RenderWindow &window) {
  for (auto &alien : m_aliens) {
    alien.draw(window);
  }
}

void Invaders::initAliens() {
//   if (!m_Texture.loadFromFile(ALIEN_TEXTURE_FILE)) {
//     std::cerr << "Error loading texture from " << ALIEN_TEXTURE_FILE
//               << std::endl;
//   }

//   m_Sprite.setTexture(m_Texture);

//   m_Sprite.setPosition(m_Position);
//   m_Sprite.setScale(0.3f, 0.3f);

  float y = INIT_INVADERS_Y;
  for (int i = 0; i < m_rowsCount; i++) {
    for (float x = rectSize.x*2; x < Width - rectSize.x*2; x += rectSize.x * 1.25) {
      m_aliens.emplace_back(x, y);
    }
    y += rectSize.y * 2;
  }
}

bool Invaders::hasChangedDirection() {
  for (const auto &alien : m_aliens) {
    if (alien.getX() >= Width - rectSize.x) {
      m_direction = 1;
      return true;
    } else if (alien.getX() <= 0) {
      m_direction = 0;
      return true;
    }
  }
  return false;
}

 void Invaders::moveAliensDown(float dtAsSeconds) {
   for (auto &alien : m_aliens) {
     alien.move(0, 5);
   }
 }

 void Invaders::update(float dtAsSeconds) {
   for (auto &alien : m_aliens) {
     if (m_direction == 0) {
       alien.move(dtAsSeconds,0);
     } else if (m_direction == 1) {
       alien.move(-dtAsSeconds, 0);
     }
   }

   if (hasChangedDirection()) {
     moveAliensDown(dtAsSeconds);
     std::cout << "Changed!\n";
   }
 }
