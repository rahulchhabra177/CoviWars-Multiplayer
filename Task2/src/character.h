#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "button.h";

class Character{

public:
	int x,y,height=20,width=20;
	int x_speed = 20;
	int y_speed = 0;
	int count = 0;
	SDL_Rect dstr;
	Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnemy);
	void changeSpeed(SDL_Event e);
	void updatePlayer();
	void render(SDL_Renderer* renderer);
	SDL_Texture* texture=NULL;
	bool isEnemy;
	bool collide(Character * enemy,SoundClass* m,bool music_on);
};
