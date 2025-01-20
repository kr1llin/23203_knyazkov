#include "State.hpp"

void Level::update(
    float dtAsSeconds,
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  handleInput(inputState);
  if (!isPaused) {
    checkCollisions();
    updateObjects(dtAsSeconds);
    if (checkGameOverCondition()) {
      notifyGameOver();
    }
    if (checkRestartGameCondition()){
      notifyRestartGame();
    }
  }
}

void Level::checkCollisions() {
  for (int i = m_player.getBullets().size() - 1; i >= 0; i--) {
    if (m_invaders.checkCollision(m_player.getBullets()[i].getX(),
                                  m_player.getBullets()[i].getY())) {
      m_player.getBullets().erase(m_player.getBullets().begin() + i);
    }
  }

  for (int i = m_invaders.getBullets().size() - 1; i >= 0; i--) {
    if (m_player.checkCollision(m_invaders.getBullets()[i].getX(),
                                m_invaders.getBullets()[i].getY())) {
      m_player.kill();
    }
  }
}

void Level::draw(sf::RenderWindow &window) {
  if (!isPaused) {
    window.clear(sf::Color::Black);
    m_player.draw(window);
    m_invaders.draw(window);
    window.display();
  }
}

// stupid!
void Level::handleInput(
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  if (!(inputState.find(sf::Keyboard::Left) == inputState.end())) {
    if (inputState.at(sf::Keyboard::Left)) {
      m_player.moveLeft();
    } else {
      m_player.stopLeft();
    }
  }

  if (!(inputState.find(sf::Keyboard::Right) == inputState.end())) {
    if (inputState.at(sf::Keyboard::Right)) {
      m_player.moveRight();
    } else {
      m_player.stopRight();
    }
  }

  if (!(inputState.find(sf::Keyboard::Z) == inputState.end())) {
    if (inputState.at(sf::Keyboard::Z)) {
      m_player.startShooting();
    }
    else {
        m_player.stopShooting();
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

void Level::updateObjects(float dtAsSeconds) {
  m_player.update(dtAsSeconds);
  m_invaders.update(dtAsSeconds);
}

//make just notify and send enum of states
void Level::notifyGameOver() {
    for (auto& listener : m_listeners) {
      listener->onGameOver();
    }
}

void Level::notifyRestartGame() {
    for (auto& listener : m_listeners) {
      listener->onStartGame();
    }
}

bool Level::checkGameOverCondition() const { return m_player.isDead(); }
bool Level::checkRestartGameCondition() const { return isRestarted; }

