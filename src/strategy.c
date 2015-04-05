#include "strategy.h"
#include "stdlib.h"
#include <stdbool.h>


void free_memless_strat (strategy strat)
{
  free (strat);
}

strategy firstStratConstruct(){
  strategy s=malloc(sizeof(struct strategy_s));
  s->play_move=FirstStrat;
  s->name="algo du coin groupe H";
  s->mem=NULL;
  s->free_strategy=free_memless_strat;
  return s;
}

dir FirstStrat(strategy s,grid g){
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

strategy (*listFunctionsStrat[])()={firstStratConstruct,NULL};
char* listNamesStrat[]={"firstStrat",NULL};
