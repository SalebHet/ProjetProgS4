#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#include "afficher.h"

static char *itoa(int i);
static void displayline();

/**
 * \brief turns an int into a 6 sized string
 * \pre the number must be lower or equal to one million in base 10.
 */
static char *itoa(int i) {
    char *ret = malloc(7 * sizeof(char));       //Alloue l'espace mémoire permettant de stocker une chaine de 7 caractères. (dont le 0 final).
    char *copie = ret + 5;      //Le bit de poid faible est à droite, donc on commence par la droite.
    memset(ret, ' ', 6);        //Par défaut, les six premiers caractères sont des espaces.
    while (i != 0) {
        *copie = (i % 10) + 48; //Le 0 est codé par le nombre 48, le 1 par 49, etc...
        copie--;                //on passe au caractère de gauche.
        i /= 10;
    }
    ret[6] = '\0';              //Le septième caractère devient un 0.
    return ret;
}

/**
 * \brief display a line of GRID_SIZE times the size of a tile (left or up side)
 * \pre the window must be large enough to display the grid
 */
static void displayline() {   //Fonction permettant d'display une ligne horizontale de la taille de la grille.
    printw("+");
    for (int i = 0; i < GRID_SIDE; i++)
        printw("------+");
    printw("\n");
}

void display(grid g) {
    erase();                    //on efface la fenêtre
    displayline();
    char *nb;
    int val;
    for (int j = 0; j < GRID_SIDE; j++) {
        for (int i = 0; i < GRID_SIDE; i++) {
            val = get_tile(g, i, j);
            if (val != 0)
                val = pow(2, val);      //Transforme la valeur logarithmique en valeur décimale.
            nb = itoa(val);
            printw("|%s", nb);
            free(nb);           //Libère la mémoire employée par la chaine de caractères.
        }
        printw("|\n");
        displayline();
    }
    printw("Score: %ld \n", grid_score(g));
    refresh();                  //On actualise l'affichage de la fenêtre

}
