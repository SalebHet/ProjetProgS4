#include "strategy.h"
#include "stdlib.h"
#include <stdbool.h>

void free_memless_strat (strategy strat)
{
  free (strat);
}


dir FirstStrat(grid g){
	if(can_move(g,LEFT))
		return LEFT;
	if (can_move(g,DOWN))
		return DOWN;
	if (can_move(g,UP))
		return UP;
	else{
		return RIGHT;
	}
}
