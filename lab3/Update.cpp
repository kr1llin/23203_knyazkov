#include "Engine.hpp"

void Engine::Engine::update(float dtAsSeconds){
    m_StateManager.update(dtAsSeconds, m_inputState);
    
    // m_level.update(dtAsSeconds, m_inputState);
    // m_player.update(dtAsSeconds);
    // m_invaders.update(dtAsSeconds);
    
    //collission resolution
}
