#pragma once

#include "Player.hpp"
#include "Invaders.hpp"
#include "Level.hpp"
#include "GameEventListener.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>
#include <vector>

class State {
public:
    State() = default;
    virtual ~State() = default;
    virtual void update(float dtAsSeconds, const std::unordered_map<sf::Keyboard::Key, bool>& inputState) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& inputState) = 0;
    void addListener(GameEventListener *listener) {
      if (listener) {
        m_listeners.push_back(listener);
      }
    }

protected:
    std::vector<GameEventListener*> m_listeners;
//   sf::RenderWindow &m_Window;
};

class Level : public State{
public:
    Level() = default;
    void update(float dtAsSeconds, const std::unordered_map<sf::Keyboard::Key, bool>& inputState) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& inputState) override;
    void updateObjects(float dtAsSeconds);
    void checkCollisions();
    void addListener(GameEventListener* listener) {
      m_listeners.push_back(listener);
    }

  private:
    void notifyRestartGame();
    void notifyGameOver();
    bool checkRestartGameCondition() const;
    bool checkGameOverCondition() const;
    bool isPaused = false;
    bool isRestarted = false;
    Player m_player;
    Invaders m_invaders;
};

class GameOver : public State {
public:
  GameOver() = default;
  void update(
      float dtAsSeconds,
      const std::unordered_map<sf::Keyboard::Key, bool> &inputState) override;
  void draw(sf::RenderWindow &window) override;
  void handleInput(
      const std::unordered_map<sf::Keyboard::Key, bool> &inputState) override;
  void addListener(GameEventListener *listener) {
    m_listeners.push_back(listener);
  }

private:
  void notifyStartGame();
  bool checkStartGameCondition() const;
  bool m_startAgain = false;
};
