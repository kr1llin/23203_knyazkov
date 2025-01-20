#include "Bullet.hpp"
#include "CollisionModule.hpp"
#include "Invaders.hpp"
#include "Object.hpp"
#include "State.hpp"
#include "Subject.hpp"
#include <iostream>
#include <memory>

Level::Level() {
  auto invaders = std::make_shared<Invaders>();
  // add to objects
  std::for_each(invaders->getAliens().begin(), invaders->getAliens().end(),
                [&](std::shared_ptr<Alien>& invader) {
                  m_objects.emplace_back(invader);
                });
  m_objects.emplace_back(invaders);
  m_player = std::make_shared<Player>();
  m_objects.emplace_back(m_player);
  // add to collission
  addObjectsToCollisionList(m_objects);
}

void Level::update(
    float dtAsSeconds,
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  handleInput(inputState);
  if (!isPaused) {
    collisionModule.CheckCollisionList();
    updateObjects(dtAsSeconds);

    if (checkGameOverCondition()) {
      notify(Event::GAME_OVER);
      return;
    }
    if (checkRestartGameCondition()) {
      notify(Event::START_GAME);
      return;
    }
  }
}

void Level::updateObjects(float dtAsSeconds) {
  for (auto it = m_objects.begin(); it != m_objects.end();) {
    if (!(*it)->isDead()) {
      (*it)->update(dtAsSeconds);
      ++it;
    } else {
      removeObjectFromCollisionList(*it);
      it = m_objects.erase(it);
    }
  }

//
  for (const auto &bullet : m_player->getBullets()) {
    addBulletToObjectsAndCollision(bullet);
  }

  auto *invaders = dynamic_cast<Invaders *>(findObjectByID(objID::INVADERS_ID));

  if (invaders) {
    for (const auto &bullet : invaders->getBullets()) {
      addBulletToObjectsAndCollision(bullet);
    }
  }
}

template <typename BulletType>
void Level::addBulletToObjectsAndCollision(
    const std::shared_ptr<BulletType> &bullet) {
  if (!bullet->isAddedToObjects()) {
    m_objects.push_back(bullet);
    collisionModule.AddToCollisionList(bullet.get());
    bullet->AddedToObjects();
  }
}

Object * Level::findObjectByID(const objID& id) const {
  auto it = std::find_if(
      m_objects.begin(), m_objects.end(),
      [id](const std::shared_ptr<Object> &obj) { return obj->getID() == id; });
  if (it != m_objects.end()) {
    return it->get();
  }
  return nullptr;
}

bool Level::checkGameOverCondition() const {
  return m_player->isDead();
}
bool Level::checkRestartGameCondition() const { return isRestarted; }


void Level::handleInput(
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  if (!(inputState.find(sf::Keyboard::Left) == inputState.end())) {
    if (inputState.at(sf::Keyboard::Left)) {
      m_player->moveLeft();
    } else {
      m_player->stopLeft();
    }
  }

  if (!(inputState.find(sf::Keyboard::Right) == inputState.end())) {
    if (inputState.at(sf::Keyboard::Right)) {
      m_player->moveRight();
    } else {
      m_player->stopRight();
    }
  }

  if (!(inputState.find(sf::Keyboard::Z) == inputState.end())) {
    if (inputState.at(sf::Keyboard::Z)) {
      m_player->startShooting();
    }
    else {
        m_player->stopShooting();
    }
  }

  if (!(inputState.find(sf::Keyboard::R) == inputState.end())) {
    if (inputState.at(sf::Keyboard::R)) {
      isRestarted = true;
    }
  }

  if (!(inputState.find(sf::Keyboard::Enter) == inputState.end())) {
    if (inputState.at(sf::Keyboard::Enter)) {
      isPaused = !isPaused;
    }
  }
}

void Level::addObjectsToCollisionList(const std::vector<std::shared_ptr<Object>> &m_objects) {
  std::for_each(m_objects.begin(), m_objects.end(), [this](const std::shared_ptr<Object>& obj) {
    if (obj) {
      auto *collidable = dynamic_cast<ICollidable *>(obj.get());
      if (collidable) { 
        collisionModule.AddToCollisionList(collidable);
      }
    }
  });
}

void Level::addObjectToCollisionList(const std::shared_ptr<Object> &obj) {
  if (obj) {
    auto *collidable = dynamic_cast<ICollidable *>(obj.get());
    if (collidable) {
      collisionModule.AddToCollisionList(collidable);
    }
  }
}

void Level::removeObjectFromCollisionList(const std::shared_ptr<Object> &obj) {
  if (obj) {
    auto *collidable = dynamic_cast<ICollidable *>(obj.get());
    if (collidable) {
      collisionModule.RemoveFromCollisionList(collidable);
    }
  }
}

// void Level::checkCollisions() {
//   for (int i = m_player.getBullets().size() - 1; i >= 0; i--) {
//     if (m_invaders.checkCollision(m_player.getBullets()[i].getX(),
//                                   m_player.getBullets()[i].getY())) {
//       m_player.getBullets().erase(m_player.getBullets().begin() + i);
//     }
//   }

//   for (int i = m_invaders.getBullets().size() - 1; i >= 0; i--) {
//     if (m_player.checkCollision(m_invaders.getBullets()[i].getX(),
//                                 m_invaders.getBullets()[i].getY())) {
//       m_player.kill();
//     }
//   }
// }
