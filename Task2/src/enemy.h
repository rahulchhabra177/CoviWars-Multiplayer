#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "sounds.h"

class Enemy{

public:
	int x,y,height=100,width=100;
	int speed = 2;
	int x_speed = 2;
	int y_speed = 0;
	int count = 0,cur_texture=0;
	int rot_speed=50;
	string name="player";
	SDL_Rect dstr,src;
	Enemy(SDL_Renderer* localRenderer,int init_x,int init_y);
	void updateEnemy();
	void render(SDL_Renderer* renderer);
	SDL_Texture* texture[8]={NULL};
};
