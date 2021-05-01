#include "Texture.h";
#include "character.h";
using namespace std;
int temp=0;

Character::Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnem){
	texture=Texture::LoadT(path,localRenderer);
	renderer=localRenderer;
	x=init_x;
	y=init_y;
	isEnemy=isEnem;
}

void Character::update(SDL_Event e){
	if(!isEnemy){
		if(e.type==SDL_KEYDOWN){
			switch(e.key.keysym.sym){
				case SDLK_UP:{y=y-speed;break;}
				case SDLK_DOWN:{y=y+speed;break;}
				case SDLK_RIGHT:{x=x+speed;break;}
				case SDLK_LEFT:{x=x-speed;break;}
			}
		}
	}
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
}


void Character::render(){
	SDL_RenderCopy(renderer,texture,NULL,&dstr);
}

