#include "Texture.h";
#include "enemy.h";
using namespace std;

Enemy::Enemy(SDL_Renderer* localRenderer,int init_x,int init_y){

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
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
	src.x=0;
	src.y=350;
	src.h=350;
	src.w=500;
}

void Enemy::updateEnemy(){
	y+=y_speed;
	x+=x_speed;
	dstr.x=x;
	dstr.y=y;
}

void Enemy::render(SDL_Renderer* renderer){
	SDL_RenderCopy(renderer,texture[cur_texture],NULL,&dstr);
	count = (count+1)%rot_speed;
	if(count==0){
		cur_texture = (cur_texture+1)%8;
	}
}
