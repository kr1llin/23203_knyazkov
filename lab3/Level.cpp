#include "State.hpp"

void Level::update(
    float dtAsSeconds,
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  handleInput(inputState);
  if (!isPaused) {
    updateObjects(dtAsSeconds);
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

//stupid!
void Level::handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& inputState) {
    if (!(inputState.find(sf::Keyboard::Left) == inputState.end())){
    if (inputState.at(sf::Keyboard::Left)) {
        m_player.moveLeft();
    } else {
        m_player.stopLeft();
    }
    }

    if (!(inputState.find(sf::Keyboard::Right) == inputState.end())){
    if (inputState.at(sf::Keyboard::Right)) {
        m_player.moveRight();
    } else {
        m_player.stopRight();
    }
    }

    if (!(inputState.find(sf::Keyboard::Z) == inputState.end())){
    if (inputState.at(sf::Keyboard::Z)) {
        // m_player.shoot();
    }
    }

    if (!(inputState.find(sf::Keyboard::Enter) == inputState.end())){
    if (inputState.at(sf::Keyboard::Enter)) {
        isPaused = !isPaused;
    }
    }

}

void Level::updateObjects(float dtAsSeconds) {
    m_player.update(dtAsSeconds);
    m_invaders.update(dtAsSeconds);
}


