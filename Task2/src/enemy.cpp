#include "Texture.h";
#include "enemy.h";
using namespace std;
bool debug_Enemy=false;

Enemy::Enemy(SDL_Renderer* localRenderer,int init_x,int init_y,bool isEnemy){
	if (debug_Enemy)cout<<"Enemy.cpp::Enemy\n";
// 	for(int i=0;i<8;i++){
// 	char c=(char)('0'+i);
// 	cout<<1;
// 	char * path="./../assets/coronai.xcf";
// 	cout<<2;
// 	path[18]=c;
// 	cout<<path<<"\n";

// 	texture[i]=Texture::LoadT(path,localRenderer);
// }
	texture[0]=Texture::LoadT("./../assets/corona0.xcf",localRenderer);
	texture[1]=Texture::LoadT("./../assets/corona1.xcf",localRenderer);
	texture[2]=Texture::LoadT("./../assets/corona2.xcf",localRenderer);
	texture[3]=Texture::LoadT("./../assets/corona3.xcf",localRenderer);
	texture[4]=Texture::LoadT("./../assets/corona4.xcf",localRenderer);
	texture[5]=Texture::LoadT("./../assets/corona5.xcf",localRenderer);
	texture[6]=Texture::LoadT("./../assets/corona6.xcf",localRenderer);
	texture[7]=Texture::LoadT("./../assets/corona7.xcf",localRenderer);
	
	x=init_x;
	y=init_y;
	width =40;
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

void Enemy::updatePlayer(){
	if (debug_Enemy)cout<<"Enemy.cpp::updatePlayer\n";
	if (y+y_speed>0 && y+y_speed<700 && x+x_speed>0 && x+x_speed<1200){
	y+=y_speed;
	x+=x_speed;
	dstr.x=x;
	dstr.y=y;
}
	// cout<<"Player Coordinates::"<<x<<" "<<y<<"\n";
}

void Enemy::changeSpeed(SDL_Event e){
	if (debug_Enemy)cout<<"Enemy.cpp::changeSpeed\n";
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


void Enemy::render(SDL_Renderer* renderer){
	if (debug_Enemy)cout<<"Enemy.cpp::render\n";
	// cout<<cur_texture<<":cur_texture\n";

	SDL_RenderCopy(renderer,texture[cur_texture],NULL,&dstr);
	count=(count+1)%rot_speed;
	if (count==0){
	cur_texture=(cur_texture+1)%8;
}
}

bool Enemy::collide(Enemy * obj,SoundClass *m,bool music_on){
	if (debug_Enemy)cout<<"Enemy.cpp::collide\n";
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


