#ifndef CHR_H

#define CHR_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "./../sound/sounds.h"
#include "enemy.h";

class Character{

public:

	//Size/speed pf pacman
	int x,y,height=100,width=100;
	int speed = 10;
	int x_speed = 10;
	int y_speed = 0;
	int kx_speed = -10;
	int ky_speed = 0;
	int rot_speed=10;
	int lastKey = 0;

	//Various counters for different effects/states of the pacman
	int count = 0,cur_texture=0,cur_dir=0;
	int score=0;
	int counter=0;
	int hazardCounter=0;
	int freezeCounter=0;
	int knockbackCounter=0;

	//Various states of pacman
	bool inQuarantine=false;
	bool isMasked=false;
	bool isInvincible=false;
	bool isVaccinated=false;
	bool isForeigner=false;
	bool isfireball = false;
	bool freeze = false;
	bool knockback = false;

	string name="player";
	SDL_Rect dstr,src;
	Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isForeign,int screen_width,SDL_Texture* texture_p[4][8],SDL_Texture* texture_pv[4][8],SDL_Texture* texture_pa[4][8]);
	Character(SDL_Renderer* localRenderer,int init_x,int init_y,int speedx,int speedy,SDL_Texture* texture_p[]);
	void updatePlayer(bool isForeigner);
	void render(SDL_Renderer* renderer);
	SDL_Texture* texture[4][8]={NULL};
	SDL_Texture* texture_v[4][8]={NULL};
	SDL_Texture* texture_a[4][8]={NULL};
	SDL_Texture* texture_ball[2]={NULL};
	bool isEnemy=false;
	bool collide(Enemy * enemy,SoundClass* m);
	string getPlayerState();
	void set_x_y(int x_ax,int y_ax);
	void set_speed(int a);
	void updateCounter(int lvl);
};
#endif