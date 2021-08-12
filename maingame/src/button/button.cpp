#include "button.h";

using namespace std;
bool button_debug=false;

//Button constructor
Button::Button(char* name, SDL_Renderer* localRenderer,int width,int height){
	if (button_debug)cout<<"button.cpp::Button1\n";
	
	//Initialising font size and style for text on buttons
	clickable=true;
	renderer=localRenderer;
	TTF_Init();
	label = name;
	s_height=height;
	s_width=width;
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	
	//Generating button texture from SDL surface
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,{255,255,255,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface=TTF_RenderText_Solid(font,label,{251,252,25,251});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	
	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";
	}
	else{
		texture=colors[(int)isSelected][cur_color];
		SDL_FreeSurface(textSurface);
	}
} 
//Overloaded Button Constructor for Rendering Text
Button::Button(char* name, SDL_Renderer* localRenderer,string fnt,int r,int g,int b){
	if (button_debug)cout<<"button.cpp::Button1\n";
	
	//Initialising font size and style for text on buttons
	clickable=false;
	renderer=localRenderer;
	TTF_Init();
	label = name;
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	
	//Generating button texture from SDL surface
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,{r,g,b,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	
	
	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";
	}
	else{
		texture=colors[(int)isSelected][cur_color];
		SDL_FreeSurface(textSurface);
	}
} 

//Overloaded button constructor for toggle buttons(like music on/off, sound effects on/off, etc.)
Button::Button(char* name,char* name2, SDL_Renderer* localRenderer,int width,int height){
	if (button_debug)cout<<"button.cpp::Button\n";
	
	//Initialising font size and style for text on buttons
	clickable=true;
	renderer=localRenderer;
	TTF_Init();
	label = name;
	s_height=height;
	s_width=width;
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	
	if (font==NULL){
		cout<<"Error:Couldn't initialize font"<<TTF_GetError()<<"\n";
		exit(1);
	}
	
	//Generating button textures from SDL surface for both versions of the button
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,{255,255,255,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface=TTF_RenderText_Solid(font,label,{255,255,25,255});
	colors[0].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	
	textSurface=TTF_RenderText_Solid(font,name2,{255,255,204,255});
	colors[1].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	textSurface=TTF_RenderText_Solid(font,name2,{255,255,25,255});
	colors[1].push_back(SDL_CreateTextureFromSurface(renderer,textSurface));
	
	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize button:"<<label<<"\n";		//To manage exit condition
	}
	else{
		texture=colors[(int)isSelected][cur_color];
		SDL_FreeSurface(textSurface);
	}
} 

//Setting coordinates of the place on the screen where the button will be rendered
void Button::set_cor(int a,int b,int q,int w){
	if (button_debug)cout<<"button.cpp::set_cor\n";
	dest.x=a;
	dest.y=b;
	dest.w=q;
	dest.h=w;
}

//Tracking the mouse pointer to detect possible button presses
bool Button::isInside(int a,int b){
	if (button_debug)cout<<"button.cpp::isInside\n";
	if (!clickable)return false;
	//The pointer location is scaled with respect to 3700*2100 resolution
	if (3700*a>=(dest.x*s_width) && 3700*a<=((dest.x+dest.w)*s_width) && 2100*b>=(dest.y*s_height) && b*2100<=((dest.y+dest.h)*s_height)){return true;}
	return false;
}
//Function change colour or label of button/Text

void Button::changeLabel(string newlabel,string fnt,int r,int g,int b){

	if (button_debug)cout<<"button.cpp:changeLabel:"<<newlabel<<"\n";
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,&newlabel[0],{r,g,b,255});
	if (textSurface==nullptr){
		cout<<"Couldn;t find font\n";
		return;
	}

	colors[0][0]=SDL_CreateTextureFromSurface(renderer,textSurface);
	textSurface=TTF_RenderText_Solid(font,&newlabel[0],{251,255,25,255});
	if (textSurface==nullptr){
		cout<<"Couldn;t find font\n";
		return;
	}
	colors[0][1]=SDL_CreateTextureFromSurface(renderer,textSurface);
	texture=colors[0][0];


}



//Event handling to decide which event to execute if a particular button is pressed
void Button::handle_event(int* state,SoundClass *m,int* prevstate,SDL_Event e){
	if (button_debug)cout<<"button.cpp::handle_event:"<<label<<"\n";
	if (!clickable)return;
	//We have implemented an effect in which hovering over a button with a mouse
	//highlights that particular button, and the following block of code checks 
	//for such an event
	if (e.type==SDL_MOUSEMOTION){
		int x_c = e.motion.x;
        	int y_c = e.motion.y;
		if (cur_color!=1){
			cur_color=1;
			texture=colors[(int)isSelected][1];
			dest.x-=10;
			dest.y-=10;
			dest.h+=20;
			dest.w+=20;
		}
	}
	else{
		//Event handling when these buttons are clicked
		
		//The effects are generally of the form:
		// 1) Every button press is accompanied by a sound effect
		// 2) Every button press causes a change in state of the game,
		//    depending on the type of the button	
		if(strcmp(label,"Exit")==0){
			m->PlaySound("button");
			*state=6;	
		}
	else if(strcmp(label,"Single Player")==0){
			m->PlaySound("button");
			m->PlaySound("start");
			*state=100;	
		}
	else if(strcmp(label,"MultiPlayer")==0){
			m->PlaySound("button");
			m->PlaySound("start");
			*prevstate=0;
			*state=101;	
		}
	else if(strcmp(label,"Next Level")==0){
			m->PlaySound("button");
			*state=-2;
		}
	else if(strcmp(label,"Options")==0){
			m->PlaySound("button");
			*prevstate=*state;
			*state=3;
		}
	else if(strcmp(label,"Pause")==0){
			m->PlaySound("button");
			*state=2;
		}
	else if(strcmp(label,"Resume")==0){
			m->PlaySound("button");
			*state=0;
		}
	else if(strcmp(label,"Play Again")==0){
			m->PlaySound("button");
			*state=-2;
		}
	else if(strcmp(label,"Back")==0){
			m->PlaySound("button");
			*state=*prevstate;
		}
	else if(strcmp(label,"Quit")==0){
			m->PlaySound("button");
			*state=1;
		}
	else if(strcmp(label,"Rules")==0){
			m->PlaySound("button");
			*prevstate=*state;
			*state=8;
		}
	else if(strcmp(label,"Credits")==0){
			m->PlaySound("button");
			*prevstate=*state;
			*state=7;
		}
	else if(strcmp(label,"Music:  ON")==0){
			m->PlaySound("button");
			label="Music:  OFF";
			texture=colors[1][1];
			isSelected=true;
			m->changeMusicState(false);
		
		}
	else if(strcmp(label,"Music:  OFF")==0){
			m->PlaySound("button");
			label="Music:  ON";
			texture=colors[0][1];
			isSelected=false;
			m->changeMusicState(true);
			
		}
	else if(strcmp(label,"Sounds:  ON")==0){
			m->PlaySound("button");
			label="Sounds:  OFF";
			texture=colors[1][1];
			isSelected=true;
			m->changeSoundState(false);
		
		}
	else if(strcmp(label,"Sounds:  OFF")==0){
			m->PlaySound("button");
			label="Sounds:  ON";
			texture=colors[0][1];
			isSelected=false;
			m->changeSoundState(true);	
		}
	}
}

//To render the button on the screen/window
void Button::render(SDL_Renderer *renderer){
	if (button_debug)cout<<"button.cpp::render\n";
	SDL_RenderCopy(renderer,texture,NULL,&dest);
}

//Reverting a button to its original state when the mouse pointer leaves it
void Button::set_original(){
	if (cur_color!=0){
		dest.x+=10;
		dest.y+=10;
		dest.h-=20;
		dest.w-=20;
	}
	cur_color=0;
	texture=colors[isSelected][cur_color];
}

