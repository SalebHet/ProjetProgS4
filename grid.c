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
