#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
  explicit Point() : _x(0), _y(0) {}
  explicit Point(uint8_t const x, uint8_t const y) : _x(x), _y(y) {}
  Point(Point const& other) { _x = other.getX(); _y = other.getY(); }

  uint8_t getX() const { return _x; }
  uint8_t getY() const { return _y; }

private:
  uint8_t _x;
  uint8_t _y;
};

#endif // POINT_H
