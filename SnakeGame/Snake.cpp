#include <iostream>
#include <string>
#include <unistd.h>
#include <ncurses.h>

void ncurses_setup() {
    initscr();
    // nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);
    noecho();
    // getmaxyx(stdscr, height, width);
}

void ncurses_end() {
    getchar();
    endwin();
}

void stage_setup() {
    int8_t width(50), height(30);
    char border = (char)219;

    // Draw top border
    for (int i = 0; i < width; ++i) {
        move(0, i);
        addch(border);
    }
    // Draw bottom border
    for (int i = 0; i < width; ++i) {
        move(height, i);
        addch(border);
    }
    // Draw left border
    for (int i = 1; i < height; ++i) {
        move(i, 0);
        addch(border);
    }
    // Draw right border
    for (int i = 1; i < height; ++i) {
        move(i, width-1);
        addch(border);
    }

    refresh();
}

void move_snake() {
    int8_t x(2), y(10);
    while(getch()) {
        move(y, ++x);
        addch((char)219);
        refresh();
        usleep(2000000);
    }
}

int main()
{
    ncurses_setup();
    stage_setup();

    move_snake();

    ncurses_end();

    return 0;
}
