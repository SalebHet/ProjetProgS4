#include "afficher.h"
#include "grid.h"
#include "strategy.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

static void test_init();
static void test_set_tile();
static void test_add();
static void test_can_move();
static void test_over();
static void test_play();
static void test_do_move();
static void test_copy();
static void test_strat();
static void test_strat_opti();

int main() {
    srand(time(NULL));
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
    test_strat();
    test_strat_opti();
}

/**
* \brief test if the initialization is correctly done
**/
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

/**
* \brief test the addition of the tiles
**/
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

/**
* \brief test the function "gameover()"
**/
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

/**
* \brief test "can_move()"
**/
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

/**
* \brief test "do_move(grid g, dir d)"
**/
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

/**
* \brief test "play(grid g, dir d)"
**/
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

/**
* \brief test "set_tile(grid g, int x, int y, tile t)"
**/
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

/**
* \brief test the copy of the grid
**/
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

/**
* \brief test "grid_score(grid g)"
**/
void test_score() {
    grid g = new_grid();
    set_tile(g, 0, 0, 1);
    set_tile(g, 0, 1, 1);
    display(g);
    do_move(g, LEFT);
    if (grid_score(g) == 4)
        printf("succes : grid_score");
    else
        printf("bug : grid_score");
    delete_grid(g);
}

/**
* \brief find the grid's maximum
* \param gird g, the grid
**/
static int max_grid(grid g) {
    int m = 0;
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            if (get_tile(g, i, j) > m)
                m = get_tile(g, i, j);
        }
    }
    return (int) pow(2, m);
}

/**
* \brief test a strategy
**/
void test_strat() {
    grid *tabGrid = malloc(sizeof(grid) * 10000);
    strategy strat = listFunctionsStrat[0] ();
    for (int i = 0; i < 10000; i++) {
        tabGrid[i] = new_grid();
        add_tile(tabGrid[i]);
        add_tile(tabGrid[i]);
        while (!game_over(tabGrid[i])) {
            play(tabGrid[i], strat->play_move(NULL, tabGrid[i]));
        }
    }
    int tmax = 0;
    unsigned long int max = 0;
    int moyenne = 0;
    for (int i = 0; i < 10000; i++) {
        moyenne += grid_score(tabGrid[i]);
        if (max < grid_score(tabGrid[i]))
            max = grid_score(tabGrid[i]);
        if (max_grid(tabGrid[i]) > tmax) {
            tmax = max_grid(tabGrid[i]);
        }
    }

    moyenne = moyenne / 10000;
    printf
        ("Le score moyen est de: %i , le score max est de: %li et la tuile max obtenue est : %i\n",
         moyenne, max, tmax);
    for (int i = 0; i < 10000; i++) {
        delete_grid(tabGrid[i]);
    }
    free(tabGrid);


}

/**
* \brief test the optimal strategy
**/
void test_strat_opti() {
    grid g = new_grid();        //Création de la grille de jeu
    strategy strat;
    add_tile(g);                //ajout des 2 premières tuiles pour le jeux
    add_tile(g);
    strat = listFunctionsStrat[1] ();
    while (!game_over(g)) {
        play(g, strat->play_move(NULL, g));
    }
    int Tmax = max_grid(g);
    printf
        ("Vous avez obtenue un score de %i et votre plus grande tuile est %i \n",
         (int) grid_score(g), Tmax);
    delete_grid(g);
}
