#include "grid.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

static void turn(grid g);
static void turningxtimes(grid g, int x);
static int firstRota(dir d);
static int secondRota(dir d);
static int rand_a_b(int a, int b);
static void fusion(grid g, dir d);
static void decalage(grid g, dir d);

/**
 * \brief calculate the number of rotation needed for simulated that the direction is UP
 * \param d the direction given by the user
 */
static int firstRota(dir d) {
    switch (d) {
    case UP:
        return 0;
        break;
    case LEFT:
        return 1;
        break;
    case DOWN:
        return 2;
        break;
    default:
        return 3;
        break;
    }
}

struct grid_s {
    tile g[GRID_SIDE][GRID_SIDE];       // On crée un tableau statique de tuiles nous servant à stoquer l'ensemble des tuiles de notre grille.
    unsigned long int score;    //Variable permettant de stocker le score
};

/**
 * \brief return an integer in the interval [a;b[
 */
static int rand_a_b(int a, int b) {     // fonction permettant de retourner un entier dans l'intervalle [a;b[
    return rand() % (b - a) + a;
}

grid new_grid() {
    srand(time(NULL));          // Initialisation de TIME pour le random
    grid gr = malloc(sizeof(struct grid_s));    //Allocation mémoire pour la nouvelle instance de grille
    gr->score = 0;              //Initialisation du score à 0
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {   //Initialisation de l'ensemble des tuiles à 0
            gr->g[i][j] = 0;
        }
    }
    return gr;
}

bool can_move(grid g, dir d) {
    turningxtimes(g, firstRota(d));

    for (int i = 0; i < GRID_SIDE; i++) {
        int tmp = g->g[i][0];
        bool void_tile = (tmp == 0);
        for (int j = 1; j < GRID_SIDE; j++) {
            if (g->g[i][j] == 0)
                void_tile = true;
            else {
                if (tmp == g->g[i][j] || void_tile) {
                    turningxtimes(g, secondRota(d));
                    return true;
                }
                tmp = g->g[i][j];
            }
        }
    }
    turningxtimes(g, secondRota(d));
    return false;
}

void delete_grid(grid g) {
    free(g);
}

void copy_grid(grid src, grid dst) {
    dst->score = src->score;
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            dst->g[i][j] = src->g[i][j];
        }
    }
}

tile get_tile(grid gr, int x, int y) {
    return gr->g[x][y];
}

void set_tile(grid gr, int x, int y, tile t) {
    gr->g[x][y] = t;
}

unsigned long int grid_score(grid g) {
    return g->score;
}

bool game_over(grid g) {
    return !(can_move(g, UP) || can_move(g, DOWN) || can_move(g, LEFT)
             || can_move(g, RIGHT));
}

void add_tile(grid g) {
    int x = rand_a_b(0, GRID_SIDE);     //récupère un entier dans l'intervalle [0;4[ pour la position x
    int y = rand_a_b(0, GRID_SIDE);     //récupère un entier dans l'intervalle [0;4[ pour la position y
    int alea = rand_a_b(0, 10); //récupère un entier dans l'intervalle [0;10[ pour savoir si la tuile aura pour valeur 2 ou 4
    int val_tile = 1;           // la valeur de la tuile, initialisée à 2 par défaut
    while (g->g[x][y] != 0) {   //Vérifie si la position trouvée n'est pas déjà occupée. Si c'est le cas, on retire une nouvelle position
        x = rand_a_b(0, GRID_SIDE);
        y = rand_a_b(0, GRID_SIDE);
    }
    if (alea == 0) {            //Permet de voir si la valeur de la nouvelle tuile est de 4 (Une chance sur dix)
        val_tile = 2;
    }
    set_tile(g, x, y, val_tile);        // affecte la tuile dans la grille
}

void play(grid gr, dir d) {
    do_move(gr, d);             // Effectue le mouvement dans la direction donnée en paramètre
    add_tile(gr);               // Ajoute une tuile de manière aléatoire
}

/**
 * \brief movement of the tiles upwards
 * \param g the grid
 * \param d the direction given by the user
 */
static void decalage(grid g, dir d) {
    int y_libre;
    turningxtimes(g, firstRota(d));
    for (int i = 0; i < GRID_SIDE; i++) {
        y_libre = 0;
        for (int j = 0; j < GRID_SIDE; j++) {
            if (g->g[i][j] != 0) {
                g->g[i][y_libre] = g->g[i][j];
                y_libre++;
            }
        }
        for (; y_libre < GRID_SIDE; y_libre++) {
            g->g[i][y_libre] = 0;
        }
    }
    turningxtimes(g, secondRota(d));
}

/**
 * \brief fusion between two consecutive tiles
 * \param g the grid
 * \param d the direction given by the user
 */
static void fusion(grid g, dir d) {
    turningxtimes(g, firstRota(d));
    for (int x = 0; x <= GRID_SIDE - 1; x++) {
        for (int y = 0; y < GRID_SIDE - 1; y++) {
            if (g->g[x][y] != 0 && g->g[x][y] == g->g[x][y + 1]) {
                g->g[x][y] += 1;
                g->g[x][y + 1] = 0;
                g->score += pow(2, g->g[x][y]);
                y++;
            }
        }
    }
    turningxtimes(g, secondRota(d));
}

void do_move(grid g, dir d) {
    decalage(g, d);             //Place l'ensemble des tuiles dans la direction donnée en paramètre
    fusion(g, d);               //Fusionne les tuiles devant fusionner entre elle
    decalage(g, d);             //Replace les tuiles dans la bonne direction
}


/**
 * \brief turn the grid in the anticlockwise
 * \param g the grid
 */
static void turn(grid g) {
    for (int x = 0; x < GRID_SIDE / 2; x++) {
        for (int y = 0; y < (GRID_SIDE + 1) / 2; y++) {
            int oldx = x;
            int oldy = y;
            int tmp1 = g->g[x][y];
            for (int i = 0; i < GRID_SIDE; i++) {
                /*On va appliquer au point une rotation d'un quart de cercle.
                   Rappel : si p est un point de la forme a+ib alors p*i vaut -b+ia et p*i est l'image de
                   p après y avoir appliqué une rotation  de PI/2 dans le sens antihoraire autour du sens du repère.
                   On décale donc le repère (et donc la tuile) afin que le centre du repère soit au centre de la grille.

                   Pour cela on applique une translation à la tuile de -GRID_SIDE/2;-GRID_SIDE/2.

                   On multiplie ensuite le point obtenu par PI puis on re-décale le repère dans le sens opposé afin de remettre la grille à sa place d'origine.

                   Détails des calculs:
                   Translation:
                   (a+ib)+(-GRID_SIDE/2-i*GRID_SIDE/2)=(a-GRID_SIDE/2) + i(b-GRID_SIDE/2)

                   Rotation:
                   [a-GRID_SIDE/2 + i(b-GRID_SIDE/2)]*i=i*(a-GRID_SIDE/2) + i²(b-GRID_SIDE/2)= -(b-GRID_SIDE/2) + i*(a-GRID_SIDE/2)
                   =-b+GRID_SIDE/2 + i*(a-GRID_SIDE/2)

                   Re-translation:
                   -b+GRID_SIDE/2 + i*(a-GRID_SIDE/2) + (GRID_SIDE/2 +i*GRID_SIDE)
                   =-b+2*GRID_SIDE/2 +i*a=-b+GRID_SIDE +i*a
                 */
                int newx = -oldy + GRID_SIDE - 1;
                int newy = oldx;
                int tmp2 = g->g[newx][newy];
                g->g[newx][newy] = tmp1;
                tmp1 = tmp2;
                oldx = newx;
                oldy = newy;
            }
        }
    }
}

/**
* \brief turn the grid x times
* \param g the grid
* \param x the number of times the grid will be turn
*/
static void turningxtimes(grid g, int x) {
    for (int i = 0; i < x; i++) {
        turn(g);
    }
}

/**
 * \brief calculate the number of rotation needed for reset the rotation after call turningxtime(g,firstRota(g))
 * \param d the direction given by the user
 */
static int secondRota(dir d) {
    return ((4 - firstRota(d)) % 4);
}
