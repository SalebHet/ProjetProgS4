
#ifndef DEPTH
#error "you must define the macro DEPTH with the depth of the algorythme expected max"
#endif

#ifndef STRAT_NAME
#error "you must define the macro STRAT_NAME with the name of the algorythme"
#endif

#ifndef NAME
#error "you must define the macro NAME with the name of the generate library without extension"
#endif

//Les deux lignes suivantes ont été trouvées sur le site suivant :
//https://gcc.gnu.org/onlinedocs/cpp/Stringification.html#Stringification
//Elles permettent d'utiliser le contenu d'une macro comme une chaine de caractère.
#define str(s) #s
#define xstr(s) str(s)

#include "grid.h"
#include "strategy.h"


static int choose_best_dir(grid g, int i, int score);
static double choose_worst_tile(grid g, int i, int score);
static dir ExpectedMax(strategy s, grid g);
#define CONST_SIDE 25000

void free_memless_strat(strategy strat) {
    free(strat);
}

/**
* \brief find if a grid is homogeneous or not. The int returned is higher if the grid is highly homogeneous.
* \brief grid g, the grid
* \brief int i, the abscissa of the tile
* \brief int j, the ordinate of the tile
**/
static int homogeneous_tile(grid g, int i, int j) {
    int diff = 0;
    if (i != 0 && get_tile(g, i - 1, j) != 0)
        diff += abs(get_tile(g, i, j) - get_tile(g, i - 1, j));
    if (j != 0 && get_tile(g, i, j - 1) != 0)
        diff += abs(get_tile(g, i, j) - get_tile(g, i, j - 1));
    return diff;
}

/**
 * \brief return 2 if the tile (i;j) is in the corner, 1 if it is in an other part of the edge, else 0
 * \param int i, the tile's abscissa
 * \param int j, the tile's ordinate
 */
static int in_corner(int i, int j) {
    int result = 0;
    if (i == 0 || i == GRID_SIDE - 1)
        result++;
    if (j == 0 || j == GRID_SIDE - 1)
        result++;
    return result;
}

/**
* \brief return the value of the grid
* \param grid g, the grid
* \param int score, the score before the move
**/
static int value_grid(grid g, int score) {
    if (game_over(g))
        return 0;
    int score_move = grid_score(g) - score;
    int void_tile = 0;
    int homo = 0;

    int max_tile, max_i, max_j;
    max_tile = 0;
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            if (get_tile(g, i, j) == 0) {
                void_tile++;
            } else {
                homo += homogeneous_tile(g, i, j);
                if (get_tile(g, i, j) > max_tile) {
                    max_tile = get_tile(g, i, j);
                    max_i = i;
                    max_j = j;
                } else if (get_tile(g, i, j) == max_tile
                           && in_corner(i, j) > in_corner(max_i, max_j)) {
                    max_tile = get_tile(g, i, j);
                    max_i = i;
                    max_j = j;
                }
            }
        }
    }
    int val_on_side = 0;
    if (max_i == 0 || max_i == GRID_SIDE - 1)
        val_on_side += CONST_SIDE;
    if (max_j == 0 || max_j == GRID_SIDE - 1)
        val_on_side += CONST_SIDE;
    return score_move * 16 + void_tile * 25 + 8000 * (10000 - homo) +
        val_on_side;
}

/**
* \brief turn an int into a direction
* \param int i, the direction as an int: 0 for UP, 1 for RIGHT, 2 for DOWN. The default direction is LEFT.
**/
static dir int_to_dir(int i) {
    if (i == 0)
        return UP;
    if (i == 1)
        return RIGHT;
    if (i == 2)
        return DOWN;
    else {
        return LEFT;
    }
}

/**
* \brief this function choose the best grid
* \param grid g, the grid
* \param int i, how many moves ahead
* \param int score, the score before the move
**/
static int choose_best_dir(grid g, int i, int score) {
    if (game_over(g))           // si on a un game over, alors la valeur de la grille est de 0
        return 0;
    if (i == 0)                 //sinon de celle du score
        return value_grid(g, score);
    grid g2 = new_grid();
    int vMax = 0;
    for (int a = 0; a < 4; a++) {       // 4 représente ici le nombre de directions
        dir d = int_to_dir(a);
        if (!(can_move(g, d)))
            continue;
        copy_grid(g, g2);
        score = grid_score(g);
        do_move(g2, d);
        int vInter = choose_worst_tile(g, i, score);
        if (vInter > vMax)
            vMax = vInter;
    }
    delete_grid(g2);
    return vMax;
}

/**
 *
 * \brief this function returns the medium grid's value obtained by placing 2 or 4 in a free case
 * \param grid g, the grid
 * \param int i, how many moves ahead
 * \param int score, the score before the move
 **/
static double choose_worst_tile(grid g, int i, int score) {
    if (game_over(g))
        return 0;
    int n = 0;
    int m = 0;
    for (int x = 0; x < GRID_SIDE; x++) {
        for (int y = 0; y < GRID_SIDE; y++) {
            if (get_tile(g, x, y) == 0) {
                set_tile(g, x, y, 1);
                score = grid_score(g);
                m += choose_best_dir(g, i - 1, score);
                set_tile(g, x, y, 2);
                score = grid_score(g);
                m += choose_best_dir(g, i - 1, score);
                set_tile(g, x, y, 0);
                score = grid_score(g);
                n += 2;
            }
        }
    }
    if (n == 0)
        return choose_best_dir(g, i - 1, score);
    return m / n;
}

/**
* \brief give the direction choosen
* \param strategy s, the strategy choosen
* \param grid g, the grid
**/
static dir ExpectedMax(strategy s, grid g) {
    double vMax = 0;
    dir d;
    grid g2 = new_grid();
    for (int i = 0; i < 4; i++) {       //on teste les 4 directions
        dir d2 = int_to_dir(i);
        if (!(can_move(g, d2)))
            continue;
        copy_grid(g, g2);
        int score = grid_score(g);
        do_move(g2, d2);
        double vInter = choose_worst_tile(g2, DEPTH, score);
        if (vInter >= vMax) {
            vMax = vInter;
            d = d2;
        }
    }
    delete_grid(g2);
    return d;
}

strategy NAME() {
    strategy s = malloc(sizeof(struct strategy_s));
    s->play_move = ExpectedMax;
    s->name = xstr(STRAT_NAME);
    s->mem = NULL;
    s->free_strategy = free_memless_strat;
    return s;
}
