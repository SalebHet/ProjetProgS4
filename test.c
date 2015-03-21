#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    printf("test initialisation:\n");
    test_init();
    printf("test de set_tile en 3, 2, avec la valeur affichée 2:\n");
    test_set_tile();
    printf("test de add_tile:\n");
    test_add();
    printf("test de can_move\n");
    test_can_move();
    printf("test de game_over");
    test_over();
    printf("test de play\n");
    test_play();
    printf("test de do_move");
    test_do_play();
    printf("test de copy\n");
    test_copy();
}

void test_init(){
    grid g = new grig;
    for (int x = 0; x<GRID_SIDE; x++){
        for (int y = 0; y<GRID_SIDE; y++){
            if (get_tile(g, x, y)!=0){
               printf("bug: initialisation, la grille n'est pas à 0\n");
               delete_grid(g);
               return;
            }
        }
    }
    delete_grid(g);
    print("succes\n");
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
                    printf("bug: add_tile, mauvaise valeur\n");
                    delete_grid(g);
                    return;
                }
            }
        }
    }
    if (nb_tile > 1){
        printf("bug: add_tile, trop de tuiles générées\n");
        delete_grid(g);
        return;
    }
    if (nb_tile == 0){
        printf("bug: add_tile, aucune tuile définie\n");
        delete_grid(g);
        return;
    }
    printf("succes add_tile\n");
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
        printf("bug: game over\n");
        delete_grid(g);
        return;
    }
    printf("succes game over\n");
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
        printf("bug can_move\n");
        delete_grid(g);
        return;
        }
    printf("succes can_move\n");
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

void test_set_tile(){
    grid g = new grid;
    set_tile(g, 3, 2, 1);
    afficher(g);
    delete_grid(g);
}

void test_copy(){
    grid g, d = new grid;
    set_tile(g, 0, 0, 1);
    afficher(g);
    copy_grid(g, d);
    afficher(d);

}

void test_score(){
    grid g = new grid;
    set_tile(g, 0, 0, 1);
    set_tile(g, 0, 1, 1);
    afficher(g)
    fusion(g, LEFT);
    grid_score(g);
}

