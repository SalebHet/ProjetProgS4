#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

static dir getDir(){  //Fonction permettant de r�cup�rer une touche du clavier et d'y associer une direction
  while(true){
  	int c = getch();
  	if(c!=ERR){
    	switch(c){
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


int main(){
    initscr();
curs_set(FALSE);
    keypad(stdscr,TRUE);
    timeout(-1);
    noecho();
    grid g = new_grid(); //Cr�ation de la grille de jeu
    add_tile(g); //ajout des 2 premi�re tiles pour le jeux
    add_tile(g);
    printw("z, q, s ou d et 'entree' pour faire un mouvement\n");
    while(!game_over(g)){ //Boucle jusqu'� la fin de la partie
        afficher(g); //Affiche la grille � chaque mouvement
        dir d = getDir(); //R�cup�re la direction pour le prochain tour
        if(can_move(g,d)){ //V�rifie si le mouvement est possible
	  		play(g,d); //Effectue le mouvement si le mouvement est possible
		}
    }
    afficher(g); //Affiche la grid lors du dernier tour
    printw("game over \n"); //Affiche que la partie est terminer
    delete_grid(g); //Supprime la Grid
    endwin();
    refresh();
    return EXIT_SUCCESS;
}
