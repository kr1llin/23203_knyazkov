#pragma once
#include "StateManager.hpp"

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>

//handles main game's loop and state
class Engine {
public:
  Engine();
  void start();

private:
  sf::RenderWindow m_Window;
  std::unordered_map<sf::Keyboard::Key, bool> m_inputState;

  StateManager m_StateManager;  // menu, options, level, etc.

  void input();
  void update(float dtAsSeconds);
  void draw();
};
