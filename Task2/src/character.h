#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "sounds.h"
#include "enemy.h";

class Character{

public:
	int x,y,height=100,width=100;
	int speed = 1;
	int x_speed = 1;
	int y_speed = 0;
		int rot_speed=50;

	int count = 0,cur_texture=0,cur_dir=0;
	int score=0;
	char* name="player";
	SDL_Rect dstr,src;
	Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnemy);
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
