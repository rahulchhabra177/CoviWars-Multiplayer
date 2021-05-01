#include "Texture.h";
#include "character.h";
using namespace std;
int temp=0;

Character::Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnem){
	texture=Texture::LoadT(path,localRenderer);
	x=init_x;
	y=init_y;
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
	isEnemy=isEnem;
}

void Character::updatePlayer(){
	y+=y_speed;
	x+=x_speed;
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
	cout<<x<<" "<<y<<"\n";
}

void Character::changeSpeed(SDL_Event e){
	if(!isEnemy){
		if(e.type==SDL_KEYDOWN){
			switch(e.key.keysym.sym){
				case SDLK_UP:{y_speed=-20;x_speed=0;break;}
				case SDLK_DOWN:{y_speed=20;x_speed=0;break;}
				case SDLK_RIGHT:{y_speed=0;x_speed=20;break;}
				case SDLK_LEFT:{y_speed=0;x_speed=-20;break;}
			}
		}
	}
}


void Character::render(SDL_Renderer* renderer){
	SDL_RenderCopy(renderer,texture,NULL,&dstr);
}

bool Character::collide(Character * obj){
	int x1 = x + width;
	int y1 = y + height;
	int x2 = obj->x + obj->width;
	int y2 = obj->y + obj->height;
	if(obj->x>=x && obj->x<=x1 && obj->y>=y && obj->y<=y1){
		return true;
	}else if(x2>=x && x2<=x1 && y2>=y && y2<=y1){
		return true;
	}else{
		return false;
	}
}


