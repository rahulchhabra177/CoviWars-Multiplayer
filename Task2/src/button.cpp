#include "button.h";

using namespace std;

Button::Button(char* name, SDL_Renderer* renderer, char* path){
	label = name;
	SDL_Surface* tmp;
	tmp=IMG_Load(path);
	if (tmp==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";		//To manage exit condition
	}
	else{
		texture=SDL_CreateTextureFromSurface(renderer,tmp);
		SDL_FreeSurface(tmp);
	}
} 

void Button::set_cor(int a,int b,int q,int w){
	dest.x=a;
	dest.y=b;
	dest.h=q;
	dest.w=w;
}


bool Button::isInside(int a,int b){
	if (a>=dest.x and a<=dest.x+dest.w and b>=dest.y and b<=dest.y+dest.h){return true;}
	return false;
}


void Button::handle_event(int* state){
	if(strcmp(label,"Exit")==0){
		*state=4;	
	}else if(strcmp(label,"Start")==0){
		*state=0;
	}else if(strcmp(label,"Options")==0){
		*state=3;
	}else if(strcmp(label,"Pause")==0){
		*state=2;
	}else if(strcmp(label,"Resume")==0){
		*state=0;
	}
}

void Button::render(SDL_Renderer *renderer){
	SDL_RenderCopy(renderer,texture,NULL,&dest);
}

