#ifndef ENEMY_H

#define ENEMY_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sounds.h"

class Enemy{

	public:
		
		int x,y,height=60,width=60;
		int speed = 20;
		int x_speed = 20;
		int y_speed = 0;
		int count = 0;
		int cur_texture = 0;
		int rot_speed = 50;
		string name="enemy";
		SDL_Rect dstr,src;
		Enemy(SDL_Renderer* localRenderer,int init_x,int init_y);
		void changeSpeed(SDL_Event e);
		void updateEnemy();
		void render(SDL_Renderer* renderer);
		SDL_Texture* texture[8]={NULL};

};

#endif
