#include "Engine.hpp"

#include <SFML/Window/Keyboard.hpp>


void Engine::input(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        m_Window.close();
    }

    sf::Event event{};

    m_inputState.clear();

    while (m_Window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_Window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
        m_inputState[event.key.code] = true;
      }

      if (event.type == sf::Event::KeyReleased) {
        m_inputState[event.key.code] = false;
      }
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    //     m_inputState[]
    //     m_player.moveLeft();
    // }
    // else{
    //     m_player.stopLeft();
    // }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    //     m_player.moveRight();
    // }
    // else{
    //     m_player.stopRight();
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
    //     // m_player.shoot();
    // }
}
