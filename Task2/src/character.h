#ifndef CHR_H

#define CHR_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "sounds.h"
#include "enemy.h";

class Character{

public:
	int x,y,height=80,width=80;
	int speed = 10;
	int x_speed = 10;
	int y_speed = 0;
	int rot_speed=10;

	int count = 0,cur_texture=0,cur_dir=0;
	int score=0;
	char* name="player";
	bool isForeigner=false;
	SDL_Rect dstr,src;
	Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isForeign,int screen_width);
	void changeSpeed(SDL_Event e,network*nmanager);
	void updatePlayer(network*nmanager,bool isForeigner);
	void render(SDL_Renderer* renderer);
	SDL_Texture* texture[4][8]={NULL};
	bool isEnemy=false;
	bool collide(Enemy * enemy,SoundClass* m,bool music_on);
	string getPlayerState();
	void set_x_y(int x_ax,int y_ax);
	void set_speed(int a);
};
#endif