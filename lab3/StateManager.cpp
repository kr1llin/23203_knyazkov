#include "StateManager.hpp"
#include <memory>
#include <stack>

void StateManager::pushState(std::unique_ptr<State> state) {
  m_States.push(std::move(state));
}

void StateManager::popState() {
  if (!m_States.empty()) {
    m_States.pop();
  }
}

void StateManager::changeState(std::unique_ptr<State> state) {
  if (!m_States.empty()) {
    m_States.pop();
  }
  m_States.push(std::move(state));
}

void StateManager::update(
    float dtAsSeconds,
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  if (!m_States.empty()) {
    m_States.top()->update(dtAsSeconds, inputState);
  }
}

void StateManager::draw(sf::RenderWindow& window) {
  if (!m_States.empty()) {
    m_States.top()->draw(window);
  }
}

void StateManager::handleInput(
    const std::unordered_map<sf::Keyboard::Key, bool> &inputState) {
  if (!m_States.empty()) {
    m_States.top()->handleInput(inputState);
  }
}
