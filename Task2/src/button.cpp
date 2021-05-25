#include "button.h";

using namespace std;
bool debug_button=false;
Button::Button(char* name, SDL_Renderer* renderer){
	if (debug_button)cout<<"button.cpp::Button\n";
	TTF_Init();
	label = name;
	TTF_Font * font;//=new TTFont();
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	// SDL_Color color={0,255,0,255};
	// SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,color);
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
void Button::set_cor(int a,int b,int q,int w){
	if (debug_button)cout<<"button.cpp::set_cor\n";
	dest.x=a;
	dest.y=b;
	dest.w=q;
	dest.h=w;
}

void Button::set_rect(int a,int b,int q,int w){
	if (debug_button)cout<<"button.cpp::set_rect\n";
	dest.x=a;
	dest.y=b;
	dest.w=q-a;
	dest.h=w-b;
}

bool Button::isInside(int a,int b){
	if (debug_button)cout<<"button.cpp::isInside\n";
	if (a>=dest.x and a<=dest.x+dest.w and b>=dest.y and b<=dest.y+dest.h){return true;}
	return false;
}


void Button::handle_event(int* state,SoundClass *m,bool music_on,SDL_Event e){
	if (debug_button)cout<<"button.cpp::handle_event\n";
		if (e.type==SDL_MOUSEMOTION){
		int x_c = e.motion.x;
        int y_c = e.motion.y;
        // cout<<(int)isInside(x_c,y_c)<<":"<<cur_color<<" is inside\n";
		if (isInside(x_c,y_c)){
			cur_color=1;
			texture=colors[1];
		}
		
	}
	else{
	if(strcmp(label,"Exit")==0){
		if (music_on){
			m->PlaySound("button");
		}	
		*state=5;	
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

}
}

void Button::render(SDL_Renderer *renderer){
	if (debug_button)cout<<"button.cpp::render\n";
	SDL_RenderCopy(renderer,texture,NULL,&dest);
}

void Button::set_original(){
	cur_color=0;
			texture=colors[cur_color];
}