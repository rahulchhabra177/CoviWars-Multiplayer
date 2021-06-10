#include "popup.h"


Popup::Popup(SDL_Renderer* localRenderer,int type,bool isTimed,int width,int height){

	renderer=localRenderer;
	dst.x=925;
	dst.y=500;
	dst.w=1850;
	dst.h=1050;
	timed=isTimed;
	background=Texture::LoadT("./../assets/pop.jpg",renderer);

	back=Texture::LoadT("./../assets/redblur.png",renderer);
	// back = SDL_CreateTextureFromSurface(renderer,sback);

	startTime=SDL_GetTicks();
	if (type==1){
		timed=true;
		Button* startmulti_button=new Button("Next Level",renderer,width,height);
		startmulti_button->set_cor(1400,1000,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1400,1175,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Exit",renderer,width,height);
		exit_button->set_cor(1400,1350,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("CONGRATULATIONS",renderer,width,height);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);
	}
	else if (type==2){
		timed=true;
		Button* startmulti_button=new Button("Play Again",renderer,width,height);
		startmulti_button->set_cor(1220,1000,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1400,1200,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Exit",renderer,width,height);
		exit_button->set_cor(1400,1400,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("YOU LOSE!",renderer,width,height);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);
	}else if (type==3){
		Button* start_button=new Button("Music:  ON","Music:  OFF",renderer,width,height);
		start_button->set_cor(1220,1000,540,150);
		buttons.push_back(start_button);
		
		Button* options_button=new Button("Sounds:  ON","Sounds:  OFF",renderer,width,height);
		options_button->set_cor(1400,1200,500,150);
		buttons.push_back(options_button);
		
		Button* option_button=new Button("Back",renderer,width,height);
		option_button->set_cor(1400,1400,500,150);
		buttons.push_back(option_button);


		Button* logo=new Button("Options",renderer,width,height);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);
	}else if (type==4){
		timed=true;
		Button* startmulti_button=new Button("Resume",renderer,width,height);
		startmulti_button->set_cor(1220,1000,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1400,1200,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Exit",renderer,width,height);
		exit_button->set_cor(1400,1400,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("YOU LOSE!",renderer,width,height);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);
	}else if (type==-1){
		Button* startmulti_button=new Button("Back",renderer,width,height);
		startmulti_button->set_cor(1400,1000,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1400,1200,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Exit",renderer,width,height);
		exit_button->set_cor(1400,1400,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("Waiting for other player to join",renderer,width,height);
		logo->set_cor(1020,520,1600,400);
		buttons.push_back(logo);
	}
}

void Popup::update(int * state){
	
	if (remaining_time==0 && timed){
		*state=-2;
	}
	// cout<<startTime<<":"<<SDL_GetTicks()<<"::"<<remaining_time<<"\n";
	if (SDL_GetTicks()-startTime>=1000){
		startTime=SDL_GetTicks();
		if (timed)remaining_time--;
	}

}

int Popup::locatePointer(int a,int b){
	for(int i=0;i<buttons.size();i++){
		if(buttons[i]->isInside(a,b)){
			return i;
		}
	}
	return -1;
}
		

void Popup::render(SDL_Renderer* renderer){

	SDL_RenderCopy(renderer,back,NULL,NULL);
	SDL_RenderCopy(renderer,background,NULL,&dst);
	for(int i=0;i<buttons.size();i++){
		buttons[i]->render(renderer);
	}
}

void Popup::handle_event(SDL_Event e,int * state,SoundClass* m,int* prevstate){
	if(e.type==SDL_QUIT){
		*state=6;
	}else if(e.type==SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEMOTION){
		int a,b;
		SDL_GetMouseState(&a,&b);
		int i = locatePointer(a,b);
		if(i>=0){
			buttons[i]->handle_event(state,m,prevstate,e);
		}else{
			for(int i=0;i<buttons.size();i++){buttons[i]->set_original();}
		}
	}else if(e.type==SDL_KEYDOWN){
		if(e.key.keysym.sym==SDLK_ESCAPE){
			*state=6;
		}
	}
}