#include <termios.h>
#include <unistd.h>
#include "Game.h"

Game::Game() : _refreshRate(1 * Second), _foodTimer(25 * Second), _stage(Stage()), _currentState(Stopped) {}

void Game::start() {
  _currentState = Playing;
  int16_t key;

  while(_currentState != Stopped) {
    key = getch();

    switch (key) {
      case KEY_UP:
      case KEY_DOWN:
      case KEY_LEFT:
      case KEY_RIGHT:
        _stage.keyPressed(key);
        break;
      default:
        break;
    }
    _stage.update([this](GameState state){
      _currentState = state;
    });
    tcflush(STDIN_FILENO, TCIFLUSH);  // flush non-transmitted key strokes
    usleep(Second * 0.5);
  }
}


