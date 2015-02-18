#include "grid.h"
#include <time.h>
#include <stdlib.h>

struct grid_s{
    tile g [GRID_SIDE][GRID_SIDE];
    unsigned long int score;
};

static int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

grid new_grid(){
    grid gr = malloc(sizeof(struct grid_s));
    gr->score=0;
    for(int i=0;i<GRID_SIDE;i++){
            for(int j=0;j<GRID_SIDE;j++){
                gr->g[i][j]=0;
            }
        }
    return gr;
    }


bool can_move (grid g, dir d)
{
  unsigned int tmp;
  bool void_tile;
  switch(d)
  {
  case UP:
    for(int i=0;i<GRID_SIDE;i++)
    {
      tmp=g->g[i][0];
      void_tile=false;
      for(int j=1;j<GRID_SIDE;j++)
      {
	if(g->g[i][j]==0)
	  void_tile=true;
	if(tmp==g->g[i][j] || (g->g[i][j]!=0 && void_tile) )
	  return true;
      }
    }
    return false;
    break;

  case DOWN:
    for(int i=0;i<GRID_SIDE;i++)
    {
      tmp=g->g[i][0];
      void_tile=false;
      for(int j=GRID_SIDE-2;j>=0;j--)
      {
	if(g->g[i][j]==0)
	  void_tile=true;
	if(tmp==g->g[i][j] || (g->g[i][j]!=0 && void_tile) )
	  return true;
      }
    }
    return false;
    break;

  case LEFT:
    for(int j=0;j<GRID_SIDE;j++)
    {
      tmp=g->g[0][j];
      void_tile=false;
      for(int i=1;i<GRID_SIDE;i++)
      {
	if(g->g[i][j]==0)
	  void_tile=true;
	if(tmp==g->g[i][j] || (g->g[i][j]!=0 && void_tile) )
	  return true;
      }
    }
    return false;
    break;

  case RIGHT:
    for(int j=0;j<GRID_SIDE;j++)
    {
      tmp=g->g[0][j];
      void_tile=false;
      for(int i=GRID_SIDE-2;i>=0;i--)
      {
	if(g->g[i][j]==0)
	  void_tile=true;
	if(tmp==g->g[i][j] || (g->g[i][j]!=0 && void_tile) )
	  return true;
      }
    }
    return false;
    break;
  }
  return false;
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
#if 0
bool can_move (grid g, dir d)
{
  unsigned int tmp;//contient la valeur de la case précédente
  boolean void_tile;//vaut vrai si il existe une case précédente qui est vide
  switch(d)
  {
  case DOWN:
    for(int i=0;i<GRID_SIDE;i++)
    {
      tmp=g->g[i][0];//on initialise à la valeur de la première case
      void_tile=false;//et on a pas encore eu de cases vides
      for(int j=1;j<GRID_SIDE;j++)
      {
	if(g->g[i][j]==0)//si la case est vide
	  void_tile=true;//alors on marque que on a rencontré une case vide
	if(tmp==g->g[i][j] || (g[i][j]!=0 && void_tile) )//si la case actuelle est la meme que la précedente alors on pourra les fusionner
	                                                 //et si la case est non vide et qu'on a rencontré une case vide alors on pourra
                                                         //décaller
	  return true;//donc on renvoi vrai
      }
    }
    return false;//si on a jamais renvoyé vrais alors on ne peut rien faire
    break;

  case UP:
    for(int i=0;i<GRID_SIDE;i++)
    {
      tmp=g->g[i][0];
      void_tile=false;
      for(int j=GRID_SIDE-2;j>=0;j--)
      {
	if(g->g[i][j]==0)
	  void_tile=true;
	if(tmp==g->g[i][j] || (g[i][j]!=0 && void_tile) )
	  return true;
      }
    }
    return false;
    break;

  case LEFT:
    for(int j=0;i<GRID_SIDE;j++)
    {
      tmp=g->g[i][0];
      void_tile=false;
      for(int i=1;i<GRID_SIDE;i++)
      {
	if(g->g[i][j]==0)
	  void_tile=true;
	if(tmp==g->g[i][j] || (g[i][j]!=0 && void_tile) )
	  return true;
      }
    }
    return false;
    break;

  case RIGHT:
    for(int j=0;i<GRID_SIDE;j++)
    {
      tmp=g->g[i][0];
      void_tile=false;
      for(int i=GRID_SIDE-2;i>=0;i--)
      {
	if(g->g[i][j]==0)
	  void_tile=true;
	if(tmp==g->g[i][j] || (g[i][j]!=0 && void_tile) )
	  return true;
      }
    }
    return false;
    break;
  }
}
#endif
static void decalage(grid g,dir d){
  int x_libre,y_libre;
    switch(d){

    case DOWN:
      x_libre=GRID_SIDE-1;
      for(int j=0;j<GRID_SIDE;j++){
	x_libre=GRID_SIDE-1;
	for(int i=GRID_SIDE-1;i>=0;i--){
	  if(g->g[i][j]!=0){
	    g->g[x_libre][j]=g->g[i][j];
	    g->g[i][j]=0;
	    x_libre--;
	  }
	}
      }
      break;


    case UP:
      x_libre=0;
      for(int j=0;j<GRID_SIDE;j++){
	x_libre=0;
	for(int i=0;i<GRID_SIDE;i++){
	  if(g->g[i][j]!=0){
	    g->g[x_libre][j]=g->g[i][j];
	    g->g[i][j]=0;
	    x_libre++;
	  }
	}
      }
      break;

    case LEFT:
      y_libre=0;
      for(int i=0;i<GRID_SIDE;i++){
	y_libre=0;
	for(int j=0;j<GRID_SIDE;j++){
	  if(g->g[i][j]!=0){
	    g->g[i][y_libre]=g->g[i][j];
	    g->g[i][j]=0;
	    y_libre++;
	  }
	}
      }
      break;

    case RIGHT:
      y_libre=GRID_SIDE-1;
      for(int i=0;i<GRID_SIDE;i++){
	y_libre=GRID_SIDE-1;
	for(int j=GRID_SIDE;j>=0;j--){
	  if(g->g[i][j]!=0){
	    g->g[i][y_libre]=g->g[i][j];
	    g->g[i][j]=0;
	    y_libre--;
	  }
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
                if (g->g[x][y] == g->g[x+1][y]){
                    g->g[x][y] += 1;
                    g->g[x+1][y] = 0;
                }
            }
        }
    case RIGHT:
      for (int y = 0; y<=GRID_SIDE-1; y++){
	for (int x = GRID_SIDE-1; x > 0; x--){
                if (g->g[x][y]==g->g[x-1][y]){
                    g-> g[x][y]+=1;
                    g-> g[x-1][y] = 0;
                }
            }
        }

    case UP:
      for (int x = 0; x<GRID_SIDE-1; x++){
	for (int y = 0; y<GRID_SIDE-1; y++){
                if (g->g[x][y]==g->g[x][y+1]){
                    g-> g[x][y]+= 1;
                    g-> g[x][y+1] = 0;
                }
            }
        }
    case DOWN:
      for (int x = 0; x<GRID_SIDE-1; x++){
	for (int y = GRID_SIDE-1; y>0; y--){
                if (g->g[x][y]==g->g[x][y+1]){
                    g-> g[x][y]+=1;
                    g-> g[x][y+1] = 0;
                }
            }
        }
    }
}

void do_move(grid g,dir d){
    decalage(g,d);
    if(0)
      fusion(g,d);
    //decalage(g,d);
}




