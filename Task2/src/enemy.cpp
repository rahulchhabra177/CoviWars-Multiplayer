#include "Texture.h";
#include "enemy.h";
using namespace std;
bool enemy_debug=true;

Enemy::Enemy(SDL_Renderer* localRenderer,int init_x,int init_y,int screen_width){
	if (enemy_debug)cout<<"Enemy.cpp::Enemy\n";

	for (int i=0;i<8;i++){
		string path="./../assets/corona"+to_string(i)+".xcf";
		char* a=&path[0];
		texture[i]=Texture::LoadT(a,localRenderer);
	}
	
	active = true;
	x=init_x;
	y=init_y;
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
}

void Enemy::updateEnemy(){
	if (enemy_debug)cout<<"Enemy.cpp::updatePlayer\n";
	y+=y_speed;
	x+=x_speed;
	dstr.x=x;
	dstr.y=y;
}



void Enemy::render(SDL_Renderer* renderer){
	if (enemy_debug)cout<<"Enemy.cpp::render\n";
	SDL_RenderCopy(renderer,texture[cur_texture],NULL,&dstr);
	count=(count+1)%rot_speed;
	if (count==0){
		cur_texture=(cur_texture+1)%8;
	}
}

string Enemy::getEnemyState(){
	string x1=to_string(x),y1=to_string(y);
	while (x1.size()<4){
		x1="0"+x1;
	}
	while (y1.size()<4){
		y1="0"+y1;
	}
	return x1+y1;
}

void Enemy::set_x_y(int x_ax,int y_ax){
	x=x_ax;
	y=y_ax;
	dstr.x=x;
	dstr.y=y;
}
