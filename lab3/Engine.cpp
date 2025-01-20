#include "Engine.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

//SEPARATE LOGIC FROM GUI (MAKE RENDERMODULE)

Engine::Engine() {
  m_RenderModule.init();
  m_StateManager.pushState(std::make_unique<Level>());
}

void Engine::start() {

  sf::Clock clock;
  // main game loop
  while (m_RenderModule.getWindow().isOpen()) {
    sf::Time dt = clock.restart();
    float dtAsSeconds = dt.asSeconds();
    input();
    update(dtAsSeconds);
    draw();
  }
}

void Engine::draw() {
  m_RenderModule.render(m_StateManager.getState()->getObjects());
}

void Engine::Engine::update(float dtAsSeconds) {
  m_StateManager.update(dtAsSeconds, m_inputState);
}

void Engine::input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    m_RenderModule.closeWindow();
  }

  sf::Event event{};

  m_inputState.clear();

  while (m_RenderModule.pollWindowEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_RenderModule.closeWindow();
    }

    if (event.type == sf::Event::KeyPressed) {
      m_inputState[event.key.code] = true;
    }

    if (event.type == sf::Event::KeyReleased) {
      m_inputState[event.key.code] = false;
    }
  }
}
