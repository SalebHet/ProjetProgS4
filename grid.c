#include "grid.h"
#include <time.h>
#include <stdlib.h>

struct grid_s{
  tile g [GRID_SIDE][GRID_SIDE]; // On créer un tableau statique de tile nous servant à stoquer l'ensemble des tiles de notre grille.
  unsigned long int score; //Variable permettant de stocker le score
};

static int rand_a_b(int a, int b){ // fonction permettant de retourner un entier dans l'intervalle [a;b[
  return rand()%(b-a) +a;
}

grid new_grid(){ // Fonction permettant l'instantiation d'une nouvelle grille
    srand(time(NULL)); // Initialisation de TIME pour le random
  grid gr = malloc(sizeof(struct grid_s)); //Allocation mémoire pour la nouvelle instance de grille
  gr->score=0; //Initialisation du score à 0
  for(int i=0;i<GRID_SIDE;i++){
    for(int j=0;j<GRID_SIDE;j++){ //Initialisation de l'ensemble des tuiles à 0
      gr->g[i][j]=0;
    }
  }
  return gr;
}
bool not_over(int i,dir d)
{
  if(d==1)
    return i<GRID_SIDE;
  else
    return i>=0;
}

bool can_move (grid g, dir d)
{
  int d2,i,j,dep;
  int *inc1,*inc2;

  switch(d){
  case UP:
  case LEFT:
    d2=1;
    dep=0;
    break;

  case DOWN:
  case RIGHT:
    d2=-1;
    dep=GRID_SIDE-1;
    break;
  }

  switch(d){
  case UP:
  case DOWN:
    inc1=&i;
    inc2=&j;
    break;

  case LEFT:
  case RIGHT:
    inc1=&j;
    inc2=&i;
    break;
  }
  unsigned long int tmp;
  bool void_tile;
  for((*inc1)=dep;not_over(*inc1,d2);(*inc1)+=d2){
    for((*inc2)=dep,tmp=g->g[i][j],void_tile=(tmp==0),(*inc2)++;not_over(*inc2,d2);(*inc2)+=d){
      if(g->g[i][j]==0)
	void_tile=true;
      else{
	if(tmp==g->g[i][j] || void_tile )
	  return true;
	tmp=g->g[i][j];
      }
    }
  }

  return false;
      

#if 0
  unsigned int tmp;
  bool void_tile;

  switch(d)
    {
    case UP:
      for(int i=0;i<GRID_SIDE;i++)
	{
	  tmp=g->g[i][0];
	  void_tile=tmp==0;
	  for(int j=1;j<GRID_SIDE;j++)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] || void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;

    case DOWN:
      for(int i=0;i<GRID_SIDE;i++)
	{
	  tmp=g->g[i][GRID_SIDE-1];
	  void_tile=tmp==0;
	  for(int j=GRID_SIDE-2;j>=0;j--)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] ||  void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;

    case LEFT:
      for(int j=0;j<GRID_SIDE;j++)
	{
	  tmp=g->g[0][j];
	  void_tile=tmp==0;
	  for(int i=1;i<GRID_SIDE;i++)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] || void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;

    case RIGHT:
      for(int j=0;j<GRID_SIDE;j++)
	{
	  tmp=g->g[GRID_SIDE-1][j];
	  void_tile=tmp==0;
	  for(int i=GRID_SIDE-2;i>=0;i--)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] || void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;
    }
  return false;
#endif
}
void delete_grid(grid g){
  free(g);
}

void copy_grid (grid src, grid dst){
  dst->score=src->score;
  for(int i=0;i<GRID_SIDE;i++){
    for(int j=0;j<GRID_SIDE;j++){
      dst->g[i][j]=src->g[i][j];
    }
  }
}

tile get_tile (grid gr, int x, int y){
  return gr->g[x][y];
}

void set_tile (grid gr, int x, int y, tile t){
  gr->g[x][y]=t;
}

unsigned long int grid_score (grid g){
  return g->score;
}

bool game_over (grid g){
  return !(can_move(g, UP) || can_move(g, DOWN) || can_move(g, LEFT) || can_move(g, RIGHT));
}

void add_tile(grid g){
  int x = rand_a_b(0, 4);
  int y = rand_a_b(0, 4);
  int alea = rand_a_b(0, 9);
  int bouh = 0;
  while (g->g[x][y]!=0){
    x = rand_a_b(0, 4);
    y = rand_a_b(0, 4);
  }
  if (alea == 0){
    bouh = 2;
  }
  else{
    bouh = 1;
  }
  set_tile(g, x, y, bouh);
}

void play(grid gr,dir d){
  do_move (gr, d);
  add_tile(gr);
}

static void decalage(grid g,dir d){
  int x_libre,y_libre;
  switch(d){

  case RIGHT:
    x_libre=GRID_SIDE-1;
    for(int j=0;j<GRID_SIDE;j++){
      x_libre=GRID_SIDE-1;
      for(int i=GRID_SIDE-1;i>=0;i--){
	if(g->g[i][j]!=0){
	  g->g[x_libre][j]=g->g[i][j];
	  x_libre--;
	}
      }
      for(;x_libre>=0;x_libre--){
	g->g[x_libre][j]=0;

      }
    }

    break;


  case LEFT:
    x_libre=0;
    for(int j=0;j<GRID_SIDE;j++){
      x_libre=0;
      for(int i=0;i<GRID_SIDE;i++){
	if(g->g[i][j]!=0){
	  g->g[x_libre][j]=g->g[i][j];
	  x_libre++;
	}

      }
      for(;x_libre<GRID_SIDE;x_libre++){
	g->g[x_libre][j]=0;
      }
    }
    break;

  case UP:
    y_libre=0;
    for(int i=0;i<GRID_SIDE;i++){
      y_libre=0;
      for(int j=0;j<GRID_SIDE;j++){
	if(g->g[i][j]!=0){
	  g->g[i][y_libre]=g->g[i][j];
	  y_libre++;
	}
      }
      for(;y_libre<GRID_SIDE;y_libre++){
	g->g[i][y_libre]=0;
      }
    }
    break;

  case DOWN:
    y_libre=GRID_SIDE-1;
    for(int i=0;i<GRID_SIDE;i++){
      y_libre=GRID_SIDE-1;
      for(int j=GRID_SIDE-1;j>=0;j--){
	if(g->g[i][j]!=0){
	  g->g[i][y_libre]=g->g[i][j];
	  y_libre--;
	}

      }
      for(;y_libre>-1;y_libre--){
        g->g[i][y_libre]=0;
      }
    }
    break;
  }
}
void static fusion (grid g, dir d){
  switch(d){
  case LEFT:
    for (int y = 0; y<=GRID_SIDE-1; y++){
      for (int x = 0; x<GRID_SIDE-1; x++){
	if (g->g[x][y]!=0 && g->g[x][y] == g->g[x+1][y]){
	  g->g[x][y] += 1;
	  g->g[x+1][y] = 0;
	  x++;
	}
      }
    }
    break;
  case RIGHT:
    for (int y = 0; y<=GRID_SIDE-1; y++){
      for (int x = GRID_SIDE-1; x >= 0; x--){
	if (g->g[x][y]!=0 && g->g[x][y]==g->g[x-1][y]){
	  g-> g[x][y]+=1;
	  g-> g[x-1][y] = 0;
	  x--;
	}
      }
    }
    break;
  case UP:
    for (int x = 0; x<=GRID_SIDE-1; x++){
      for (int y = 0; y<GRID_SIDE-1; y++){
	if (g->g[x][y]!=0 && g->g[x][y]==g->g[x][y+1]){
	  g-> g[x][y]+= 1;
	  g-> g[x][y+1] = 0;
	  y++;
	}
      }
    }
    break;
  case DOWN:
    for (int x = 0; x<=GRID_SIDE-1; x++){
      for (int y = GRID_SIDE-2; y>=0; y--){
	if (g->g[x][y]!=0 && g->g[x][y]==g->g[x][y+1]){
	  g-> g[x][y]+=1;
	  g-> g[x][y+1] = 0;
	  y--;
	}
      }
    }
    break;
  }
}

void do_move(grid g,dir d){
  decalage(g,d);
  fusion(g,d);
  decalage(g,d);
}




