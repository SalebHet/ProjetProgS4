#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    if(test_init())
        printf ("Success Initialisation");
    printf("Initialisation KO");
}

bool test_init(){
    grid g = new grig;
    for (int x = 0; x<GRID_SIDE; x++){
        for (int y = 0; y<GRID_SIDE; y++){
            if (get_tile(g, x, y)!=0)
                return false
        }
    }
    delete_grid(g);
    return true;
}

void test_score(){

}
