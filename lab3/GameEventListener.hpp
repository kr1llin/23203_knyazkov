#pragma once
#include "Events.hpp"
#include <vector>

// ObserverInterface
class GameEventListener {
public:
  virtual ~GameEventListener() = default;
  virtual void onNotify(Event event) = 0;
};

// Subject (observable interface)
class Subject {
public:
  virtual ~Subject() {}

  void addListener(GameEventListener *listener);
  void removeListener(GameEventListener *listener);
  void notify(Event event);

private:
  std::vector<GameEventListener *> m_listeners;
};
