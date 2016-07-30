#ifndef FOOD_H
#define FOOD_H

#include <ncurses.h>
#include "Point.h"

enum GameState { Playing, Paused, Stopped };

class Food
{
public:
  explicit Food(Point const& point) : _position(point), _symbol('*') {}

  void setPosition(Point const& point) {
    _position = point;

    mvaddch(_position.getY(), _position.getX(), _symbol);
    refresh();
  }

  Point getPosition() const {
    return _position;
  }

  void expire() {
    mvaddch(_position.getY(), _position.getX(), ' ');
    refresh();

    _position = Point(0, 0);
  }

private:
  Point _position;
  char _symbol;
};

#endif // FOOD_H
