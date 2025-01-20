#pragma once
#include "StateManager.hpp"

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>


//handles main game's loop and its state
class Engine {
public:
  Engine();
  void start();

private:
  RenderModule m_RenderModule;
  StateManager m_StateManager;  // menu, options, level, etc.

  std::unordered_map<sf::Keyboard::Key, bool> m_inputState;

  void input(); // to be remade as InputManager
  void update(float dtAsSeconds);
  void draw(); // -//- RenderModule
};
