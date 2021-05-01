#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>

class Character{

public:
	int x,y,height=300,width=300;
	int speed = 20;
	int count = 0;
	SDL_Rect dstr;
	Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnemy);
	void update(SDL_Event e);
	void render();
	SDL_Texture* texture=NULL;
	SDL_Renderer* renderer=NULL;
	bool isEnemy;	
};
