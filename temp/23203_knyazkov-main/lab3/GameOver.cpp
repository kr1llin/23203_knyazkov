#include "State.hpp"
#include <SFML/Graphics/Font.hpp>
#include <iostream>

void GameOver::update(
    float dtAsSeconds,
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  handleInput(inputState);
    if (m_startAgain){
        notifyStartGame();
    }
}

void GameOver::draw(sf::RenderWindow &window) {
  window.clear(sf::Color::Black);

sf::Font font;
font.loadFromFile("/home/krillin/code/nsu/23203_knyazkov/lab3/Assets/ARCADECLASSIC.TTF");
sf::Text gameOverText;
gameOverText.setFont(font);
gameOverText.setString("Game Over");
gameOverText.setCharacterSize(200);
gameOverText.setFillColor(sf::Color::Red);
gameOverText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

window.draw(gameOverText);

sf::Text restartText;
restartText.setFont(font);
restartText.setString("Press  R  to Restart");
restartText.setCharacterSize(100);
restartText.setFillColor(sf::Color::White);
restartText.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 200);

window.draw(restartText);
window.display();
}

void GameOver::handleInput(
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  if (!(inputState.find(sf::Keyboard::R) == inputState.end()) && inputState.at(sf::Keyboard::R)) {
    m_startAgain = true;
  }
}

void GameOver::notifyStartGame() {
    for (auto& listener : m_listeners) {
      listener->onStartGame();
    }
}
