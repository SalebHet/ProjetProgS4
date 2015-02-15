#include "afficher.h"
#include "grid.h"
#include <stdio.h>"
#include <stdlib.h>


void main(){
    grid g = new_grid();
    set_taile(g,1,2,2);
    set_taile(g,2,2,3);
    if(get_taile(1,2)!=2)
        printf("Mauvais retour de valeur");
    afficher(g);
    delete_grid(g);
}
