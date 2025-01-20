#include "Engine.hpp"

void Engine::Engine::update(float dtAsSeconds){
    m_StateManager.update(dtAsSeconds, m_inputState);
}
