#include "Engine.hpp"
#include <SFML/Graphics/Color.hpp>

void Engine::draw(){

    m_StateManager.draw(m_Window);

}
