// #include "Engine.hpp"
// #include <SFML/Window/Keyboard.hpp>


// void Engine::input(){
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
//         m_Window.close();
//     }

//     sf::Event event{};

//     m_inputState.clear();

//     while (m_Window.pollEvent(event)) {
//       if (event.type == sf::Event::Closed) {
//         m_Window.close();
//       }

//       if (event.type == sf::Event::KeyPressed) {
//         m_inputState[event.key.code] = true;
//       }

//       if (event.type == sf::Event::KeyReleased) {
//         m_inputState[event.key.code] = false;
//       }
//     }
// }
