#include "Texture.h";
#include "character.h";

using namespace std;
bool character_debug=true;

Character::Character(char * path,SDL_Renderer* localRenderer,int init_x,int init_y,bool isForeign){
	if (character_debug)cout<<"character.cpp::Character\n";
	for (int i=0;i<4;i++){
		for (int j=0;j<8;j++){
		string path="./../assets/pac"+to_string(i)+to_string(j%2+1)+".xcf";
		// cout<<path<<"\n";
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
		// if (count%8==0){
			y+=y_speed;
			x+=x_speed;
			dstr.x=x;
			dstr.y=y;
// }

}

// else{

// 	int debug=0;
// 	string temp="";
// 	while (debug<100 && temp==""){
// 		temp=nmanager->recieve(2);
// 		debug++;
// 		// cout<<"debug\n";
// 	}
// 	string s=temp;
// 	// cout<<s<<"\n\n";
// 	if (s=="" || s=="$0"){
// 		if (y+y_speed>0 && y+y_speed<700 && x+x_speed>0 && x+x_speed<1200){
// 	y+=y_speed;
// 	x+=x_speed;
// 	dstr.x=x;
// 	dstr.y=y;
	
// }
// 	cout<<"Testing irrelevant values::"<<s<<"\n";
// 	return;
// }
// 	if (s[0]=='$'){
// 		cout<<"Errorcuser:"<<s<<"\n";
// 	set_speed(stoi(s.substr(1,1)));
// }


// }
	// cout<<"Player Coordinates::"<<x<<" "<<y<<"\n";
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
	}
	else{
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
	// return false;
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
// cout<<x1+y1<<"\n";
	return x1+y1;


}