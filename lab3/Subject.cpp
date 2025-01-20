#pragma once

#include "GameEventListener.hpp"
#include <algorithm>

void Subject::addListener(GameEventListener *listener) {
  if (listener) {
    m_listeners.push_back(listener);
  }
}

void Subject::removeListener(GameEventListener *listener) {
  m_listeners.erase(
      std::remove(m_listeners.begin(), m_listeners.end(), listener),
      m_listeners.end());
}

void Subject::notify(Event event) {
  for (auto &listener : m_listeners) {
    listener->onNotify(event);
  }
}
