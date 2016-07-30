#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "Point.h"

class Snake {
  enum Direction { L, R, U, D, None };

public:
  explicit Snake(Point const& startingPosition);
  Direction getDirection() const { return _currentDirection; }
  void update() const;
  void advance(bool consumeFood);
  void updateDirection(uint16_t direction);
  void calculateNextPosition();
  Point getNextPosition();
  std::deque<Point> getSnake() const { return _body; }
private:
  std::deque<Point> _body;
  Direction _currentDirection;
  Point _nextPosition;
  char _symbol;
};

#endif // SNAKE_H
