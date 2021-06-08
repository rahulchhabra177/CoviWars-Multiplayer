#ifndef ENEMY_H

#define ENEMY_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "sounds.h"

class Enemy{

public:
	int x,y,height=100,width=100;
	int speed = 1;
	int x_speed = 1;
	int y_speed = 0;
	int count = 0,cur_texture=0;
	int rot_speed=10;
	string name="player";
	SDL_Rect dstr,src;
	Enemy(SDL_Renderer* localRenderer,int init_x,int init_y,int screen_width);
	void updateEnemy();
	void render(SDL_Renderer* renderer);
	SDL_Texture* texture[8]={NULL};
	string getEnemyState();
	void set_x_y(int ax,int ay);
};
#endif
