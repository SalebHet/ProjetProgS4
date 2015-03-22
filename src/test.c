#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void test_init();
static void test_set_tile();
static void test_add();
static void test_can_move();
static void test_over();
static void test_play();
static void test_do_move();
static void test_copy();

int main() {
    printf("test initialisation:\n");
    test_init();
    printf("test de set_tile\n");
    test_set_tile();
    printf("test de add_tile:\n");
    test_add();
    printf("test de can_move\n");
    test_can_move();
    printf("test de game_over\n");
    test_over();
    printf("test de play\n");
    test_play();
    printf("test de do_move\n");
    test_do_move();
    printf("test de copy\n");
    test_copy();
}

void test_init() {
    grid g = new_grid();
    for (int x = 0; x < GRID_SIDE; x++) {
        for (int y = 0; y < GRID_SIDE; y++) {
            if (get_tile(g, x, y) != 0) {
                printf("bug : initialisation, la grille n'est pas à 0\n");
                delete_grid(g);
                return;
            }
        }
    }
    delete_grid(g);
    printf("succes : initialisation\n");
}

void test_add() {
    grid g = new_grid();
    int nb_tile = 0;
    add_tile(g);
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            if (get_tile(g, i, j) != 0) {
                if (get_tile(g, i, j) == 1 || get_tile(g, i, j) == 2)
                    nb_tile += 1;
                else {
                    printf("bug: add_tile, mauvaise valeur\n");
                    delete_grid(g);
                    return;
                }
            }
        }
    }
    if (nb_tile > 1) {
        printf("bug : add_tile, trop de tuiles générées\n");
        delete_grid(g);
        return;
    }
    if (nb_tile == 0) {
        printf("bug : add_tile, aucune tuile définie\n");
        delete_grid(g);
        return;
    }
    printf("succes : add_tile\n");
    delete_grid(g);
}

void test_over() {
    grid g = new_grid();
    int val_tile = 1;
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            set_tile(g, i, j, val_tile);
            val_tile++;
        }
    }
    if (!game_over(g)) {
        printf("bug : game over\n");
        delete_grid(g);
        return;
    }
    printf("succes :  game over\n");
    delete_grid(g);
}

void test_can_move() {
    grid g1 = new_grid();
    for (int y = 0; y < GRID_SIDE; y++) {
        set_tile(g1, 0, y, y);
    }
    if ((!can_move(g1, UP)) || can_move(g1, DOWN)) {
        printf("bug : can_move\n");
        delete_grid(g1);
        return;
    }
    delete_grid(g1);
    grid g2 = new_grid();
    for (int x = 0; x < GRID_SIDE; x++) {
        set_tile(g2, x, 0, x + 1);
    }
    if (can_move(g2, LEFT) || can_move(g2, RIGHT)) {
        printf("bug : can_move\n");
        delete_grid(g2);
        return;
    }
    printf("succes : can_move\n");
    delete_grid(g2);
}

void test_do_move() {
    grid g = new_grid();
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            set_tile(g, i, j, 1);
        }
    }
    do_move(g, DOWN);
    do_move(g, RIGHT);
    do_move(g, UP);
    do_move(g, LEFT);
    for (int x = 0; x < GRID_SIDE; x++) {
        for (int y = 0; y < GRID_SIDE; y++) {
            if (x != 0 && y != 0 && get_tile(g, x, y)) {
                printf("bug : do_move, tuiles non fusionnees\n");
                delete_grid(g);
                return;
            }
        }
    }
    if (get_tile(g, 0, 0) == 5)
        printf("succes : do_move\n");
    else
        printf("bug : do_move\n");
    delete_grid(g);
}

void test_play() {
    grid g = new_grid();
    set_tile(g, 1, 2, 1);
    set_tile(g, 0, 2, 1);
    play(g, LEFT);
    int compteur = 0;
    for (int x = 0; x < GRID_SIDE; x++) {
        for (int y = 0; y < GRID_SIDE; y++) {
            if (get_tile(g, x, y)) {
                compteur++;
            }
        }
    }
    if (compteur < 2)
        printf("bug : play, tuiles manquantes\n");
    else if (compteur > 2)
        printf("bug : play, trop de tuiles generees\n");
    else
        printf("succes : play\n");
    delete_grid(g);
}

void test_set_tile() {
    grid g = new_grid();
    set_tile(g, 3, 2, 1);
    for (int x = 0; x < GRID_SIDE; x++) {
        for (int y = 0; y < GRID_SIDE; y++) {
            if (x != 3 && y != 2 && get_tile(g, x, y) != 0) {
                printf("bug : set_tile, mauvaise tuile modifiee\n");
                delete_grid(g);
                return;
            }
        }
    }
    printf("succes : set_tile\n");
    delete_grid(g);
}

void test_copy() {
    grid g = new_grid();
    grid c = new_grid();
    set_tile(g, 0, 0, 1);
    copy_grid(g, c);
    for (int x = 0; x < GRID_SIDE; x++) {
        for (int y = 0; y < GRID_SIDE; y++) {
            if (get_tile(g, x, y) != get_tile(c, x, y)) {
                printf("bug : copy_grid, erreur lors de la copie");
                delete_grid(g);
                delete_grid(c);
            }
        }
    }
    printf("succes : copy_grid\n");
    delete_grid(g);
    delete_grid(c);
}

void test_score() {
    grid g = new_grid();
    set_tile(g, 0, 0, 1);
    set_tile(g, 0, 1, 1);
    afficher(g);
    do_move(g, LEFT);
    if (grid_score(g) == 4)
        printf("succes : grid_score");
    else
        printf("bug : grid_score");
    delete_grid(g);
}
