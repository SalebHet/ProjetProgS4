

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "grid.h"
/**
 * \brief list of the possible state of the game
 */
typedef enum {MOVE_UP=UP,MOVE_LEFT=LEFT,MOVE_DOWN=DOWN,MOVE_RIGHT=RIGHT,RUN,GAME_OVER,QUIT} state;

/**
 * \brief contain the information relative of the game
 */
typedef struct{
  state st;
  bool disable_play_mouse;
  Uint32 time;
  int fps;
  grid g;
} *game;
/**
 * \brief Initialise the game structure
 * \return created a game structure at the state play
 */
game new_game(){
  game g=malloc(sizeof(*g));
  g->st=RUN;
  g->disable_play_mouse=false;
  g->g=new_grid();
  g->fps=0;
  g->time=0;
  add_tile(g->g);
  add_tile(g->g);
  return g;
}
/**
 * \brief free the game
 * \param g the game to free
 */
void free_game(game g){
  delete_grid(g->g);
  free(g);
}

/**
 * \brief contain the variables needed for the display
 */
typedef struct{
  SDL_Surface* screen;
  TTF_Font** fonts;
} *vars_draw;

/**
 * \brief initialise the vars_draw structure and the SDL display
 * \return created a structure with the surface of the screen and a police in 4 diferents sizes
 */
vars_draw new_vars_draw(){
  vars_draw v=malloc(sizeof(*v));
  //l'écran de rendu comporte GRID_SIDE tuiles de 100 pixels de cotés chacuns (taille arbitraire)
  //il possède aussi une marge de 50 pixels en bas (encore une fois, taille arbitraire) pour pouvoir afficher le score
  //les pixels sont codés sur 32 bits
  v->screen=SDL_SetVideoMode( GRID_SIDE*100,GRID_SIDE*100+50, 32, SDL_HWSURFACE );
  v->fonts=malloc(sizeof(TTF_Font*)*4);//on utilise 4 polices de tailles différentes pour pouvoir écrire toutes les valeurs
  //de tuiles sans déborder.
  v->fonts[0]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",60);
  v->fonts[1]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",40);
  v->fonts[2]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",30);
  v->fonts[3]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",25);
  return v;
}
/**
 * \brief destroy a vars_draw structure
 * \param v the vars_draw to destroy
 */
void free_vars_draw(vars_draw v){
  for(int i=0;i<4;i++)//il y a 4 polices à libérer dans le tableau
    TTF_CloseFont(v->fonts[i]);
  free(v->fonts);
  free(v);
}

/**
 * \brief indicate the movement of the mouse
 * \param x the relative motion of the mouse in X direction
 * \param y the relative motion of the mouse in Y direction
 * \param fps the number of frame per second of the application
 * \return MOVE_<DIRECTION> if a movement is detected, RUN else
 */
state mouse_move(int x,int y,int fps){
  const int real_movement = 400;//le déplacement doit etre de au moins 400 pixel/s pour etre considéré comme valide
  if(fabs(x)>fabs(y)){
    if(x*fps<-real_movement)
      return MOVE_LEFT;
    else if(x*fps>real_movement)
      return MOVE_RIGHT;
  }
  else{
    if(y*fps<-real_movement)
      return MOVE_UP;
    else if(y*fps>real_movement)
      return MOVE_DOWN;
  }
  return RUN;
}

/**
 * \brief process the extern events and update the state of the game if needed
 * \param g the structure of the actual game
 */
void event(game g){
  SDL_Event* event=malloc(sizeof(SDL_Event));
  while(SDL_PollEvent(event)){
    switch(event->type){
    case SDL_KEYDOWN:
      switch(event->key.keysym.sym){
      case SDLK_ESCAPE:
	g->st=QUIT;
	break;
      case SDLK_UP:
	g->st=MOVE_UP;
	break;
      case SDLK_DOWN:
	g->st=MOVE_DOWN;
	break;
      case SDLK_RIGHT:
	g->st=MOVE_RIGHT;
	break;
      case SDLK_LEFT:
	g->st=MOVE_LEFT;
	break;
      default:
	break;
      }
      break;
    case SDL_QUIT:
      g->st=QUIT;
      break;
    case SDL_MOUSEMOTION:
      if(!g->disable_play_mouse &&  event->motion.state&SDL_BUTTON(1)){
	state st=mouse_move(event->motion.xrel,event->motion.yrel,g->fps);
	if(st!=RUN){
	  g->st=st;
	  g->disable_play_mouse=true;
	}
      }
      break;
    case SDL_MOUSEBUTTONUP:
      g->disable_play_mouse=false;
      break;
    default:
      break;
    }
  }
  free(event);
}
/**
 * \brief return the color of the tile for this value
 * \param f a pointer to the format needed for the pixel
 * \param tile the value of the tile
 */
Uint32 get_tile_color(SDL_PixelFormat* f,int tile){
  int r,g,b;
  if(tile == 0)
    r=g=b=80;
  else{
    b=16*fmax(0,fmax(11-fabs(3-tile),16-fabs(18-tile)-1));
    r=16*fmax(11-fabs(3-tile),16-fabs(9-tile)-1);
    g=16*fmax(11-fabs(3-tile),fmax(16-fabs(9-tile)-1,16-fabs(14-tile)-1));
  }
  return SDL_MapRGB(f,r,g,b);
}


/**
 * \brief draw the game
 * \param v the variable vars_draw of the actual window
 * \param g the structure of the actual game
 */
void draw(vars_draw v,game g){
  Uint32 rmask, gmask, bmask, amask;
  //on définit les masques pour déterminer quelle partie du pixel correspond à quelle couleur
 rmask = 0xff000000;
 gmask = 0x00ff0000;
 bmask = 0x0000ff00;
 amask = 0x000000ff;
 //une tuile a pour taille 100x100 et est codée sur 32 bits.
 SDL_Surface *tile=SDL_CreateRGBSurface(SDL_HWSURFACE,100,100,32,rmask,gmask,bmask,amask);

 SDL_FillRect(tile, NULL,SDL_MapRGBA(tile->format,0,0,0,0));
 SDL_Rect rect={5,5,90,90};//on définit une marge de 5 pixels pour chaque tuile
 SDL_Color c={0,0,0};//la couleur du texte est le noir
  char* str=malloc(15*sizeof(char));
  SDL_FillRect(v->screen, NULL, SDL_MapRGB(v->screen->format, 100, 100, 100));//on définit un fond gris foncé
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      int t=get_tile(g->g,x,y);
      SDL_FillRect(tile, &rect,get_tile_color(tile->format,t));
      SDL_Rect tilePos={100*x,100*y};//toujours 100 pour la taille d'une tuile

      if(t!=0){

	t=pow(2,t);
	int size=sprintf(str,"%d",t);
	int size_font;
	if(size<3)//on adapte la taille de la police en fonction du nombre de caractères que contient la valeur de la tuile
	  size_font=0;
	else if(size==3)
	  size_font=1;
	else if(size==4)
	  size_font=2;
	else
	  size_font=3;
	SDL_Surface* s=TTF_RenderText_Solid( v->fonts[size_font], str, c );
	assert(s->w <= tile->w-10);//la taille du texte doit rentrer dans une tuile privée de sa marge
	assert(s->h <= tile->h-10);
	SDL_Rect tileRect={50 - (s->w)/2 , 50 - (s->h)/2 , 0,0};//on écrit le texte au millieu de la tuile (50 = 100/2)
	SDL_BlitSurface(s,NULL,tile,&tileRect);
	SDL_FreeSurface(s);
      }

      SDL_BlitSurface(tile,NULL,v->screen,&tilePos);
    }
  }
  sprintf(str,"score : %5ld",grid_score(g->g));
  SDL_Rect scorePos={0,400};//on affiche le score en bas à gauche (400 veut dire en dessous de la 4eme tuile)
  SDL_Surface *der=TTF_RenderText_Solid( v->fonts[2],str , c );
  SDL_BlitSurface(der,NULL,v->screen,&scorePos);
  SDL_Flip(v->screen);

  free(str);
  SDL_FreeSurface(tile);
  SDL_FreeSurface(der);
}
/**
 * \brief process the game
 * \param g the structure of the actual game
 */
void execute(game g){
  Uint32 time=SDL_GetTicks();
  g->fps=1000.f/((time-g->time));//SDL_GetTicks renvoie une valeur en ms, il faut la diviser par 1000 pour avoir une valeur en secondes 
  g->time=time;
  if(g->st<RUN){
    dir d=g->st;
    if(can_move(g->g,d))
      play(g->g,d);
    if(game_over(g->g))
      g->st=GAME_OVER;
    else
      g->st=RUN;
  }
  else if(g->st==GAME_OVER)
    g->st=QUIT;
}


int main(int argc,char** argv){
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  srand(time(NULL));
  game g=new_game();
  vars_draw v=new_vars_draw();

#if 0
  int i=2;
  for(int x=0;x<GRID_SIDE;x++)
    for(int y=0;y<GRID_SIDE;y++)
      set_tile(g->g,x,y,i++);
#endif
  while(g->st!=QUIT){
    event(g);
    execute(g);
    draw(v,g);
  }


  free_game(g);
  free_vars_draw(v); 
  TTF_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
