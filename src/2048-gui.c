

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "grid.h"

typedef enum {MOVE_UP=UP,MOVE_LEFT=LEFT,MOVE_DOWN=DOWN,MOVE_RIGHT=RIGHT,RUN,GAME_OVER,QUIT} state;
typedef struct{
  state st;
  bool disable_play_mouse;
  Uint32 time;
  int fps;
  grid g;
} *game;
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


typedef struct{
  SDL_Surface* screen;
  TTF_Font** fonts;
} *vars_draw;
vars_draw new_vars_draw(){
  vars_draw v=malloc(sizeof(*v));
  v->screen=SDL_SetVideoMode( 400,450, 32, SDL_HWSURFACE );
  v->fonts=malloc(sizeof(TTF_Font*)*4);
  v->fonts[0]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",60);
  v->fonts[1]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",40);
  v->fonts[2]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",30);
  v->fonts[3]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",25);
  return v;
}


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
    default:
      break;
    }
  }
}

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

void draw(vars_draw v,game g){
  Uint32 rmask, gmask, bmask, amask;

 rmask = 0xff000000;
 gmask = 0x00ff0000;
 bmask = 0x0000ff00;
 amask = 0x000000ff;

 SDL_Surface *tile=SDL_CreateRGBSurface(SDL_HWSURFACE,100,100,32,rmask,gmask,bmask,amask);

 SDL_FillRect(tile, NULL,SDL_MapRGBA(tile->format,0,0,0,0));
 SDL_Rect rect={5,5,90,90};
 SDL_Color c={0,0,0};
  char* str=malloc(15*sizeof(char));
  SDL_FillRect(v->screen, NULL, SDL_MapRGB(v->screen->format, 100, 100, 100));
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){ 
      int t=get_tile(g->g,x,y);
      SDL_FillRect(tile, &rect,get_tile_color(tile->format,t));
      SDL_Rect tilePos={100*x,100*y};
      
      if(t!=0){

	t=pow(2,t);
	int taille=sprintf(str,"%d",t);
	int size_police;
	if(taille<3)
	  size_police=0;
	else if(taille==3)
	  size_police=1;
	else if(taille==4)
	  size_police=2;
	else
	  size_police=3;
	SDL_Surface* s=TTF_RenderText_Solid( v->fonts[size_police], str, c );
	assert(s->w <= tile->w-10);//la taille du texte doit rentrer dans une tuile privée de sa marge
	assert(s->h <= tile->h-10);
	SDL_Rect tileRect={45 - (s->w)/2 , 45 - (s->h)/2 , 0,0};
	SDL_BlitSurface(s,NULL,tile,&tileRect);
	SDL_FreeSurface(s);
      }
      
      SDL_BlitSurface(tile,NULL,v->screen,&tilePos);
    }
  }
  sprintf(str,"score : %5ld",grid_score(g->g));
  SDL_Rect fpsPos={0,400};
  SDL_Surface *der=TTF_RenderText_Solid( v->fonts[2],str , c );
  SDL_BlitSurface(der,NULL,v->screen,&fpsPos);
  SDL_Flip(v->screen);


  SDL_FreeSurface(tile);
  SDL_FreeSurface(der);
}

void execute(game g){
  Uint32 time=SDL_GetTicks();
  g->fps=1000.f/((time-g->time));
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
  SDL_Quit();
  return EXIT_SUCCESS;
}
