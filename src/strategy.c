#include "strategy.h"
#include "stdlib.h"
#include <stdbool.h>

void free_memless_strat (strategy strat)
{
  free (strat);
}
dir static int_to_dir(int i){
	if (i==0)
		return UP;
	if (i==1)
		return RIGHT;
	if (i==2)
		return DOWN;
	if (i==3)
		return LEFT;
}
int choose_best_dir(grid g, int i){
	if(game_over(g))
		return 0;
	if (i==0)
		return grid_score(g);
	grid g2 = new_grid();
	int vMax=0;
	for(int a = 0;a<4;a++){
		dir d = int_to_dir(a);
		if (!(can_move(g,d)))
			continue;
		copy_grid(g,g2);
		do_move(g2,d);
		int vInter = choose_worst_tile(g,i);
		if(vInter<vMax)
			vMax=vInter;

	}
	delete_grid(g2);
	return vMax;
}
double choose_worst_tile(grid g, int i){
	if (game_over(g))
		return 0;
	int n = 0;
	int m = 0 ;
	for (int x =0 ; i<GRID_SIDE;i++){
		for (int y = 0; i<GRID_SIDE;i++){
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
	return m/n;
}
dir ExpectedMax(grid g, int i){
	double vMax=0;
	dir d;
	grid g2 = new_grid();
	for (int i = 0 ; i<4,i++){
		dir d2 = int_to_dir(i);
		if(!(can_move(g,d2)))
			continue;
		copy_grid(g,g2);
		do_move(g2,d2);
		double vInter = Choose_worst_tile(g2,3);
		if(vInter>vMax){
			vMax = vInter;
			d=d2;
		}

	}
	delete_grid(g2);
	return d;
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
