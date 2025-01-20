#include "Engine.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

Engine::Engine(){
  sf::Vector2f resolution;
  resolution.x = sf::VideoMode::getDesktopMode().width;
  resolution.y = sf::VideoMode::getDesktopMode().height;

  m_Window.create(sf::VideoMode(), "Space Invaders", sf::Style::Fullscreen);
  m_StateManager.pushState(std::make_unique<Level>());
}

void Engine::start(){

  sf::Clock clock;

  // main game loop
  while (m_Window.isOpen()) {
    sf::Time dt = clock.restart();
    float dtAsSeconds = dt.asSeconds();

    input();
    update(dtAsSeconds);
    draw();
  }
}
