#include "./../button/button.h"
using namespace std;
extern char* cplayer;

class Menu{
	
	public:
		
		//Basic parameters which are common to all menus
		char* name;								//Name of menu
		vector<Button*> buttons;				//List of buttons in the menu
		SDL_Texture* background,*playerName;
		SDL_Renderer* renderer;
		bool menu_debug=false;
		SDL_Rect input_box;						//For taking in the name of the player as input
		bool changed=false;						//To check if the player inputs any characters
		string cur_player="";					//The name of the current player
		char* cplayer=&cur_player[0];
		int s_width,s_height;
		SDL_Texture* rules=nullptr;
		SDL_Rect rule_rect;
		int type;
		//Menu constructor
		Menu(char* title, int menuType, SDL_Texture* poster, SDL_Renderer* localRenderer,int width,int height){
			if (menu_debug)cout<<"menu.cpp::Menu\n";
			
			//Initialising common parameters
			name = title;
			background = poster;
			s_width=width;
			s_height=height;
			renderer = localRenderer;
			type=menuType;
			//Initialising buttons in different menus

			//Start Menu
			if(menuType==1){
				changed=true;
				Button* startsingle_button=new Button("Single Player",renderer,width,height);
				startsingle_button->set_cor(1680,800,540,170);
				buttons.push_back(startsingle_button);

				Button* startmulti_button=new Button("MultiPlayer",renderer,width,height);
				startmulti_button->set_cor(1680,1000,540,170);
				buttons.push_back(startmulti_button);
				
				Button* options_button=new Button("Options",renderer,width,height);
				options_button->set_cor(1700,1200,500,170);
				buttons.push_back(options_button);
				
				Button* rule_button=new Button("Rules",renderer,width,height);
				rule_button->set_cor(1700,1400,500,170);
				buttons.push_back(rule_button);

				Button* credit_button=new Button("Credits",renderer,width,height);
				credit_button->set_cor(1700,1600,500,170);
				buttons.push_back(credit_button);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1800,500,170);
				buttons.push_back(exit_button);
				
				Button* logo=new Button("COVI-WARS",renderer,"",255,255,252);
				logo->set_cor(1300,250,1200,400);
				buttons.push_back(logo);
				
				input_box.x=0/*2926*/;
				input_box.y=0/*2034*/;
				input_box.h=308;
				input_box.w=660;
				playerName=Texture::LoadText("Enter Your Name",renderer);
				
			}

			//Pause Menu
			else if(menuType==2){

				Button* resume_button=new Button("Resume",renderer,width,height);
				resume_button->set_cor(1700,900,300,70);
				buttons.push_back(resume_button);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1100,300,70);
				buttons.push_back(exit_button);

			}

			//Options Menu
			else if(menuType==3){

				Button* start_button=new Button("Music:  ON","Music:  OFF",renderer,width,height);
				start_button->set_cor(1700,900,500,170);
				buttons.push_back(start_button);
				
				Button* options_button=new Button("Sounds:  ON","Sounds:  OFF",renderer,width,height);
				options_button->set_cor(1700,1200,500,170);
				buttons.push_back(options_button);
				
				Button* option_button=new Button("Back",renderer,width,height);
				option_button->set_cor(1700,1500,500,170);
				buttons.push_back(option_button);

				Button* logo=new Button("Options",renderer,width,height);
				logo->set_cor(1350,250,800,300);
				buttons.push_back(logo);

			}

			//Game Over Menu
			else if(menuType==4){

				Button* playAgain=new Button("Play Again",renderer,width,height);
				playAgain->set_cor(1700,1500,300,70);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1800,300,70);
				buttons.push_back(exit_button);
			}

			//Winner Screen
			else if(menuType==5){

				Button* playAgain=new Button("Play Again",renderer,width,height);
				playAgain->set_cor(1700,1500,300,70);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1800,300,70);
				buttons.push_back(exit_button);
			}
			else if(menuType==6){

				rules=Texture::LoadT("./../assets/backgrounds/rules.png",renderer);
				rule_rect.x=250;
				rule_rect.y=-50;
				rule_rect.h=1700;
				rule_rect.w=3200;
				Button* back_button=new Button("Back",renderer,width,height);
				back_button->set_cor(1700,1850,300,70);
				back_button->changeLabel("Back","",255,255,255);
				buttons.push_back(back_button);
			}

		}
		
		int locatePointer(int a,int b){
			if (menu_debug)cout<<"menu.cpp::locatePointer\n";
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		//Local render function
		void render(){
			if (menu_debug)cout<<"menu.cpp::render\n";

			SDL_RenderCopy(renderer,background,NULL,NULL);
			if (changed and type==1){
				changed=false;
				if (cur_player!=""){
				playerName=Texture::LoadText(&cur_player[0],renderer);
				SDL_RenderCopy(renderer,playerName,NULL,&input_box);
				input_box.w=50*cur_player.size();
				}else{
					playerName=Texture::LoadText("Enter Your Name",renderer);
					input_box.w=700;
					SDL_RenderCopy(renderer,playerName,NULL,&input_box);
				}
			}
			if (type==1){
				SDL_RenderCopy(renderer,playerName,NULL,&input_box);
			}
			
			else if (type==6){
				SDL_RenderCopy(renderer,rules,NULL,&rule_rect);	
			}

			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void update(){
			
		}
		
		//Local event handler. Again notice that the event handling is further
		//deferred to the button class to take care of the function of each 
		//button separately
		void handle_event(SDL_Event e,int* state,SoundClass *m,int* prevstate){
			if (menu_debug)cout<<"menu.cpp::handle_event\n";
			if(e.type==SDL_QUIT ){
				*state=6;
			}
			else if (e.key.keysym.sym == SDLK_ESCAPE){
				*state=1;
			}
			else if (e.type==SDL_TEXTINPUT){
				changed=true;
				cur_player+=e.text.text;
			}else if (e.key.keysym.sym == SDLK_BACKSPACE && cur_player.length() > 0){
				cur_player.pop_back();
				changed=true;
			}else if(e.type==SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEMOTION){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					buttons[i]->handle_event(state,m,prevstate,e);
				}else{
					for(int i=0;i<buttons.size();i++){buttons[i]->set_original();}
				}
			}
			else if(e.type==SDL_KEYDOWN){
				if(e.key.keysym.sym==SDLK_ESCAPE && *state==2){
					*state=0;
				}
			}
		}
};






