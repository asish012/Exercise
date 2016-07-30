#include <ncurses.h>
#include "Snake.h"

Snake::Snake(Point const& startingPosition) : _symbol('x'), _currentDirection(Direction::L) {
  for (int i = 0; i < 5; ++i) {
    _body.push_back(Point(startingPosition.getX() + i, startingPosition.getY()));
  }
}

void Snake::update() const {
  for (Point p: _body)
  {
    move(p.getY(), p.getX());
    addch(_symbol);
  }
  refresh();
}

void Snake::updateDirection(uint16_t direction) {
  switch (direction) {
    case KEY_LEFT:
      if (_currentDirection != Direction::R) {
        _currentDirection = Direction::L;
      }
      break;

    case KEY_RIGHT:
      if (_currentDirection != Direction::L) {
        _currentDirection = Direction::R;
      }
      break;

    case KEY_UP:
      if (_currentDirection != Direction::D) {
        _currentDirection = Direction::U;
      }
      break;

    case KEY_DOWN:
      if (_currentDirection != Direction::U) {
        _currentDirection = Direction::D;
      }
      break;
    default:
      break;
  }
}

void Snake::advance(bool consumed) {
  Point newPosition;

  switch (_currentDirection) {
    case Direction::L:
        newPosition = Point(_body.front().getX() - 1, _body.front().getY());
      break;

    case Direction::R:
        newPosition = Point(_body.front().getX() + 1, _body.front().getY());
      break;

    case Direction::U:
        newPosition = Point(_body.front().getX(), _body.front().getY() - 1);
      break;

    case Direction::D:
        newPosition = Point(_body.front().getX(), _body.front().getY() + 1);
      break;
    default:
      break;
  }


  mvaddch(newPosition.getY(), newPosition.getX(), _symbol); // add head
  _body.push_front(Point(newPosition.getX(), newPosition.getY()));

  if (not consumed) {
    mvaddch(_body.back().getY(), _body.back().getX(), ' ');    // clear tail
    _body.pop_back();
  }

  update();
}
