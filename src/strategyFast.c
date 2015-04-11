
#include "grid.h"
#include "strategy.h"

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

strategy A2_beziau_pathe_nerestan_fast(){
  strategy s=malloc(sizeof(struct strategy_s));
  s->play_move=FirstStrat;
  s->name="algo du coin groupe H";
  s->mem=NULL;
  s->free_strategy=free_memless_strat;
  return s;
}
