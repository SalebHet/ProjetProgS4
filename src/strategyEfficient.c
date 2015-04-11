#include <stdlib.h>
#include <math.h>
#include "strategy.h"
#include "grid.h"

static int valeur_grille(grid g);
static dir int_to_dir(int i);
static int choose_best_dir(grid g, int i);
static double choose_worst_tile(grid g, int i);

static int valeur_grille(grid g){
  if(game_over(g))
    return 0;
  int grille_pleines=1;
  int diff_tuiles=0;
  int nb_diff_tuile=0;
  for(int i=0;i<GRID_SIDE;i++)
    if(get_tile(g,i,0)!=0)
       grille_pleines++;
  for(int i=1;i<GRID_SIDE;i++)
    if(get_tile(g,0,i)!=0)
       grille_pleines++;
  for(int i=1;i<GRID_SIDE;i++)
    for(int j=1;j<GRID_SIDE;j++){
      int a=get_tile(g,i,j);
      int b=get_tile(g,i-1,j);
      if(a!=0){
	grille_pleines++;
	if(b!=0){
	  diff_tuiles+=abs(a-b);
	  nb_diff_tuile++;
	}
	b=get_tile(g,i,j-1);
	if(b!=0){
	  diff_tuiles+=abs(a-b);
	  nb_diff_tuile++;
	}
      } 
    }
  float moy_diff_tuiles=(nb_diff_tuile!=0)?1+diff_tuiles/nb_diff_tuile:1;
  return log(grid_score(g))/log(2)+1.5f/moy_diff_tuiles;
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
		return valeur_grille(g);
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
		double vInter = choose_worst_tile(g2,4);
		if(vInter>=vMax){
			vMax = vInter;
			d=d2;
		}


	}
	delete_grid(g2);
	return d;
}

strategy A2_beziau_pathe_nerestan_efficient(){
  strategy s=malloc(sizeof(struct strategy_s));
  s->play_move=ExpectedMax;
  s->name="algo expectedMax groupe H";
  s->mem=NULL;
  s->free_strategy=free_memless_strat;
  return s;
}
