#include "./../texture/Texture.h";
#include "./../character/coviwars.h";

using namespace std;
bool character_debug=false;

Character::Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isForeign,int screen_width,SDL_Texture* texture_p[4][8],SDL_Texture* texture_pv[4][8],SDL_Texture* texture_pa[4][8]){
	
	if (character_debug)cout<<"character.cpp::Character\n";
	isfireball=false;
	//Initialising textures for our main character(pacman), one for each 
	//direction in which it will be moving. We have also animated the pacman
	//so each direction will also have several textures(here 8), for a total
	//of 32 textures. 
	for (int i=0;i<4;i++){
		for (int j=0;j<8;j++){
			
			texture[i][j]=texture_p[i][j];
		}
	}
	for (int i=0;i<4;i++){
		for (int j=0;j<8;j++){
			
			texture_v[i][j]=texture_pv[i][j];
		}
	}
	for (int i=0;i<4;i++){
		for (int j=0;j<8;j++){
			
			texture_a[i][j]=texture_pa[i][j];
		}
	}
	//Initial position and size of the pacman
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
	isForeigner=isForeign;
}



Character::Character(SDL_Renderer* localRenderer,int init_x,int init_y,int speedx,int speedy,SDL_Texture* texture_p[]){
	
	if (character_debug)cout<<"character.cpp::Character\n";
	isfireball=true;
	isVaccinated=true;
	texture_ball[0]=texture_p[0];
	texture_ball[1]=texture_p[1];
	
	x=init_x;
	y=init_y;

	dstr.h=height;
	dstr.w=width;
	dstr.x=x+75;
	dstr.y=y+75;
	dstr.h=50;
	dstr.w=50;
	src.x=0;
	src.y=350;
	src.h=350;
	src.w=500;
	x_speed=speedx;
	y_speed=speedy;
	isForeigner=false;

}



//Updating the pacman's position with time depending upon different constraints in the game
void Character::updatePlayer(bool isForeigner){
	if (character_debug)cout<<"character.cpp::updatePlayer\n";
	
	//The boolean isForeigner checks whether the current character actually
	//belongs to the current instance of the game, i.e. in multiplayer mode,
	//the other pacman(controlled by the opponent) will not be in control 
	//by the current player, so that character's position should not be 
	//updated in current instance of the game.
	if (!isForeigner){
		if (isfireball){
			y+=y_speed;
			x+=x_speed;
			dstr.x=x+25;
			dstr.y=y+25;
		}else{
			if(freeze){
				if(freezeCounter==60*3){
					freeze=false;
					freezeCounter=0;
				}else{
					freezeCounter++;
				}
			}else{
				if(knockback){
					if(knockbackCounter==60*3){
						knockback=false;
						knockbackCounter=0;
						x_speed = (-1)*x_speed/2;
						y_speed = (-1)*y_speed/2;     
					}else{
						if(knockbackCounter==0){
							x_speed = (-2)*x_speed;
							y_speed = (-2)*y_speed;
						}
						knockbackCounter++;
					}
				}
				y+=y_speed;
				x+=x_speed;
				dstr.x=x;
				dstr.y=y;
			}
		}
	}
}

//To render the pacman on the screen
void Character::render(SDL_Renderer* renderer){
	if (character_debug)cout<<"Character.cpp::render:"<<cur_dir<<":"<<cur_texture<<"\n";
	if (isfireball){
		SDL_RenderCopy(renderer,texture_ball[cur_texture%2],NULL,&dstr);
		cur_texture++;
		if (cur_texture==200){
			cur_texture=0;
		}
		return;
	}
	if (isVaccinated){
		SDL_RenderCopy(renderer,texture_v[cur_dir][cur_texture],NULL,&dstr);	
	}
	else if (isInvincible){
		SDL_RenderCopy(renderer,texture_a[cur_dir][cur_texture],NULL,&dstr);	
		
	}
	else{
		SDL_RenderCopy(renderer,texture[cur_dir][cur_texture],NULL,&dstr);
	}
	//The animation of the pacman is implemented here. For a particular
	//direction, the pacman will change its texture after some fixed numbr 
	//of frames, denoted by rotation speed (rot_speed).
	count=(count+1)%rot_speed;
	if (count==0){
		cur_texture=(cur_texture+1)%8;
	}
	if (character_debug)cout<<"character.cpp::render:"<<cur_dir<<":"<<cur_texture<<"\n";

}

//To check collision between pacman and an enemy
bool Character::collide(Enemy * obj,SoundClass *m){
	if (character_debug)cout<<"character.cpp::collide\n";
	
	//Pacman's constraints
	int x1 = x + width;
	int y1 = y + height;
	
	//Enemy's constraints
	if(obj==nullptr){
		exit(1);
	}
	int x2 = obj->x + obj->width;
	int y2 = obj->y + obj->height;
	
	//The collision checking is done by simply comparing the constraints of 
	//the bounding boxes of pacman and the enemy. If both the boxes overlap
	//from any direction, then collision has occured.
	if(obj->x<=x && x<=x2 && obj->y<=y && y<=y2){
		return true;
	}else if(obj->x<=x && x<=x2 && obj->y<=y1 && y1<=y2){
		return true;
	}else if(obj->x<=x1 && x1<=x2 && obj->y<=y && y<=y2){
		return true;
	}else if(obj->x<=x1 && x1<=x2 && obj->y<=y1 && y1<=y2){
		return true;
	}else{
		return false;
	}
}

//To set the position of the character, when the co-ordinates are provided 
//externally. This is particularly useful in multiplayer mode, for setting the 
//position of the non-local pacman.
void Character::set_x_y(int x_ax,int y_ax){
	x=x_ax;
	y=y_ax;
	dstr.x=x;
	dstr.y=y;
}

//To set the speed of the non-local pacman, for use in multiplayer mode, similar
//to the above function.
void Character::set_speed(int a){
	if (a==1){
		y_speed=(-1)*speed;x_speed=0;
		cur_dir=1;
	}
	else if (a==2){
		y_speed=speed;x_speed=0;
		cur_dir=3;
	}
	else if (a==3){
		y_speed=0;
		x_speed=speed;
		cur_dir=0;
	}
	else if (a==4){
		y_speed=0;x_speed=(-1)*speed;
		cur_dir=2;
	}
}

//For updating the time counter for various powerups 
void Character::updateCounter(int lvl){
	
	//Normal update
	if(isVaccinated || isInvincible){
		counter++;
	}
	
	//If the counter reaches a particular upper limit, for a given level,
	//then the power-up runs out.
	if(counter==(7-lvl)*60){
		counter=0;
		isInvincible=false;
		isVaccinated=false;
	}
}

//Obtaining the current state of the player in string form to send over the 
//network, for updating the position and speed of its non-local copy on another
//instance of the game.
string Character::getPlayerState(){
	string x1=to_string(x),y1=to_string(y);
	int k;
	if(x_speed!=0){
		if(x_speed>0){
			k=3;
		}else{
			k=4;
		}
	}else{
		if(y_speed>0){
			k=2;
		}else{
			k=1;
		}
	}
	while (x1.size()<4){
		x1="0"+x1;
	}
	while (y1.size()<4){
		y1="0"+y1;
	}
	return to_string(k)+x1+y1;
}