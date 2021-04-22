#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>

class pacman{

public:
	int x,y,height=40,width=40;
	SDL_Rect dstr;
	pacman(char * path,SDL_Renderer* rendere,int init_x,int init_y,bool isenemy);
	void update();
	void render();
	SDL_Texture* character=NULL;
	SDL_Renderer* renderer=NULL;
	bool isenemy;	
};
