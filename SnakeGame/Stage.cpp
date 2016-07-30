#include <ctime>
#include <sstream>
#include "Stage.h"

Stage::Stage() : _width(80), _height(30), _snake(Snake(Point(_width/2, _height/2))), _food(Point()), _score(0) {
  init();
  setup();
  addFood();
}

void Stage::init() const {
  initscr();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  curs_set(0);
  noecho();
  // getmaxyx(stdscr, height, width);
}

void Stage::terminate() const {
  std::string msg("Game Over");
  mvaddstr(_height + 1, _width / 2 - msg.length() / 2, msg.c_str());
  refresh();

  nodelay(stdscr, false);
  getchar();
  endwin();
}

void Stage::setup() const {
  char const border = (char)219;

  // Draw top border
  for (int i = 0; i < _width; ++i) {
    mvaddch(0, i, border);
  }
  // Draw bottom border
  for (int i = 0; i < _width; ++i) {
    mvaddch(_height, i, border);
  }
  // Draw left border
  for (int i = 1; i < _height; ++i) {
    mvaddch(i, 0, border);
  }
  // Draw right border
  for (int i = 1; i < _height; ++i) {
    mvaddch(i, _width - 1, border);
  }

  mvaddstr(_height + 1, 0, "Score: 0");

  refresh();
}

void Stage::addFood() {
  uint8_t x, y;
  bool conflict = true;
  while (conflict) {
    std::srand(std::time(0));
    x = std::rand() % (_width - 1) + 1;
    y = std::rand() % (_height - 1) + 1;

    for (Point p: _snake.getSnake()) {
      if (p.getX() == x and p.getY() == y) {
        conflict = true;
        break;
      }
      conflict = false;
    }
  }

  _food.setPosition(Point(x, y));
}

void Stage::update(std::function<void(GameState)> changeGameState) {
  std::deque<Point> const &snake = _snake.getSnake();
  Point const &head = snake.front();

  if (head.getX() == _food.getPosition().getX() and
      head.getY() == _food.getPosition().getY()) {
    _snake.advance(true);
    score();
    addFood();
  }
  else {
    _snake.advance(false);
  }

  // check collision with boundaries
  if (checkBorderCollision()) {
    changeGameState(GameState::Stopped);
  }

  // check self collision
//  auto i = snake.begin();
//  if (i != snake.end()) { ++i; }
//  for (; i != snake.end(); ++i) {
//    if (head.getX() == i->getX() and head.getY() == i->getY()) {
//      fp(GameState::Stopped);
//    }
//  }
}

void Stage::keyPressed(uint16_t key) {
  _snake.updateDirection(key);
}

bool Stage::checkBorderCollision() {
  Point head = _snake.getSnake().front();
  if ((head.getX() > 0 and head.getX() < _width) and
      (head.getY() > 0 and head.getY() < _height)) {

    return false;
  }
  return true;
}

void Stage::score() {
  _score++;
  std::string str = "Score: " + std::to_string(_score);
  mvaddstr(_height + 1, 0, str.c_str());
  refresh();
}











