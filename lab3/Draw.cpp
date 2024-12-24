#include "Engine.hpp"
#include <SFML/Graphics/Color.hpp>

void Engine::draw(){

    m_StateManager.draw(m_Window);
    // m_level.draw(m_Window);
    //std::for_each(..,..,draw) objects
    // m_Window.draw(m_player.getRectangle());
    // m_invaders.draw(m_Window);

    // m_Window.display();
}
