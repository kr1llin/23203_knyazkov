#include "Invaders.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <set>

const float Width = sf::VideoMode::getDesktopMode().width;
const float Height = sf::VideoMode::getDesktopMode().height;

std::vector<std::shared_ptr<Alien>> &Invaders::getAliens() {
  return m_aliens;
}

// void Invaders::draw(sf::RenderWindow &window) {
//   for (const auto &bullet : m_bullets) {
//     bullet.draw(window);
//   }

//   for (auto &alien : m_aliens) {
//     alien->draw(window);
//   }
// }

void Invaders::initAliens() {
  auto alien = std::make_shared<Alien>(); // for comparing
  float y = INIT_INVADERS_Y;
  for (int i = 0; i < m_rowsCount; i++) {
    for (float x = alien->GetSize().x * 2;
         x < Width - alien->GetSize().x* 2;
         x += alien->GetSize().x * 1.25) {
      m_aliens.emplace_back(std::make_shared<Alien>(x, y));
    }
    y += alien->GetSize().y * 2;
  }
}

bool Invaders::hasChangedDirection() {
  for (const auto &alien : m_aliens) {
    if (alien->GetPosition().x >= Width - alien->GetSize().x) {
      m_direction = 1;
      return true;
    } else if (alien->GetPosition().x <= 0) {
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
  float directionMultiplier = (m_direction == 0) ? 1.0F : -1.0F;
  std::for_each(
      m_aliens.begin(), m_aliens.end(),
      [directionMultiplier, deltaTime](std::shared_ptr<Alien> &alien) {
        alien->move(directionMultiplier * deltaTime, 0);
      });

  if (hasChangedDirection()) {
    moveAliensDown();
  }

  if (m_timeSinceLastBullet >= SHOOT_PERIOD) {
    auto bottomAliens = getBottomAliens();
    if (!bottomAliens.empty()) {
      makeABottomAlienShoot(bottomAliens);
    }
  }
  m_timeSinceLastBullet++;
}

std::vector<std::shared_ptr<Alien>> Invaders::getBottomAliens() {
  std::set<float> allXPositions;
  for (const auto &alien : m_aliens) {
    allXPositions.insert(alien->GetPosition().x);
  }

  std::vector<std::shared_ptr<Alien>> aliensAtTheBottom;
  for (float alienAtX : allXPositions) {
    float bestYPosition = 0;
    auto lowestAlien =
        std::make_shared<Alien>(0, 0); // aux alien to compare to
    for (const auto &alien : m_aliens) {
      if (alien->GetPosition().x == alienAtX) {
        if (alien->GetPosition().y > bestYPosition) {
          bestYPosition = alien->GetPosition().y;
          lowestAlien = std::make_shared<Alien>(alien->GetPosition().x,
                                                     alien->GetPosition().y);
          ;
        }
      }
    }
    aliensAtTheBottom.push_back(std::move(lowestAlien));
  }
  return aliensAtTheBottom;
}

void Invaders::makeABottomAlienShoot(
    const std::vector<std::shared_ptr<Alien>> &bottomAliens) {
  int index = rand() % bottomAliens.size();
  auto &shootingAlien = bottomAliens[index];
  AlienBullet bullet(shootingAlien->GetPosition().x + 10,
                     shootingAlien->GetPosition().y + 10);
  // m_bullets.pickUp(bullet);
  m_bullets.push_back(std::make_shared<AlienBullet>(bullet));
  m_timeSinceLastBullet = 0;
}

void Invaders::RemoveDeadAliens() {
  m_aliens.erase(std::remove_if(m_aliens.begin(), m_aliens.end(),
                                [](std::shared_ptr<Alien> &alien) {
                                  return !alien->isAlive();
                                }),
                 m_aliens.end());
}
