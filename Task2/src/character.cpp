#include "Texture.h";
#include "character.h";

using namespace std;
bool debug_character=false;

Character::Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnemy){
	if (debug_character)cout<<"character.cpp::Character\n";
	texture=Texture::LoadT(path,localRenderer);
	x=init_x;
	y=init_y;
	width =80;
	height = width;
	speed = 1;
	x_speed = speed;
	y_speed = 0;
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
	isEnemy=isEnemy;
	src.x=0;
	src.y=350;
	src.h=350;
	src.w=500;
}

void Character::updatePlayer(){
	if (debug_character)cout<<"character.cpp::updatePlayer\n";
	if (y+y_speed>0 && y+y_speed<700 && x+x_speed>0 && x+x_speed<1200){
	y+=y_speed;
	x+=x_speed;
	dstr.x=x;
	dstr.y=y;
}
	// cout<<"Player Coordinates::"<<x<<" "<<y<<"\n";
}

void Character::changeSpeed(SDL_Event e){
	if (debug_character)cout<<"character.cpp::changeSpeed\n";
	if(!isEnemy){
		if(e.type==SDL_KEYDOWN){
			switch(e.key.keysym.sym){
				case SDLK_UP:{y_speed=(-1)*speed;x_speed=0;break;}
				case SDLK_DOWN:{y_speed=speed;x_speed=0;break;}
				case SDLK_RIGHT:{y_speed=0;x_speed=speed;break;}
				case SDLK_LEFT:{y_speed=0;x_speed=(-1)*speed;break;}
			}
		}
	}
}


void Character::render(SDL_Renderer* renderer){
	if (debug_character)cout<<"character.cpp::render\n";
	
	SDL_RenderCopy(renderer,texture,NULL,&dstr);
}

bool Character::collide(Enemy * obj,SoundClass *m,bool music_on){
	if (debug_character)cout<<"character.cpp::collide\n";
	return false;
	int x1 = x + width;
	int y1 = y + height;
	int x2 = obj->x + obj->width;
	int y2 = obj->y + obj->height;
	if(obj->x>=x && obj->x<=x1 && obj->y>=y && obj->y<=y1){
		m->PlaySound("collision");
		return true;
	}else if(x2>=x && x2<=x1 && y2>=y && y2<=y1){
		m->PlaySound("collision");
		return true;
	}else{
		return false;
	}
}


