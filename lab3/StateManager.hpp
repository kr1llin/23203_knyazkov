#include "State.hpp"


#include <memory>
#include <stack>


class StateManager {
public:
  void pushState(std::unique_ptr<State> state);
  void popState();

  void changeState(std::unique_ptr<State> state);

  void update(float dtAsSeconds,
              const std::unordered_map<sf::Keyboard::Key, bool> &inputState);

  void draw(sf::RenderWindow& window);

  void
  handleInput(const std::unordered_map<sf::Keyboard::Key, bool> &inputState);

private:
  std::stack<std::unique_ptr<State>> m_States;
};

