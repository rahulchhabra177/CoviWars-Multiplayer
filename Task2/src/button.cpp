#include "button.h";

using namespace std;
bool button_debug=true;

Button::Button(char* name, SDL_Renderer* renderer,int width,int height){
	if(button_debug)cout<<"button.cpp::Button\n";
	
	TTF_Init();
	label = name;
	s_height=height;
	s_width=width;
	
	TTF_Font * font;
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,{226,88,34,255});
	colors.push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface=TTF_RenderText_Solid(font,label,{255,255,255,255});
	colors.push_back(SDL_CreateTextureFromSurface(renderer,textSurface));

	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";		//To manage exit condition
	}
	else{
		texture=colors[cur_color];
		SDL_FreeSurface(textSurface);
	}
} 
void Button::set_cor(int x,int y,int w,int h){
	if (button_debug)cout<<"button.cpp::set_cor\n";
	dest.x=x;
	dest.y=y;
	dest.w=w;
	dest.h=h;
}

void Button::set_rect(int x,int y,int w,int h){
	if (button_debug)cout<<"button.cpp::set_rect\n";
	dest.x=x;
	dest.y=y;
	dest.w=w-x;
	dest.h=h-y;
}

bool Button::isInside(int a,int b){
	if (button_debug)cout<<"button.cpp::isInside\n";
	if (3700*a>=(dest.x*s_width) && 3700*a<=((dest.x+dest.w)*s_width) && 2100*b>=(dest.y*s_height) && b*2100<=((dest.y+dest.h)*s_height)){return true;}
	return false;
}

void Button::handle_event(int* state,SoundClass *m,bool music_on,SDL_Event e){
	if (e.type==SDL_MOUSEMOTION){
		int x_c = e.motion.x;
        	int y_c = e.motion.y;
		if (cur_color!=1){
			cur_color=1;
			texture=colors[1];
			dest.x-=10;
			dest.y-=10;
			dest.h+=20;
			dest.w+=20;
		}		
	}else if(strcmp(label,"Exit")==0){
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
	}else if(strcmp(label,"Sounds")==0){
		if (music_on){
			m->PlaySound("button");
			m->music_on=false;
		}
	}else if(strcmp(label,"Options")==0){
		if(music_on){
			m->PlaySound("button");
		}
		// *state=3;
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
}

void Button::render(SDL_Renderer *renderer){
	if (button_debug)cout<<"button.cpp::render\n";
	SDL_RenderCopy(renderer,texture,NULL,&dest);
}

void Button::set_original(){
	if (cur_color!=0){
		dest.x+=10;
		dest.y+=10;
		dest.h-=20;
		dest.w-=20;
	}
	cur_color=0;
	texture=colors[cur_color];
}