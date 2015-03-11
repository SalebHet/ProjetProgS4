#include "grid.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

static void turn(grid g);

struct grid_s{
  tile g [GRID_SIDE][GRID_SIDE]; // On crée un tableau statique de tiles nous servant à stoquer l'ensemble des tiles de notre grille.
  unsigned long int score; //Variable permettant de stocker le score
};

static int rand_a_b(int a, int b){ // fonction permettant de retourner un entier dans l'intervalle [a;b[
  return rand()%(b-a) +a;
}

grid new_grid(){ // Fonction permettant l'instantiation d'une nouvelle grille
    srand(time(NULL)); // Initialisation de TIME pour le random
  grid gr = malloc(sizeof(struct grid_s)); //Allocation mémoire pour la nouvelle instance de grille
  gr->score=0; //Initialisation du score à 0
  for(int i=0;i<GRID_SIDE;i++){
    for(int j=0;j<GRID_SIDE;j++){ //Initialisation de l'ensemble des tuiles à 0
      gr->g[i][j]=0;
    }
  }
  return gr;
}
bool not_over(int i,dir d)
{
  if(d==1)
    return i<GRID_SIDE;
  else
    return i>=0;
}

bool can_move (grid g, dir d)
{
  int d2,i,j,dep;
  int *inc1,*inc2;

  switch(d){
  case UP:
  case LEFT:
    d2=1;
    dep=0;
    break;

  case DOWN:
  case RIGHT:
    d2=-1;
    dep=GRID_SIDE-1;
    break;
  }

  switch(d){
  case UP:
  case DOWN:
    inc1=&i;
    inc2=&j;
    break;

  case LEFT:
  case RIGHT:
    inc1=&j;
    inc2=&i;
    break;
  }
  unsigned long int tmp;
  bool void_tile;
  for((*inc1)=dep;not_over(*inc1,d2);(*inc1)+=d2){
    (*inc2)=dep;
    tmp=g->g[i][j];
    void_tile=(tmp==0);//si la case [i][j] vaut 0 alors on a rencontré une case vide
    (*inc2)+=d2;//et on pase à la case suivante,on vient de traiter la première
    for(;not_over(*inc2,d2);(*inc2)+=d2){
      if(g->g[i][j]==0)
	void_tile=true;
      else{
	if(tmp==g->g[i][j] || void_tile )
	  return true;
	tmp=g->g[i][j];
      }
    }
  }

  return false;


#if 0
  unsigned int tmp;
  bool void_tile;

  switch(d)
    {
    case UP:
      for(int i=0;i<GRID_SIDE;i++)
	{
	  tmp=g->g[i][0];
	  void_tile=tmp==0;
	  for(int j=1;j<GRID_SIDE;j++)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] || void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;

    case DOWN:
      for(int i=0;i<GRID_SIDE;i++)
	{
	  tmp=g->g[i][GRID_SIDE-1];
	  void_tile=tmp==0;
	  for(int j=GRID_SIDE-2;j>=0;j--)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] ||  void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;

    case LEFT:
      for(int j=0;j<GRID_SIDE;j++)
	{
	  tmp=g->g[0][j];
	  void_tile=tmp==0;
	  for(int i=1;i<GRID_SIDE;i++)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] || void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;

    case RIGHT:
      for(int j=0;j<GRID_SIDE;j++)
	{
	  tmp=g->g[GRID_SIDE-1][j];
	  void_tile=tmp==0;
	  for(int i=GRID_SIDE-2;i>=0;i--)
	    {
	      if(g->g[i][j]==0)
		void_tile=true;
	      else{
		if(tmp==g->g[i][j] || void_tile )
		  return true;
		tmp=g->g[i][j];
	      }
	    }
	}
      return false;
      break;
    }
  return false;
#endif
}
void delete_grid(grid g){ //Permet de libérer l'espace mémoire employer par une instance de grille
  free(g);
}

void copy_grid (grid src, grid dst){ // Fonction permettant de retourner une grille dans une nouvelle instance de grille
  dst->score=src->score;
  for(int i=0;i<GRID_SIDE;i++){
    for(int j=0;j<GRID_SIDE;j++){
      dst->g[i][j]=src->g[i][j];
    }
  }
}

tile get_tile (grid gr, int x, int y){ // Fonction retournant une tile situé en position (x,y) dans une instance de grid)
  return gr->g[x][y];
}

void set_tile (grid gr, int x, int y, tile t){ //affecte une tile à une position(x,y) dans une grid
  gr->g[x][y]=t;
}

unsigned long int grid_score (grid g){ //retourne le score d'une grid
  return g->score;
}

bool game_over (grid g){ // Evalue si un mouvement est encore possible dans une grid si ce n'est pas le cas retourne "game_over"
  return !(can_move(g, UP) || can_move(g, DOWN) || can_move(g, LEFT) || can_move(g, RIGHT));
}

void add_tile(grid g){ //Ajoute une tile de manière aléatoire dans une grid
  int x = rand_a_b(0, 4); //récupère un entier dans l'intervalle [0;4[ pour la position x
  int y = rand_a_b(0, 4); //récupère un entier dans l'intervalle [0;4[ pour la position y
  int alea = rand_a_b(0, 10); //récupère un entier dans l'intervalle [0;10[ pour savoir si la tuile aura la valeur 2 ou 4
  int bouh = 0;
  while (g->g[x][y]!=0){ //Vérifie si la position trouvé n'est pas déjà occupé si c'est le cas retire une nouvelle position
    x = rand_a_b(0, 4);
    y = rand_a_b(0, 4);
  }
  if (alea == 0){ //Permet de voir si la valeur de la nouvelle tuile est de 4 (Une chance sur dix)
    bouh = 2;
  }
  else{ //Met la valeur de la tuile à 2
    bouh = 1;
  }
  set_tile(g, x, y, bouh); // affecte la tuile dans la grid
}

void play(grid gr,dir d){
  do_move (gr, d); // Effectue le mouvement dans la direction donné en paramètre
  add_tile(gr); // Ajoute une tile de manière aléatoire
}

static void decalage(grid g,dir d){
  int x_libre,y_libre;
  switch(d){

  case RIGHT:
    x_libre=GRID_SIDE-1;
    for(int j=0;j<GRID_SIDE;j++){
      x_libre=GRID_SIDE-1;
      for(int i=GRID_SIDE-1;i>=0;i--){
	if(g->g[i][j]!=0){
	  g->g[x_libre][j]=g->g[i][j];
	  x_libre--;
	}
      }
      for(;x_libre>=0;x_libre--){
	g->g[x_libre][j]=0;

      }
    }

    break;


  case LEFT:
    x_libre=0;
    for(int j=0;j<GRID_SIDE;j++){
      x_libre=0;
      for(int i=0;i<GRID_SIDE;i++){
	if(g->g[i][j]!=0){
	  g->g[x_libre][j]=g->g[i][j];
	  x_libre++;
	}

      }
      for(;x_libre<GRID_SIDE;x_libre++){
	g->g[x_libre][j]=0;
      }
    }
    break;

  case UP:
    y_libre=0;
    for(int i=0;i<GRID_SIDE;i++){
      y_libre=0;
      for(int j=0;j<GRID_SIDE;j++){
	if(g->g[i][j]!=0){
	  g->g[i][y_libre]=g->g[i][j];
	  y_libre++;
	}
      }
      for(;y_libre<GRID_SIDE;y_libre++){
	g->g[i][y_libre]=0;
      }
    }
    break;

  case DOWN:
    y_libre=GRID_SIDE-1;
    for(int i=0;i<GRID_SIDE;i++){
      y_libre=GRID_SIDE-1;
      for(int j=GRID_SIDE-1;j>=0;j--){
	if(g->g[i][j]!=0){
	  g->g[i][y_libre]=g->g[i][j];
	  y_libre--;
	}

      }
      for(;y_libre>-1;y_libre--){
        g->g[i][y_libre]=0;
      }
    }
    break;
  }
}
void static fusion (grid g, dir d){
  switch(d){
  case LEFT:
    for (int y = 0; y<=GRID_SIDE-1; y++){
      for (int x = 0; x<GRID_SIDE-1; x++){
	if (g->g[x][y]!=0 && g->g[x][y] == g->g[x+1][y]){
	  g->g[x][y] += 1;
	  g->g[x+1][y] = 0;
	  g->score+=pow(2,g->g[x][y]);
	  x++;
	}
      }
    }
    break;
  case RIGHT:
    for (int y = 0; y<=GRID_SIDE-1; y++){
      for (int x = GRID_SIDE-1; x >= 0; x--){
	if (g->g[x][y]!=0 && g->g[x][y]==g->g[x-1][y]){
	  g-> g[x][y]+=1;
	  g-> g[x-1][y] = 0;
	  g->score+=pow(2,g->g[x][y]);
	  x--;
	}
      }
    }
    break;
  case UP:
    for (int x = 0; x<=GRID_SIDE-1; x++){
      for (int y = 0; y<GRID_SIDE-1; y++){
	if (g->g[x][y]!=0 && g->g[x][y]==g->g[x][y+1]){
	  g-> g[x][y]+= 1;
	  g-> g[x][y+1] = 0;
	  g->score+=pow(2,g->g[x][y]);
	  y++;
	}
      }
    }
    break;
  case DOWN:
    for (int x = 0; x<=GRID_SIDE-1; x++){
      for (int y = GRID_SIDE-2; y>=0; y--){
	if (g->g[x][y]!=0 && g->g[x][y]==g->g[x][y+1]){
	  g-> g[x][y]+=1;
	  g-> g[x][y+1] = 0;
	  g->score+=pow(2,g->g[x][y]);
	  y--;
	}
      }
    }
    break;
  }
}

void do_move(grid g,dir d){ //Fonction permettant d'effectuer un mouvement
  decalage(g,d); //Plaque l'ensemble des tuiles dans la direction donné en paramètre
  fusion(g,d); //Fusionne les tuiles devant fusionner entre elle
  decalage(g,d); //Replaque les tuiles dans la bonne direction
}


/**
 * \brief turn the grid in the anticlockwise
 * \param g the grid
 */
static void turn(grid g)
{
  for(int x=0;x<GRID_SIDE/2;x++){
    for(int y=0;y<(GRID_SIDE+1)/2;y++){
      int oldx=x;
      int oldy=y;
      int tmp1=g->g[x][y];
      for(int i=0;i<4;i++){
	/*On va appliquer au point une rotation d'un quart de cercle.
	  Rappel : si p est un point de la forme a+ib alors p*i vaut -b+ia et p*i est l'image de p après y avoir appliqué une rotion
	  de PI/2 dans le sens antihorraire autour du sens du reperre.
	  on décale donc le repère (et donc la tuile) afin que le centre du repère soit au centre de la grille
	  Pour celà on applique une translation à la tuile de -GRID_SIDE/2;-GRID_SIDE/2
	  on multiplie ensuite le point obtenu par PI puis on redécale le repère dans le sens opposé afin de remettre la grille à sa
	  place d'origine.
	  détails des calculs:
	  translation:
	  (a+ib)+(-GRID_SIDE/2-i*GRID_SIDE/2)=(a-GRID_SIDE/2) + i(b-GRID_SIDE/2)
	  rotation:
	  [a-GRID_SIDE/2 + i(b-GRID_SIDE/2)]*i=i*(a-GRID_SIDE/2) + i²(b-GRID_SIDE/2)= -(b-GRID_SIDE/2) + i*(a-GRID_SIDE/2)
	  =-b+GRID_SIDE/2 + i*(a-GRID_SIDE/2)
	  re-translation:
	  -b+GRID_SIDE/2 + i*(a-GRID_SIDE/2) + (GRID_SIDE/2 +i*GRID_SIDE)
	  =-b+2*GRID_SIDE/2 +i*a=-b+GRID_SIDE +i*a
	 */
	int newx=-oldy+GRID_SIDE;
	int newy=oldx;
	int tmp2=g->g[newx][newy];
	g->g[newx][newy]=tmp1;
	tmp1=tmp2;
	oldx=newx;
	oldy=newy;
      }
    }
  }
}
