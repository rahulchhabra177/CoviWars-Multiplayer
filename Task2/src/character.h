#ifndef CHARACTER_H

#define CHARACTER_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "sounds.h"
#include "enemy.h"

class Character{

public:
	int x,y,height=60,width=60;
	int speed = 10;
	int x_speed = 10;
	int y_speed = 0;
	SDL_Rect dstr,src;
	int count=0;
	int score=0;
	int cur_texture=0;
	char* name = "Player";
	Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y);
	void changeSpeed(SDL_Event e);
	void updatePlayer();
	void render(SDL_Renderer* renderer);
	SDL_Texture* texture=NULL;
	bool collide(Enemy * enemy,SoundClass* m,bool music_on);
	
};
#endif
