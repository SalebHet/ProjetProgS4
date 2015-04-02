#include "strategy.h"
#include "stdlib.h"
#include <stdbool.h>

void free_memless_strat (strategy strat)
{
  free (strat);
}


void FirstStrat(grid g){
    dir dir;
    while (!(game_over(g)){
        if (can_move(g, LEFT))
            dir = LEFT
        else{
            if (can_move(g, DOWN))
                dir = DOWN;
            else {
                if (can_move(g, RIGHT))
                    dir = RIGHT;
                dir = UP;
            }
        }
        do_move(g, dir);
    }
}
