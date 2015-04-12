#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

static dir getDir() {           //Fonction permettant de récupérer une touche du clavier et d'y associer une direction
    srand(time(NULL));
    while (true) {
        int c = getch();
        if (c != ERR) {
            switch (c) {
            case KEY_UP:
                return UP;
            case KEY_LEFT:
                return LEFT;
            case KEY_DOWN:
                return DOWN;
            case KEY_RIGHT:
                return RIGHT;
            }
        }
    }
}


int main() {
    srand(time(NULL));
    initscr();
    curs_set(FALSE);
    initscr();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(-1);
    noecho();
    grid g = new_grid();        //Création de la grille de jeu
    add_tile(g);                //ajout des 2 premières tuiles pour le jeux
    add_tile(g);
    printw("z, q, s ou d et 'entree' pour faire un mouvement\n");
    while (!game_over(g)) {     //Boucle jusqu'à la fin de la partie
        display(g);            //Affiche la grille à chaque mouvement
        dir d = getDir();       //Récupère la direction pour le prochain tour
        if (can_move(g, d)) {   //Vérifie si le mouvement est possible
            play(g, d);         //Effectue le mouvement, s'il est possible
        }
    }
    display(g);                //Affiche la grille lors du dernier tour
    printw("game over \n");     //Affiche que la partie est terminée
    delete_grid(g);             //Supprime la grille
    endwin();
    return EXIT_SUCCESS;
}
