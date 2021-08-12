#include "popup.h"

//The main difference between normal menus and pop-up menus is that a menu
//signifies a completely different state of the game, and therefore occupies
//the whole screen, while a pop-up menu object is simply another object on the 
//screen in the same state of the game, and when it is rendered, it doesn't
//occupy the whole screen, and also doesn't cause any state transitions in
//the game. Consequently, the game feels less cluttered, more connected and
//more convenient to use as having a large number of menus partitions the game into a large number of 
//states which makes the transitions between a menu and play state significantly 
//slower as compared to that between a pop up menu and the play state

//Constructor
Popup::Popup(SDL_Renderer* localRenderer,int type,bool isTimed,int width,int height){

	renderer=localRenderer;
	
	//Position and dimensions of popup menu
	dst.x=925;
	dst.y=500;
	dst.w=1850;
	dst.h=1150;

	//This checks if the pop-up is timed, i.e. if the pop-up automatically
	//disappears after some time
	timed=isTimed;

	//Background textures
	background=Texture::LoadT("./../assets/backgrounds/popup.png",renderer);
	back = Texture::LoadT("./../assets/backgrounds/redblur.png",renderer);

	startTime=SDL_GetTicks();

	//Different types of pop-up menus

	//Pop-up menu in the transition between levels
	if (type==1){
		Button* startmulti_button=new Button("Next Level",renderer,width,height);
		startmulti_button->set_cor(1550,950,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1550,1125,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Quit",renderer,width,height);
		exit_button->set_cor(1550,1300,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("CONGRATULATIONS",renderer,"",255,255,255);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);
	}

	//Game over pop-up menu
	else if (type==2){
		Button* startmulti_button=new Button("Play Again",renderer,width,height);
		startmulti_button->set_cor(1550,950,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1550,1125,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Quit",renderer,width,height);
		exit_button->set_cor(1550,1300,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("YOU LOSE!",renderer,"",255,255,255);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);

	//Options pop-menu
	}else if (type==3){
		Button* start_button=new Button("Music:  ON","Music:  OFF",renderer,width,height);
		start_button->set_cor(1550,950,540,150);
		buttons.push_back(start_button);
		
		Button* options_button=new Button("Sounds:  ON","Sounds:  OFF",renderer,width,height);
		options_button->set_cor(1550,1125,500,150);
		buttons.push_back(options_button);
		
		Button* option_button=new Button("Back",renderer,width,height);
		option_button->set_cor(1550,1300,500,150);
		buttons.push_back(option_button);

		Button* logo=new Button("Options",renderer,"",255,255,255);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);

	//Pause pop-up menu
	}else if (type==4){
		Button* startmulti_button=new Button("Resume",renderer,width,height);
		startmulti_button->set_cor(1550,1000,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1550,1200,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Quit",renderer,width,height);
		exit_button->set_cor(1550,1400,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("Game Paused!",renderer,"",255,255,255);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);

	//Lobby pop-up menu
	}else if (type==-1){
		Button* startmulti_button=new Button("Back",renderer,width,height);
		startmulti_button->set_cor(1550,1000,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1550,1200,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Quit",renderer,width,height);
		exit_button->set_cor(1550,1400,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("Waiting for other player to join",renderer,"",255,255,255);
		logo->set_cor(1020,520,1600,400);
		buttons.push_back(logo);
	}

	//Congratulations pop-up
	else if (type==5){
		Button* startmulti_button=new Button("Play Again",renderer,width,height);
		startmulti_button->set_cor(1550,950,540,150);
		buttons.push_back(startmulti_button);

		Button* options_button=new Button("Options",renderer,width,height);
		options_button->set_cor(1550,1125,500,150);
		buttons.push_back(options_button);

		Button* exit_button=new Button("Quit",renderer,width,height);
		exit_button->set_cor(1550,1300,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("YOU WIN!",renderer,"",255,255,255);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);
	}
	else if (type==-2){
		// timed=true;
		Button* startmulti_button=new Button("Rahul Chhabra",renderer,"",255,255,52);
		startmulti_button->set_cor(1550,950,540,150);
		buttons.push_back(startmulti_button);
		
		Button* options_button=new Button("Shrey Patel",renderer,"",255,255,52);
		options_button->set_cor(1550,1125,500,150);
		buttons.push_back(options_button);
		
		Button* exit_button=new Button("Back",renderer,width,height);
		exit_button->set_cor(1550,1300,500,150);
		buttons.push_back(exit_button);

		Button* logo=new Button("Contributors",renderer,"",255,255,52);
		logo->set_cor(1220,520,1200,400);
		buttons.push_back(logo);
	}
}

//To check whether the pop-up menu has timed out, if it is timed
void Popup::update(int * state){

}

//Same as button and menu classes, to track the location of the mouse pointer 
int Popup::locatePointer(int a,int b){
	for(int i=0;i<buttons.size();i++){
		if(buttons[i]->isInside(a,b)){
			return i;
		}
	}
	return -1;
}

//Local renderer, where the rendering is deferred to the buttons, just like
//the menu class		
void Popup::render(SDL_Renderer* renderer){
	SDL_RenderCopy(renderer,back,NULL,NULL);
	SDL_RenderCopy(renderer,background,NULL,&dst);
	for(int i=0;i<buttons.size();i++){
		buttons[i]->render(renderer);
	}
}

//Local event handler, again similar to menu state
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
