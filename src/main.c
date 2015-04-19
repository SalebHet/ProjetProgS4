#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "Keybord.h"


int main() {
    srand(time(NULL));
    initscr();
    curs_set(FALSE);
    initscr();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(-1);
    noecho();
    grid g = new_grid();        //Cr�ation de la grille de jeu
    add_tile(g);                //ajout des 2 premi�res tuiles pour le jeux
    add_tile(g);
    printw("z, q, s ou d et 'entree' pour faire un mouvement\n");
    while (!game_over(g)) {     //Boucle jusqu'� la fin de la partie
        display(g);            //Affiche la grille � chaque mouvement
        dir d = getDir();       //R�cup�re la direction pour le prochain tour
        if (can_move(g, d)) {   //V�rifie si le mouvement est possible
            play(g, d);         //Effectue le mouvement, s'il est possible
        }
    }
    display(g);                //Affiche la grille lors du dernier tour
    printw("game over \n");     //Affiche que la partie est termin�e
    delete_grid(g);             //Supprime la grille
    endwin();
    return EXIT_SUCCESS;
}
