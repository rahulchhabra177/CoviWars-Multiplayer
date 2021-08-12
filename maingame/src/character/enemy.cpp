#include "./../texture/Texture.h";
#include "enemy.h";
using namespace std;
bool enemy_debug=false;

Enemy::Enemy(SDL_Renderer* localRenderer,int init_x,int init_y,int screen_width,vector<SDL_Texture*> texture_e){
	if (enemy_debug)cout<<"Enemy.cpp::Enemy\n";

	//Multiple textures(here 8) of the enemy for animation effect
	for (int i=0;i<8;i++){
		texture.push_back(texture_e[i]);
	}
	
	//This checks whether this instance of the enemy is in play or not.
	//A particular enemy may get out of play if it is eaten by the pacman.
	active = true;
	
	//Initial parameters of the enemy
	x=init_x;
	y=init_y;
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
}

//Alternative enemy contructor
Enemy::Enemy(SDL_Renderer* localRenderer,int enemyType,int init_x,int init_y,int screen_width,vector<SDL_Texture*> texture_e){
	if (enemy_debug)cout<<"Enemy.cpp::Enemy\n";

	//Multiple textures(here 8) of the enemy for animation effect
	for (int i=0;i<8;i++){
		texture.push_back(texture_e[i]);
	}
	
	//This checks whether this instance of the enemy is in play or not.
	//A particular enemy may get out of play if it is eaten by the pacman.
	active = true;
	type = enemyType;
	
	//Initial parameters of the enemy
	x=init_x;
	y=init_y;
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
}

//For updating the position of the enemy on the screen
void Enemy::updateEnemy(){
	if (enemy_debug)cout<<"Enemy.cpp::updatePlayer\n";
	if(active){
		y+=y_speed;
		x+=x_speed;
		dstr.x=x;
		dstr.y=y;
		if(type==3 || type==0){
			explodeCounter++;
		}
	}
}

//To render the enemy on the screen
void Enemy::render(SDL_Renderer* renderer){
	if (enemy_debug)cout<<"Enemy.cpp::render\n";
	SDL_RenderCopy(renderer,texture[cur_texture],NULL,&dstr);
	
	//The enemy is animated by rotating the textures after a fixed number 
	//of frames, known as the rotation speed(rot_speed)
	count=(count+1)%rot_speed;
	if (count==0){
		cur_texture=(cur_texture+1)%8;
	}
}

//To fetch the current state of the enemy to send it over the network. We have 
//designed out sockets so that the enemies are initialised and updated by the 
//server and their positions at every moment are sent to the clients using the 
//network
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


//For setting the position of non-local enemies
void Enemy::set_x_y(int x_ax,int y_ax){
	x=x_ax;
	y=y_ax;
	dstr.x=x;
	dstr.y=y;
}