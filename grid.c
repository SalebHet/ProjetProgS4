#include "grid.h"

struct grid_s{
    tile g [GRID_SIDE][GRIDE_SIDE];
    unsigned int score;
    };
grid newGrid(){
    grid gr;
    gr->score=0;
    for(int i=0;i<GRID_SIDE,i++){
            for(int j=0;j<GRID_SIDE;j++){
                gr->g[i][j]=0;
            }
        }
    return gr;
    }


bool can_move (grid g, dir d)
{
  unsigned int tmp;
  boolean void_tile;
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
	if(tmp==g->g[i][j] || (g[i][j]!=0 && void_tile) )
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
