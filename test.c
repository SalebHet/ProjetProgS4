#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    test_init();
    test_add();
    test_can_move();
    test_over();
    test_play();
    test_do_play();
}

void test_init(){
    grid g = new grig;
    for (int x = 0; x<GRID_SIDE; x++){
        for (int y = 0; y<GRID_SIDE; y++){
            if (get_tile(g, x, y)!=0){
               printf("bug: initialisation, la grille n'est pas à 0");
               delete_grid(g);
               return;
            }
        }
    }
    delete_grid(g);
    print("succes");
}

void test_add(){
    grid g = new grid();
    int nb_tile = 0;
    add_tile(g);
    for (int i = 0; i<GRID_SIDE; i++){
        for (int j = 0; j<GRID_SIDE; j++){
            if (get_tile(g, i, j)!=0){
                if (get_tile(g, i, j)==1 || get_tile(g, i, j)== 2)
                    nb_tile+=1;
                else{
                    printf("bug: add_tile, mauvaise valeur");
                    delete_grid(g);
                    return;
                }
            }
        }
    }
    if (nb_tile > 1){
        printf("bug: add_tile, trop de tuiles générées");
        delete_grid(g);
        return;
    }
    if (nb_tile == 0){
        printf("bug: add_tile, aucune tuile définie");
        delete_grid(g);
        return;
    }
    printf("succes add_tile");
    delete_grid(g);
}

void test_over(){
    grid g = new grid;
    int val_a = 1;
    int val_b = 2;
    int val_tmp;
    for (int i = 0; i < GRID_SIDE ; i++){
        for (int j = 0; j < GRID_SIDE ; j++){
            set_tile(g, x, y, val_a);
            val_tmp = val_a;
            val_a = val_b;
            val_b = val_tmp;
        }
    }
    if (!game_over(g)){
        printf("bug: game over");
        delete_grid(g);
        return;
    }
    printf("succes game over");
    delete_grid(g);
}

void test_can_move(){
    grid g_u_d, g_r_l = new grid;
    for (int x = 0; x<GRID_SIDE; x ++){
        set_tile(g_r_l, x, 0, x);
    }
    for (int y = 0; y<GRID_SIDE; y++){
        set_tile(g_u_d, 0, y, y);
    }
    if ((can_move(g_u_d, UP) || can_move(g_u_d, DOWN) ||
         can_move(g_r_l, LEFT) || can_move(g_r_l, RIGHT)){
        printf("bug can_move");
        delete_grid(g);
        return;
        }
    printf("succes can_move");
    delete_grid(g);
}
void test_do_play(){
    grid g_u_d, g_r_l = new grid;
    for (int i = 0; i<GRID_SIDE; i++){
        for (int j = 0; j < GRID_SIDE; j++){
            set_tile(g_u_d, i, j, 1);
            set_tile(g_r_l, i, j, 1);
        }
    }
    afficher(g_u_d);
    afficher(g_r_l);
    do_move(g_u_d, UP);
    afficher(g_u_d);
    do_move(g_u_d, DOWN);
    afficher(g_u_d);
    do_move(g_r_l, RIGHT);
    afficher(g_r_l);
    do_move(g_r_l, LEFT);
    afficher(g_r_l);
    delete_grid(g_u_d);
    delete_grid(g_r_l);
}

void test_play(){
    grid g = new grid;
    add_tile(g);
    add_tile(g);
    afficher(g);
    play(g, UP);
    afficher(g);
    play(g, RIGHT);
    afficher(g);
    play(g, DOWN);
    afficher(g);
    play(g, LEFT);
    afficher(g);
    delete_grid(g);
}
