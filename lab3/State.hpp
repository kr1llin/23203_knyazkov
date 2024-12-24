#include "Player.hpp"
#include "Invaders.hpp"
#include "Level.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>

class State {
public:
    State() {}
    virtual ~State() = default;
    virtual void update(float dtAsSeconds, const std::unordered_map<sf::Keyboard::Key, bool>& inputState) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& inputState) = 0;
protected:
//   sf::RenderWindow &m_Window;
};

class Level : public State{
public:
    Level() : isPaused(false){}
    void update(float dtAsSeconds, const std::unordered_map<sf::Keyboard::Key, bool>& inputState);
    void draw(sf::RenderWindow& window);
    void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& inputState);
    void updateObjects(float dtAsSeconds);

private:
  // sf::RenderWindow m_Window;
  bool isPaused;
  Player m_player;
  Invaders m_invaders;
};
