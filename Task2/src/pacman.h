#include "game.hpp"



class pacman{

public:
	int x,y,height=64,width=64;
	SDL_Rect dstr;
	pacman(char * path,SDL_Renderer* rendere,int init_x,int init_y,bool isenemy);
	void update();
	void render();
	SDL_Texture* character=NULL;
	SDL_Renderer* renderer=NULL;
	bool isenemy;	
};