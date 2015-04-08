#include "strategy.h"
#include "stdlib.h"
#include <stdbool.h>

static int choose_best_dir(grid g, int i);
static double choose_worst_tile(grid g, int i);
static dir ExpectedMax(strategy s,grid g);


void free_memless_strat (strategy strat)
{
  free (strat);
}

/**
*
* \brief turn a int between 0 and 4 into a direction
* \param int i the int to turn
*
**/
static dir int_to_dir(int i){
	if (i==0)
		return UP;
	if (i==1)
		return RIGHT;
	if (i==2)
		return DOWN;
	else{
		return LEFT;
	}
}

/**
 *
 * \brief returns grid's value if i == 0 or if there's game over.
 *  Else, this function returns the grid's value after the best mouvment.
 * \param grid g the grid
 * \param int i the direction
 *
 **/
static int choose_best_dir(grid g, int i){
  if(game_over(g))// si on a un game over, alors la valeur de la grille est de 0
		return 0;
  if (i==0)//sinon de celle du score
		return grid_score(g);
	grid g2 = new_grid();
	int vMax=0;
	for(int a = 0;a<4;a++){ // 4 représente ici le nombre de directions
		dir d = int_to_dir(a);
		if (!(can_move(g,d)))
			continue;
		copy_grid(g,g2);
		do_move(g2,d);
		int vInter = choose_worst_tile(g,i);
		if(vInter>vMax)
			vMax=vInter;

	}
	delete_grid(g2);
	return vMax;
}


/**
 *
 * \brief this function returns the medium grid's value obtained by placing 2 or 4 in a free case
 * \param grid g, the grid
 * \param int i, the direction
 *
 **/
static double choose_worst_tile(grid g, int i){
	if (game_over(g))
		return 0;
	int n = 0;
	int m = 0;
	for (int x =0 ; x<GRID_SIDE;x++){
		for (int y = 0; y<GRID_SIDE;y++){
			if(get_tile(g,x,y)==0){
				set_tile(g,x,y,1);
				m+=choose_best_dir(g,i-1);
				set_tile(g,x,y,2);
				m+=choose_best_dir(g,i-1);
				set_tile(g,x,y,0);
				n+=2;
			}
		}
	}
	if(n==0)
	  return choose_best_dir(g,i-1);
	return m/n;
}


/**
 *
 * \brief give out the direction choose by expectedMax
 * \param strategy s, structure strategy
 * \param grid g, the grid
 *
 */
static dir ExpectedMax(strategy s,grid g){
	double vMax=0;
	dir d;
	grid g2 = new_grid();
	for (int i = 0 ; i<4;i++){
		dir d2 = int_to_dir(i);
		if(!(can_move(g,d2)))
			continue;
		copy_grid(g,g2);
		do_move(g2,d2);
		double vInter = choose_worst_tile(g2,3);
		if(vInter>=vMax){
			vMax = vInter;
			d=d2;
		}


	}
	delete_grid(g2);
	return d;
}

/**
*
* \brief construct a nex structure strategy
*
**/
strategy expectedMaxConstruct(){
  strategy s=malloc(sizeof(struct strategy_s));
  s->play_move=ExpectedMax;
  s->name="algo expectedMax groupe H";
  s->mem=NULL;
  s->free_strategy=free_memless_strat;
  return s;
}
strategy firstStratConstruct(){
  strategy s=malloc(sizeof(struct strategy_s));
  s->play_move=FirstStrat;
  s->name="algo du coin groupe H";
  s->mem=NULL;
  s->free_strategy=free_memless_strat;
  return s;
}

/**
*
* \brief choose the first direction possible in this order: LEFT, DOWN, UP, RIGHT
* \param strategy s, a structure strategy
* \param grid g, the grid
*
**/
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


strategy (*listFunctionsStrat[])()={firstStratConstruct,expectedMaxConstruct,NULL};
char* listNamesStrat[]={"firstStrat","expectedMax",NULL};
