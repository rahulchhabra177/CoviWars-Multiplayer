#ifndef ENEMY_H

#define ENEMY_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "./../sound/sounds.h"

class Enemy{

public:
	int x,y,height=100,width=100;
	int speed = 5;
	int x_speed = 5;
	int y_speed = 0;
	int count = 0,cur_texture=0;
	int rot_speed=20;
	int type=-1;
	int explodeCounter=0;
	bool active=false;
	string name="player";
	SDL_Rect dstr,src;
	Enemy(SDL_Renderer* localRenderer,int init_x,int init_y,int screen_width,vector<SDL_Texture*> texture_e);
	Enemy(SDL_Renderer* localRenderer,int enemyType,int init_x,int init_y,int screen_width,vector<SDL_Texture*> texture_e);
	void updateEnemy();
	void render(SDL_Renderer* renderer);
	vector<SDL_Texture*> texture;
	string getEnemyState();
	void set_x_y(int ax,int ay);
};
#endif
