#include "Texture.h";
#include "character.h";

using namespace std;
bool character_debug=true;

Character::Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isForeign){
	if (character_debug)cout<<"character.cpp::Character\n";
	for (int i=0;i<4;i++){
		for (int j=0;j<8;j++){
			string path="./../assets/pac"+to_string(i)+to_string(j%2+1)+".xcf";
			char* a=&path[0];
			texture[i][j]=Texture::LoadT(a,localRenderer);
		}
	}
	
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

void Character::updatePlayer(network*nmanager,bool isForeigner){
	if (character_debug)cout<<"character.cpp::updatePlayer\n";
	if (!isForeigner){
		y+=y_speed;
		x+=x_speed;
		dstr.x=x;
		dstr.y=y;
	}
}

void Character::changeSpeed(SDL_Event e,network*nmanager){
	if (character_debug)cout<<"character.cpp::changeSpeed\n";
	if(e.type==SDL_KEYDOWN){
		switch(e.key.keysym.sym){
			case SDLK_UP:{y_speed=(-1)*speed;x_speed=0;cur_dir=1;if (nmanager->connected){nmanager->send("$1");}break;}
			case SDLK_DOWN:{y_speed=speed;x_speed=0;cur_dir=3;if (nmanager->connected){nmanager->send("$2");}break;}
			case SDLK_RIGHT:{y_speed=0;x_speed=speed;cur_dir=0;if (nmanager->connected){nmanager->send("$3");}break;}
			case SDLK_LEFT:{y_speed=0;x_speed=(-1)*speed;cur_dir=2;if (nmanager->connected){nmanager->send("$4");}break;}
			default:{if (nmanager->connected){nmanager->send("$0");}break;}
		}
	}else{
		if (nmanager->connected){nmanager->send("$0");}
	}
}


void Character::render(SDL_Renderer* renderer){
	if (character_debug)cout<<"character.cpp::render\n";
	SDL_RenderCopy(renderer,texture[cur_dir][cur_texture],NULL,&dstr);
	count=(count+1)%rot_speed;
	if (count==0){
		cur_texture=(cur_texture+1)%8;
	}
}

bool Character::collide(Enemy * obj,SoundClass *m,bool music_on){
	if (character_debug)cout<<"character.cpp::collide\n";
	int x1 = x + width;
	int y1 = y + height;
	if(obj==nullptr){
		exit(1);
	}
	int x2 = obj->x + obj->width;
	int y2 = obj->y + obj->height;
	if(obj->x<=x && x<=x2 && obj->y<=y && y<=y2){
		m->PlaySound("collision");
		return true;
	}else if(obj->x<=x && x<=x2 && obj->y<=y1 && y1<=y2){
		m->PlaySound("collision");
		return true;
	}else if(obj->x<=x1 && x1<=x2 && obj->y<=y && y<=y2){
		m->PlaySound("collision");
		return true;
	}else if(obj->x<=x1 && x1<=x2 && obj->y<=y1 && y1<=y2){
		m->PlaySound("collision");
		return true;
	}else{
		return false;
	}
}

void Character::set_x_y(int x_ax,int y_ax){
	x=x_ax;
	y=y_ax;
	dstr.x=x;
	dstr.y=y;
}

void Character::set_speed(int a){
	if (a==1){
		y_speed=(-1)*speed;x_speed=0;
	}
	else if (a==2){
		y_speed=speed;x_speed=0;
	}
	else if (a==3){
		y_speed=0;x_speed=speed;
	}
	else if (a==4){
		y_speed=0;x_speed=(-1)*speed;
	}

}



string Character::getPlayerState(){
	string x1=to_string(x),y1=to_string(y);
	while (x1.size()<4){
		x1="0"+x1;
	}
	while (y1.size()<4){
		y1="0"+y1;
	}
	return x1+y1;
}