#ifndef GAME_H
#define GAME_H

#include "Stage.h"

class Game
{
public:

  explicit Game();
  ~Game() {}
  void update(uint16_t key);
  void start();

private:
  uint32_t _foodTimer;
  uint32_t _refreshRate;
  Stage _stage;
  GameState _currentState;
};

#endif // GAME_H
