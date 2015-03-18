#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "afficher.h"

static char* itoa(int i){ //Permet de transformer un entier en chaine de charactère
  char* ret=malloc(7*sizeof(char)); //Alloue l'espace mémoire permettant d'afficher une chaine de 7 charactères.
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


void afficherLigne(){ //Fonction permettant d'afficher une ligne horizontale à la taille de la grille
  printf("+");
  for(int i=0;i<GRID_SIDE;i++)
    printf("------+");
  printf("\n");
}
void afficher(grid g){  //Affiche l'ensemble d'une grid
  afficherLigne();
  char *nb;
  int val;
  for(int j=0;j<GRID_SIDE;j++){
    for(int i=0;i<GRID_SIDE;i++){
      val=get_tile(g,i,j);
      if(val!=0)
	val=pow(2,val); //Transforme la valeur logarithmique en valeur décimale
      nb=itoa(val);
      printf("|%s",nb);
      free(nb); //Libère la mémoire employer par la chaine de charactère
    }
    printf("|\n");
    afficherLigne();
  }
  printf("Score: %ld \n",grid_score(g));
}

