#pragma once

#include "CollisionModule.hpp"
#include "Player.hpp"
#include "Invaders.hpp"
#include "GameEventListener.hpp"
#include "RenderModule.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>

class State : public Subject {
public:
    State() = default;
    virtual ~State() = default;
    virtual void update(float dtAsSeconds, const std::unordered_map<sf::Keyboard::Key, bool>& inputState) = 0;
    // virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& inputState) = 0;
    const std::vector<std::shared_ptr<Object>>& getObjects() const { return m_objects; }
  protected:
    std::vector<std::shared_ptr<Object>> m_objects;
};

class BulletObserver : GameEventListener {
public:
    virtual void onBulletAdded(std::shared_ptr<Object> bullet) = 0;
    virtual void onBulletRemoved(std::shared_ptr<Object> bullet) = 0;
};

class Level : public State{
public:
    Level();
    void update(float dtAsSeconds, const std::unordered_map<sf::Keyboard::Key, bool>& inputState) override;
    // void draw(sf::RenderWindow& window) override;
    void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& inputState) override;
    void updateObjects(float dtAsSeconds);
    void checkCollisions();

  private:
    CollisionModule collisionModule;
    
    //bad
    bool checkRestartGameCondition() const;
    bool checkGameOverCondition() const;
    bool deleteDeadObjects();

    std::vector<std::shared_ptr<Object>> getFlattenedObjects() const;
    void addObjectsToCollisionList(const std::vector<std::shared_ptr<Object>> &m_objects);
    void addObjectToCollisionList(const std::shared_ptr<Object> &obj);
    void removeObjectFromCollisionList(const std::shared_ptr<Object> &obj);

    Object *findObjectByID(const objID& id) const;
    template <typename BulletType>
    void addBulletToObjectsAndCollision(const std::shared_ptr<BulletType> &bullet);

    bool isPaused = false;
    bool isRestarted = false;

    std::shared_ptr<Player> m_player;

    };

    class GameOver : public State {
    public:
      GameOver() = default;
      void update(float dtAsSeconds,
                  const std::unordered_map<sf::Keyboard::Key, bool> &inputState)
          override;
      // void draw(sf::RenderWindow &window) override;
      void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>
                           &inputState) override;

    private:
      bool checkStartGameCondition() const;
      bool m_startAgain = false;
};

class Quit : public State {
public:
  Quit() = default;
  void update(
      float dtAsSeconds,
      const std::unordered_map<sf::Keyboard::Key, bool> &inputState) override;
  // void draw(sf::RenderWindow &window) override;
  void handleInput(
      const std::unordered_map<sf::Keyboard::Key, bool> &inputState) override;

private:
};
