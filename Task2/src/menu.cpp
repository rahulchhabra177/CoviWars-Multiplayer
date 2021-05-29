#include "button.h"
#include "Texture.h"
using namespace std;
class Menu{
	
	public:
		
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background,*playerName;
		SDL_Renderer* renderer;
		bool debug_menu=true;
		SDL_Rect input_box;
		bool changed=true;
		string cur_player="";
		Menu(char* title, int menuType, SDL_Texture* poster, SDL_Renderer* localRenderer){
			if (debug_menu)cout<<"menu.cpp::Menu\n";
			name = title;
			background = poster;
			renderer = localRenderer;
			
			if(menuType==1){
				Button* start_button=new Button("Start",renderer);
				start_button->set_cor(589,286,174,49);
				buttons.push_back(start_button);
				
				Button* options_button=new Button("Options",renderer);
				options_button->set_cor(580,410,174,49);
				buttons.push_back(options_button);
				
				Button* exit_button=new Button("Exit",renderer);
				exit_button->set_cor(589,508,174,49);
				buttons.push_back(exit_button);
				
				Button* logo=new Button("COROMAN",renderer);
				logo->set_rect(412,62,920,188);
				buttons.push_back(logo);
				input_box.x=949;
				input_box.y=678;
				input_box.h=100;
				input_box.w=220;
				playerName=Texture::LoadText("Enter Some Text",renderer);
			}
			else if(menuType==2){
				Button* resume_button=new Button("Resume",renderer);
				resume_button->set_cor(600,300,20,70);
				buttons.push_back(resume_button);
				
				Button* exit_button=new Button("Exit",renderer);
				exit_button->set_cor(600,400,20,70);
				buttons.push_back(exit_button);
			}
			else if(menuType==4){
				Button* playAgain=new Button("Play Again",renderer);
				playAgain->set_cor(600,50,20,70);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer);
				exit_button->set_cor(600,600,20,70);
				buttons.push_back(exit_button);
			}
		}
		
		int locatePointer(int a,int b){
			if (debug_menu)cout<<"menu.cpp::locatePointer\n";
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		void render(){
			if (debug_menu)cout<<"menu.cpp::render\n";

			SDL_RenderCopy(renderer,background,NULL,NULL);
			if (changed){
				
				changed=false;
				if (cur_player!=""){
				playerName=Texture::LoadText(&cur_player[0],renderer);
			}
			}
			SDL_RenderCopy(renderer,playerName,NULL,&input_box);
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void update(){
			
		}
		
		void handle_event(SDL_Event e,int* state,SoundClass *m,bool music_on){
			if (debug_menu)cout<<"menu.cpp::handle_event\n";
			// cout<<1;
			if(e.type==SDL_QUIT){
				*state=5;
				// cout<<2;
			}
			else if (e.type==SDL_TEXTINPUT){
				// cout<<3;
				changed=true;
				cur_player+=e.text.text;
			}
			else if (e.key.keysym.sym == SDLK_BACKSPACE && cur_player.length() > 0){
				// cout<<4;
				cur_player.pop_back();
				changed=true;
							}

			else if(e.type==SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEMOTION){
				// cout<<5;
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
// cout<<6;
					buttons[i]->handle_event(state,m,music_on,e);
				}
				else{
					// cout<<7;
					for(int i=0;i<buttons.size();i++){buttons[i]->set_original();}
				}
			}else if(e.type==SDL_KEYDOWN){
				// cout<<9;
				if(e.key.keysym.sym==SDLK_ESCAPE && *state==2){
					// cout<<10;
					*state=0;
				}
			}
		}
	
};







