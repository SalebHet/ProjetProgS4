#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#include "afficher.h"

static char* itoa(int i){ //Permet de transformer un entier en chaine de charact�re
  char* ret=malloc(7*sizeof(char)); //Alloue l'espace m�moire permettant d'afficher une chaine de 7 charact�res.
  char* copie=ret+5;
  memset(ret,' ',6);
  while(i!=0){
    *copie=(i%10)+48;
    copie--;
    i/=10;
  }
  ret[6]='\0';
  return ret;
}


void afficherLigne(){ //Fonction permettant d'afficher une ligne horizontale � la taille de la grille
  printw("+");
  for(int i=0;i<GRID_SIDE;i++)
    printw("------+");
  printw("\n");
}

void afficher(grid g){  //Affiche l'ensemble d'une grid
  erase();
  afficherLigne();
  char *nb;
  int val;
  for(int j=0;j<GRID_SIDE;j++){
    for(int i=0;i<GRID_SIDE;i++){
      val=get_tile(g,i,j);
      if(val!=0)
	val=pow(2,val); //Transforme la valeur logarithmique en valeur d�cimale
      nb=itoa(val);
      printw("|%s",nb);
      free(nb); //Lib�re la m�moire employer par la chaine de charact�re
    }
    printw("|\n");
    afficherLigne();
  }
  printw("Score: %ld \n",grid_score(g));
refresh();
<<<<<<< HEAD

=======
erase();
>>>>>>> 5de216f239b9b541f4c5af1222ab931320d743ce
}

