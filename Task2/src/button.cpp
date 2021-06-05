#include "button.h";

using namespace std;
bool button_debug=true;
Button::Button(char* name, SDL_Renderer* renderer,int width,int height){
	if (button_debug)cout<<"button.cpp::Button\n";
	TTF_Init();
	label = name;
	s_height=height;
	s_width=width;
	TTF_Font * font;//=new TTFont();
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	// SDL_Color color={0,255,0,255};
	// SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,color);
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,{149,215,246,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface=TTF_RenderText_Solid(font,label,{14,215,246,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	

	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";		//To manage exit condition
	}
	else{
	texture=colors[(int)isSelected][cur_color];
		SDL_FreeSurface(textSurface);
	}
} 

Button::Button(char* name,char* name2, SDL_Renderer* renderer,int width,int height){
	if (button_debug)cout<<"button.cpp::Button\n";
	TTF_Init();
	label = name;
	s_height=height;
	s_width=width;
	TTF_Font * font;//=new TTFont();
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	// SDL_Color color={0,255,0,255};
	// SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,color);
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,{149,215,246,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface=TTF_RenderText_Solid(font,label,{255,255,255,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	
	textSurface=TTF_RenderText_Solid(font,name2,{14,25,204,255});
	colors[1].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface=TTF_RenderText_Solid(font,name2,{255,255,255,255});
	colors[1].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	
	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";		//To manage exit condition
	}
	else{
	texture=colors[(int)isSelected][cur_color];
		SDL_FreeSurface(textSurface);
	}
} 



void Button::set_cor(int a,int b,int q,int w){
	if (button_debug)cout<<"button.cpp::set_cor\n";
	dest.x=a;
	dest.y=b;
	dest.w=q;
	dest.h=w;
}

void Button::set_rect(int a,int b,int q,int w){
	if (button_debug)cout<<"button.cpp::set_rect\n";
	dest.x=a;
	dest.y=b;
	dest.w=q-a;
	dest.h=w-b;
}

bool Button::isInside(int a,int b){
	if (button_debug)cout<<"button.cpp::isInside\n";
	if (3700*a>=(dest.x*s_width) && 3700*a<=((dest.x+dest.w)*s_width) && 2100*b>=(dest.y*s_height) && b*2100<=((dest.y+dest.h)*s_height)){return true;}
	return false;
}

void Button::handle_event(int* state,SoundClass *m,bool music_on,SDL_Event e){
	if (button_debug)cout<<"button.cpp::handle_event:"<<label<<"\n";
		if (e.type==SDL_MOUSEMOTION){
		int x_c = e.motion.x;
        int y_c = e.motion.y;
        // cout<<(int)isInside(x_c,y_c)<<":"<<cur_color<<" is inside\n";
		if (/*isInside(x_c,y_c) && */cur_color!=1){
			cur_color=1;
			texture=colors[(int)isSelected][1];
			dest.x-=10;
			dest.y-=10;
			dest.h+=20;
			dest.w+=20;
		}
		
	}
	else{
	if(strcmp(label,"Exit")==0){
		if (music_on){
			m->PlaySound("button");
		}	
		*state=6;	
	}else if(strcmp(label,"Single Player")==0){
		if (music_on){
			m->PlaySound("button");
			m->PlaySound("start");
		}
		*state=0;	
	}else if(strcmp(label,"MultiPlayer")==0){
		if (music_on){
			m->PlaySound("button");
			m->PlaySound("start");
		}
		*state=0;	
	}else if(strcmp(label,"Next Level")==0){
		if (music_on){
			m->PlaySound("button");
			*state=-2;
		}
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
	}else if(strcmp(label,"Back")==0){
		if(music_on){
			m->PlaySound("button");
		}
		*state=1;
	}else if(strcmp(label,"Music:  ON")==0){
		if(music_on){
			m->PlaySound("button");
		}
		label="Music:  OFF";
		texture=colors[1][1];
		isSelected=true;
		m->changeMusicState(false);
	
	}else if(strcmp(label,"Music:  OFF")==0){
		if(music_on){
			m->PlaySound("button");
		}
		label="Music:  ON";
		texture=colors[0][1];
		isSelected=false;
		m->changeMusicState(true);
		
	}
	else if(strcmp(label,"Sounds:  ON")==0){
		if(music_on){
			m->PlaySound("button");
		}
		label="Sounds:  OFF";
		texture=colors[1][1];
		isSelected=true;
		m->changeSoundState(false);
	
	}else if(strcmp(label,"Sounds:  OFF")==0){
		if(music_on){
			m->PlaySound("button");
		}
		label="Sounds:  ON";
		texture=colors[0][1];
		isSelected=false;
		m->changeSoundState(true);
		
	}
}
}

void Button::render(SDL_Renderer *renderer){
	if (button_debug)cout<<"button.cpp::render\n";
	SDL_RenderCopy(renderer,texture,NULL,&dest);
}

void Button::set_original(){
	// cout<<"set_original\n\n";
	if (cur_color!=0){
		dest.x+=10;
		dest.y+=10;
		dest.h-=20;
		dest.w-=20;
	}

	cur_color=0;
	texture=colors[isSelected][cur_color];
			}