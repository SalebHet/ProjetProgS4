#include "strategy.h"
#include "stdlib.h"
#include <stdbool.h>
#include <math.h>
#include <assert.h>
static int choose_best_dir(grid g, int i,int score);
static double choose_worst_tile(grid g, int i, int score);
static dir ExpectedMax(strategy s,grid g);
static int max_j (grid g);
static int max_i (grid g);
static int max_on_side(grid g);

# define CONST_SIDE 25

void free_memless_strat (strategy strat)
{
  free (strat);
}
static int homogeneous_tile(grid g,int i,int j){
  int diff=0;
  if(i!=0 && get_tile(g,i-1,j)!=0)
    diff+=abs(get_tile(g,i,j)-get_tile(g,i-1,j));
  if(j!=0 && get_tile(g,i,j-1)!=0)
    diff+=abs(get_tile(g,i,j)-get_tile(g,i,j-1));
  return diff;
}
#if 1
static int value_grid(grid g,int score){
	if (game_over(g))
		return 0;
	int score_move = grid_score(g)-score;
	int void_tile = 0;
	int homo = 0;
	for(int i = 0 ; i<GRID_SIDE ; i++){
		for (int j = 0 ; j<GRID_SIDE ; j++){
			if (get_tile(g,i,j)==0)
				void_tile++;
				homo += homogeneous_tile(g,i,j);
		}
	}

	return log(score_move)*5 + void_tile*10 +500*(10000-homo) + max_on_side(g);
}
#endif
#if 0
static int value_grid(grid g, int rjesz){
  if(game_over(g))
    return 0;
  int grille_pleines=1;
  int diff_tuiles=0;
  int nb_diff_tuile=0;
  for(int i=0;i<GRID_SIDE;i++){
    if(get_tile(g,i,0)!=0)
      grille_pleines++;
  }
  for(int i=1;i<GRID_SIDE;i++){
    if(get_tile(g,0,i)!=0)
      grille_pleines++;
  }
  for(int i=1;i<GRID_SIDE;i++){
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
  }
  float moy_diff_tuiles=(nb_diff_tuile!=0)?1+diff_tuiles/nb_diff_tuile:1;
  return log(grid_score(g))/log(2)+1.5f/moy_diff_tuiles;
}
#endif


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
static int choose_best_dir(grid g, int i, int score){
  if(game_over(g))// si on a un game over, alors la valeur de la grille est de 0
		return 0;
  if (i==0)//sinon de celle du score
		return value_grid(g,score);
	grid g2 = new_grid();
	int vMax=0;
	for(int a = 0;a<4;a++){ // 4 représente ici le nombre de directions
		dir d = int_to_dir(a);
		if (!(can_move(g,d)))
			continue;
		copy_grid(g,g2);
		score = grid_score(g);
		do_move(g2,d);
		int vInter = choose_worst_tile(g,i,score);
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
static double choose_worst_tile(grid g, int i,int score){
	if (game_over(g))
		return 0;
	int n = 0;
	int m = 0;
	for (int x =0 ; x<GRID_SIDE;x++){
		for (int y = 0; y<GRID_SIDE;y++){
			if(get_tile(g,x,y)==0){
				set_tile(g,x,y,1);
				score = grid_score(g);
				m+=choose_best_dir(g,i-1,score);
				set_tile(g,x,y,2);
				score = grid_score(g);
				m+=choose_best_dir(g,i-1,score);
				set_tile(g,x,y,0);
				score = grid_score(g);
				n+=2;
			}
		}
	}
	if(n==0)
	  return choose_best_dir(g,i-1,score);
	return m/n;
}


/**
 *
 * \brief give out the direction choose by expectedMax
 * \param strategy s, structure strategy
 * \param grid g, the grid
 *
 */
static dir hybridAlgo(strategy s,grid g){
  if(*(int*)s->mem==0 && (grid_score(g)<500 ||
  (get_tile(g,0,GRID_SIDE-1) < get_tile(g,0,GRID_SIDE-2) || get_tile(g,0,GRID_SIDE-1)<get_tile(g,1,GRID_SIDE-1))))
    return FirstStrat(s,g);
  int cases_vides=0;
  for(int i=0;i<GRID_SIDE;i++)
    for(int j=0;j<GRID_SIDE;j++)
      if(get_tile(g,i,j)==0)
	cases_vides++;
  if(cases_vides==0)
    *(int*)s->mem=5;
  else if(cases_vides<6)
    *(int*)s->mem=4;
  else
    *(int*)s->mem=3;
  return ExpectedMax(s,g);
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
		int score = grid_score(g);
		do_move(g2,d2);
		double vInter = choose_worst_tile(g2,*(int*)s->mem,score);
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
  s->mem=malloc(sizeof(int));
  *(int*)(s->mem)=3;
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
strategy hybridAlgoConstruct(){
  strategy s=expectedMaxConstruct();
  *(int*)s->mem=0;
  s->play_move=hybridAlgo;
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

static int max_i (grid g){
    int max_i = 0;
    int max = 0;
    for (int i = 0; i < GRID_SIDE-1; i++){
        for (int j = 0; j < GRID_SIDE-1 ; j++){
            if (get_tile(g, i, j) > max){
                max = get_tile(g, i, j);
                max_i = i;
            }
        }
    }
    return max_i;
}

static int max_j (grid g){
    int max_j = 0;
    int max = 0;
    for (int i = 0; i < GRID_SIDE-1; i++){
        for (int j = 0; j < GRID_SIDE-1; j++){
            if (get_tile(g,i,j)> max){
                max = get_tile(g, i, j);
                max_j = j;
            }
        }
    }
    return max_j;
}

static int max_on_side (grid g){
    int maxI = max_i(g);
    int maxJ = max_j(g);
    int point = 0;
    if (maxI == 0 || maxI == GRID_SIDE-1)
        point += CONST_SIDE;
    if (maxJ == 0 || maxJ == GRID_SIDE-1)
        point +=CONST_SIDE;
    return point;
}

strategy (*listFunctionsStrat[])()={firstStratConstruct,expectedMaxConstruct,hybridAlgoConstruct,NULL};
char* listNamesStrat[]={"firstStrat","expectedMax","algo hybride",NULL};
