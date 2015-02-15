#include "grid.h"
#include <time.h>
#include <stdlib.h>

struct grid_s{
    tile g [GRID_SIDE][GRIDE_SIDE];
    unsigned long int score;
    };

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

grid new_grid(){
    grid gr = malloc(sizeof(struct grid_s));
    gr->score=0;
    for(int i=0;i<GRID_SIDE,i++){
            for(int j=0;j<GRID_SIDE;j++){
                gr->g[i][j]=0;
            }
        }
    return gr;
    }

void delete_grid(grid g){
    free(g);
    }

void copy_grid (grid src, grid dst){
    dst->score=src->score;
    for(int i=0;i<GRID_SIDE,i++){
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
    while (g[x][y]!=0){
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
    do_move (grid gr, dir d);
    add_tile(g);
}
