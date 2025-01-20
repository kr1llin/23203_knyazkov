#pragma once
#include "Events.hpp"
#include "State.hpp"

#include <memory>
#include <stack>

class StateManager : GameEventListener {
public:
  void pushState(std::unique_ptr<State> state);
  void popState();

  void changeState(std::unique_ptr<State> state);

  void update(float dtAsSeconds,
              const std::unordered_map<sf::Keyboard::Key, bool> &inputState);

  // void draw(sf::RenderWindow &window);
  const std::unique_ptr<State>& getState() const {return m_States.top();}
  void
  handleInput(const std::unordered_map<sf::Keyboard::Key, bool> &inputState);

  void onNotify(Event event) override;
  //
  // void onGameOver() override { changeState(std::make_unique<GameOver>()); }
  // void onStartGame() override {changeState(std::make_unique<Level>()); }

private:
  std::stack<std::unique_ptr<State>> m_States;
};
