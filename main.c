#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>

dir getDir(){
  while(true){
  char c = getchar();

    switch(c){
        case 'z':
            return UP;
        case 'q':
            return LEFT;
        case 's':
            return DOWN;
        case 'd':
            return RIGHT;

    }
  }
}
/*
int main(){
    grid g = new_grid();
    set_tile(g,1,2,2);
    set_tile(g,2,2,2);
    for (int j=0;j<GRID_SIDE;j++){
        set_tile(g,0,j,2);
    }
    if(get_tile(g,1,2)!=2)
        printf("Mauvais retour de valeur");
    afficher(g);
    do_move(g,LEFT);
    afficher(g);
    delete_grid(g);
    return EXIT_SUCCESS;
}*/

int main(){
    grid g = new_grid();
    add_tile(g);
    add_tile(g);
    printf("z, q, s ou d et 'entrée' pour faire un mouvement\n");
    while(!game_over(g)){
        afficher(g);
        dir d = getDir();
        if(can_move(g,d)){
	  play(g,d);

	}
	else
	  printf("mouvement impossible\n");
    }
    afficher(g);
    printf("game over \n");
    delete_grid(g);
    return EXIT_SUCCESS;
}
