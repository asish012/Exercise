#ifndef STAGE_H
#define STAGE_H

#include "Food.h"
#include "Point.h"
#include "Snake.h"

#define Second 1000000

class Stage
{
public:
  explicit Stage();
  ~Stage() { terminate(); }

  void init() const;      // init ncurses
  void terminate() const; // terminate ncurses
  void setup() const;     // draw stage
  void update(std::function<void(GameState)> changeGameState); // update with interval
  void addFood();         // addFood '*'
  void keyPressed(uint16_t key);
  void score();

private:
  uint8_t _width;
  uint8_t _height;
  uint16_t _score;
  Snake _snake;
  Food _food;
};

#endif // STAGE_H
