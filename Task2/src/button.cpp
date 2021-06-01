#include "button.h";

using namespace std;

Button::Button(char* name, SDL_Renderer* renderer,int width,int height,char* path){
	//TTF_Init();
	label = name;
	s_width = width;
	s_height = height;
	
	SDL_Surface* textSurface;
	textSurface=IMG_Load(path);
	
	/*TTF_Font* font;
	font = TTF_OpenFont("./../batmfa.ttf",20);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font,label,{226,88,34,255});
	colors.push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface = TTF_RenderText_Solid(font,label,{255,255,255,255});
	colors.push_back(SDL_CreateTextureFromSurface(renderer,textSurface));*/
	
	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";
	}
	else{
		texture=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_FreeSurface(textSurface);
		/*texture = colors[cur_color];
		SDL_FreeSurface(textSurface);*/
	}
} 

void Button::set_cor(int x,int y,int w,int h){
	dest.x=x;
	dest.y=y;
	dest.w=w;
	dest.h=h;
}

void Button::set_rect(int x,int y,int w,int h){
	dest.x=x;
	dest.y=y;
	dest.w=w-x;
	dest.h=h-y;
}

bool Button::isInside(int a,int b){
	if (a>=(dest.x*s_width)/3700 and a<=(dest.x+dest.w)*s_width/3700 and b>=(dest.y*s_height)/2100 and b<=(dest.y+dest.h)*s_height/2100) {return true;}
	return false;
}


void Button::handle_event(int* state,SoundClass *m,bool music_on/*,SDL_Event e*/){
	/*if(e.type==SDL_MOUSEMOTION){
		int x_c = e.motion.x;
		int y_c = e.motion.y;
		if(isInside(x_c,y_c)){
			cur_color = 1;
			texture = colors[1];
		}
	}else{*/
		if(strcmp(label,"Exit")==0){
			if (music_on){
				m->PlaySound("button");
			}	
			*state=6;	
		}else if(strcmp(label,"Start")==0){
			if (music_on){
				m->PlaySound("button");
				m->PlaySound("start");
			}
			*state=0;	
		}else if(strcmp(label,"Options")==0){
			if(music_on){
				m->PlaySound("button");
			}
			*state=3;
		}else if(strcmp(label,"Pause")==0){
			if(music_on){
				m->PlaySound("button");
			}
			*state=2;
		}else if(strcmp(label,"Resume")==0){
			if(music_on){
				m->PlaySound("button");
			}
			*state=0;
		}else if(strcmp(label,"Play Again")==0){
			if(music_on){
				m->PlaySound("button");
			}
			*state=-2;
		}
	//}
}

void Button::render(SDL_Renderer *renderer){
	SDL_RenderCopy(renderer,texture,NULL,&dest);
}

/*void Button::set_original(){
	cur_color = 0;
	texture = colors[cur_color];
}*/

