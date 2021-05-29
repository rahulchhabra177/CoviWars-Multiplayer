#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "sounds.h"

class Enemy{

public:
	int x,y,height=40,width=40;
	int speed = 20;
	int x_speed = 20;
	int y_speed = 0;
	int count = 0,cur_texture=0;
	int rot_speed=50;
	string name="player";
	SDL_Rect dstr,src;
	Enemy(SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnemy);
	void changeSpeed(SDL_Event e);
	void updatePlayer();
	void render(SDL_Renderer* renderer);
	SDL_Texture* texture[8]={NULL};
	bool isEnemy;
	bool collide(Enemy * enemy,SoundClass* m,bool music_on);
};
