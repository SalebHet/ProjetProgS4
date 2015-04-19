#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "keyboard.h"
#include "grid.h"
/**
* \brief return the direction given by the user
**/
dir getDir() {
    srand(time(NULL));
    while (true) {
        int c = getch();
        if (c != ERR) {
            switch (c) {
            case KEY_UP:
                return UP;
            case KEY_LEFT:
                return LEFT;
            case KEY_DOWN:
                return DOWN;
            case KEY_RIGHT:
                return RIGHT;
            }
        }
    }
}
