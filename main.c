#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    grid g = new_grid();
    set_tile(g,1,2,2);
    set_tile(g,2,2,2);
    if(get_tile(g,1,2)!=2)
        printf("Mauvais retour de valeur");
    afficher(g);
    do_move(g,LEFT);
    afficher(g);
    delete_grid(g);
    return EXIT_SUCCESS;
}
