#include <stdio.h>
#include <string.h>

#include "afficher.h"
void afficherLigne(){
    printf("_____________________________\n");
}

void afficher(grid g){
  afficherLigne();
  char *nb;
  for(int i=0;i<GRID_SIZE;i++){
    for(int j=0;j<29;j++){//la taille maxi d'un nombre est de 6,6*4+4+2=29
      nb=itoa(pow(2,get_tile(g,i,j)));
      printf("|%s",nb);
      free(nb);
    }
    printf("|\n");
    afficherLigne();
  }
  afficherLigne();
}

char* itoa(int i){
  char* ret=malloc(7*sizeof(char));
  char* copie=ret;
  memset(ret,' ',6);
  ret[6]=0;
  while(i!=0){
    *copie=(i%10)+48;
    copie++;
  }
  return ret;
}
