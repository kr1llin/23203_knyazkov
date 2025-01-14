#include "Invaders.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <memory>
#include <set>

const float Width = sf::VideoMode::getDesktopMode().width;
const float Height = sf::VideoMode::getDesktopMode().height;


const std::vector<std::unique_ptr<BasicAlien>>& Invaders::getAliens() const { return m_aliens; }

void Invaders::draw(sf::RenderWindow &window) {
  for (const auto &bullet : m_bullets) {
    bullet.draw(window);
  }

  for (auto &alien : m_aliens) {
    alien->draw(window);
  }
}

void Invaders::initAliens() {
  auto alien = std::make_unique<BasicAlien>(); // for comparing
  float y = INIT_INVADERS_Y;
  for (int i = 0; i < m_rowsCount; i++) {
    for (float x = alien->getBounds().width*2; x < Width - alien->getBounds().width*2; x += alien->getBounds().width * 1.25) {
      m_aliens.emplace_back(std::make_unique<BasicAlien>(x,y));
    }
    y += alien->getBounds().height * 2;
  }
}

bool Invaders::hasChangedDirection() {
  for (const auto &alien : m_aliens) {
    if (alien->getX() >= Width - alien->getBounds().width) {
      m_direction = 1;
      return true;
    } else if (alien->getX() <= 0) {
      m_direction = 0;
      return true;
    }
  }
  return false;
}

 void Invaders::moveAliensDown() {
   for (auto &alien : m_aliens) {
     alien->move(0, 0.5);
   }
 }

 void Invaders::update(float deltaTime) {
   for (auto &alien : m_aliens) {
     if (m_direction == 0) {
       alien->move(deltaTime,0);
     } else if (m_direction == 1) {
       alien->move(-deltaTime, 0);
     }
   }

   if (hasChangedDirection()) {
     moveAliensDown();
   }

    if (m_timeSinceLastBullet >= 1000) {
        auto bottomAliens = getBottomAliens();
        if (!bottomAliens.empty()) {
            makeABottomAlienShoot(bottomAliens);
        }
    }
    m_timeSinceLastBullet++;

    updateBullets(deltaTime);
 }

 std::vector<std::unique_ptr<BasicAlien>> Invaders::getBottomAliens() {
   std::set<float> allXPositions;
   for (const auto &alien : m_aliens) {
     allXPositions.insert(alien->getX());
   }

   std::vector<std::unique_ptr<BasicAlien>> aliensAtTheBottom;
   for (float alienAtX : allXPositions) {
     float bestYPosition = 0;
     auto lowestAlien = std::make_unique<BasicAlien>(0, 0); // aux alien to compare to
     for (const auto &alien : m_aliens) {
       if (alien->getX() == alienAtX) {
         if (alien->getY() > bestYPosition) {
           bestYPosition = alien->getY();
           lowestAlien = std::make_unique<BasicAlien>(alien->getX(), alien->getY());;
         }
       }
     }
     aliensAtTheBottom.push_back(std::move(lowestAlien));
   }
   return aliensAtTheBottom;
 }

 void Invaders::makeABottomAlienShoot(const std::vector<std::unique_ptr<BasicAlien>> &bottomAliens) {
   int index = rand() % bottomAliens.size();
   auto &shootingAlien = bottomAliens[index];
   AlienBullet bullet(shootingAlien->getX() + 10, shootingAlien->getY() + 10);
   m_bullets.push_back(bullet);
   m_timeSinceLastBullet = 0;
 }

 void Invaders::updateBullets(float deltaTime) {
   for (int i = m_bullets.size() - 1; i >= 0; i--) {
     m_bullets[i].update(deltaTime);
     if (m_bullets[i].isOffScreen()) {
       m_bullets.erase(m_bullets.begin() + i);
     }
   }
 }

 bool Invaders::checkCollision(float x, float y) {
   for (int i = m_aliens.size() - 1; i >= 0; i--) {
     auto &currentAlien = m_aliens[i];
     sf::FloatRect alienBounds = currentAlien->getBounds();
     if (x >= currentAlien->getX() && x <= currentAlien->getX() + alienBounds.width &&
         y >= currentAlien->getY() && y <= currentAlien->getY() + alienBounds.height) {
       m_aliens.erase(m_aliens.begin() + i);
       return true;
     }
   }
   return false;
 }

