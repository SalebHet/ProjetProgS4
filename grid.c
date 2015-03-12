#include "grid.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

static void turn(grid g);
static void turningxtimes(grid g, int x);
static int firstRota(dir d);
static int secondRota(dir d);

static int firstRota(dir d)
{
  switch (d){
    case UP:
        return 0;
        break;
    case LEFT:
        return 1;
        break;
    case DOWN:
        return 2;
        break;
    case RIGHT:
        return 3;
        break;
    }
}
struct grid_s{
  tile g [GRID_SIDE][GRID_SIDE]; // On cr�e un tableau statique de tiles nous servant � stoquer l'ensemble des tiles de notre grille.
  unsigned long int score; //Variable permettant de stocker le score
};

static int rand_a_b(int a, int b){ // fonction permettant de retourner un entier dans l'intervalle [a;b[
  return rand()%(b-a) +a;
}

grid new_grid(){ // Fonction permettant l'instantiation d'une nouvelle grille
    srand(time(NULL)); // Initialisation de TIME pour le random
  grid gr = malloc(sizeof(struct grid_s)); //Allocation m�moire pour la nouvelle instance de grille
  gr->score=0; //Initialisation du score � 0
  for(int i=0;i<GRID_SIDE;i++){
    for(int j=0;j<GRID_SIDE;j++){ //Initialisation de l'ensemble des tuiles � 0
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
  turningxtimes(g,firstRota(d));

  for(int i=0;i<GRID_SIDE;i++){
    int tmp=g->g[i][0];
    bool void_tile= (tmp==0);
    for(int j=1;j<GRID_SIDE;j++){
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

  turningxtimes(g,secondRota(d));

}
void delete_grid(grid g){ //Permet de lib�rer l'espace m�moire employer par une instance de grille
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

tile get_tile (grid gr, int x, int y){ // Fonction retournant une tile situ� en position (x,y) dans une instance de grid)
  return gr->g[x][y];
}

void set_tile (grid gr, int x, int y, tile t){ //affecte une tile � une position(x,y) dans une grid
  gr->g[x][y]=t;
}

unsigned long int grid_score (grid g){ //retourne le score d'une grid
  return g->score;
}

bool game_over (grid g){ // Evalue si un mouvement est encore possible dans une grid si ce n'est pas le cas retourne "game_over"
  return !(can_move(g, UP) || can_move(g, DOWN) || can_move(g, LEFT) || can_move(g, RIGHT));
}

void add_tile(grid g){ //Ajoute une tile de mani�re al�atoire dans une grid
  int x = rand_a_b(0, 4); //r�cup�re un entier dans l'intervalle [0;4[ pour la position x
  int y = rand_a_b(0, 4); //r�cup�re un entier dans l'intervalle [0;4[ pour la position y
  int alea = rand_a_b(0, 10); //r�cup�re un entier dans l'intervalle [0;10[ pour savoir si la tuile aura la valeur 2 ou 4
  int bouh = 0;
  while (g->g[x][y]!=0){ //V�rifie si la position trouv� n'est pas d�j� occup� si c'est le cas retire une nouvelle position
    x = rand_a_b(0, 4);
    y = rand_a_b(0, 4);
  }
  if (alea == 0){ //Permet de voir si la valeur de la nouvelle tuile est de 4 (Une chance sur dix)
    bouh = 2;
  }
  else{ //Met la valeur de la tuile � 2
    bouh = 1;
  }
  set_tile(g, x, y, bouh); // affecte la tuile dans la grid
}

void play(grid gr,dir d){
  do_move (gr, d); // Effectue le mouvement dans la direction donn� en param�tre
  add_tile(gr); // Ajoute une tile de mani�re al�atoire
}

/*static void decalage(grid g,dir d){
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
*/
/**
* \brief movement of the tiles upwards
* \param g the grid
* \param d the direction given by the user
*/
static void decalage(grid g,dir d){
    int y_libre = 0;
    turningxtimes(g, firstRota(d));
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
    turningxtimes(g, secondRota(d));
}

/**
 * \brief fusion between two consecutive tiles
 * \param g the grid
 * \param d the direction given by the user
 */
static void fusion (grid g, dir d){
    turningxtimes(g, firstRota(d));
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
    turningxtimes(g, secondRota(d));
}
/**
*\brief make a move
*\param g the grid
*\param d the direction given by the user
*/
void do_move(grid g,dir d){ //Fonction permettant d'effectuer un mouvement
  decalage(g,d); //Plaque l'ensemble des tuiles dans la direction donn� en param�tre
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
	  Rappel : si p est un point de la forme a+ib alors p*i vaut -b+ia et p*i est l'image de p apr�s y avoir appliqu� une rotion
	  de PI/2 dans le sens antihorraire autour du sens du reperre.
	  on d�cale donc le rep�re (et donc la tuile) afin que le centre du rep�re soit au centre de la grille
	  Pour cel� on applique une translation � la tuile de -GRID_SIDE/2;-GRID_SIDE/2
	  on multiplie ensuite le point obtenu par PI puis on red�cale le rep�re dans le sens oppos� afin de remettre la grille � sa
	  place d'origine.
	  d�tails des calculs:
	  translation:
	  (a+ib)+(-GRID_SIDE/2-i*GRID_SIDE/2)=(a-GRID_SIDE/2) + i(b-GRID_SIDE/2)
	  rotation:
	  [a-GRID_SIDE/2 + i(b-GRID_SIDE/2)]*i=i*(a-GRID_SIDE/2) + i�(b-GRID_SIDE/2)= -(b-GRID_SIDE/2) + i*(a-GRID_SIDE/2)
	  =-b+GRID_SIDE/2 + i*(a-GRID_SIDE/2)
	  re-translation:
	  -b+GRID_SIDE/2 + i*(a-GRID_SIDE/2) + (GRID_SIDE/2 +i*GRID_SIDE)
	  =-b+2*GRID_SIDE/2 +i*a=-b+GRID_SIDE +i*a
	 */
        int newx=-oldy+GRID_SIDE-1;
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
/**
* \brief turn the grid x times
* \param g the grid
* \param x the number of times the grid will be turn
*/
static void turningxtimes (grid g,int x){
    for (int i = 0; i<x; i++){
        turn(g);
    }
}

static int secondeRota(dir d){
    return ((4-firstRota(d))%4);
}
