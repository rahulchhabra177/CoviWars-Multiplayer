#include "button.h";

using namespace std;


SDL_Texture* Button::LoadButtonFromImage(char * path,SDL_Renderer* renderer,char* label_1){
	label=label_1;
	SDL_Surface* tmp;
	tmp=IMG_Load(path);
	SDL_Texture* returng=NULL;
	if (tmp==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";
	}
	else{
		returng=SDL_CreateTextureFromSurface(renderer,tmp);
		SDL_FreeSurface(tmp);
	}
	return returng;
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


void Button::handle_event(SDL_Event event,int* state){
	switch (event.type){
		case SDL_MOUSEBUTTONDOWN:
			int a,b;
			SDL_GetMouseState( &a, &b );
			if (isInside(a,b)){
				cout<<"State change\n";
				*state=1;
			}
			break;
		default:
			break;		
	}
}

void Button::render(SDL_Renderer *renderer,SDL_Texture *tect){
	SDL_RenderCopy(renderer,tect,NULL,&dest);
}

