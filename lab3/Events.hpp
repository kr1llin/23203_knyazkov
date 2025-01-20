#pragma once
enum class Event { START_GAME, DEATH, LEVEL, PAUSED, GAME_OVER, EXIT, BULLET_UP, BULLET_DOWN};


// class Event {
// public:
//   enum GameState { START_GAME, LEVEL, PAUSED, GAME_OVER, EXIT};

//   Event(GameState state) : currentState(state) {}

//   GameState getCurrentState() const { return currentState; }
//   void setCurrentState(GameState state) { currentState = state; }

// private:
//   GameState currentState;
// };
