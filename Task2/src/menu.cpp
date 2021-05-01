#include "game.hpp"
#include "button.h"
#include "Texture.h"
using namespace std;

class Menu{
	
	public:
		
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Renderer* renderer;
		
		Menu(char* title, int menuType, SDL_Texture* poster, SDL_Renderer* localRenderer){
			name = title;
			background = poster;
			renderer = localRenderer;
			
			if(menuType==1){
				Button* start_button=new Button("Start",renderer,"./../assets/start.png");
				start_button->set_cor(1920,700,70,300);
				buttons.push_back(start_button);
				
				Button* options_button=new Button("Options",renderer,"./../assets/options.png");
				options_button->set_cor(1920,900,70,300);
				buttons.push_back(options_button);
				
				Button* exit_button=new Button("Exit",renderer,"./../assets/exit.png");
				exit_button->set_cor(1920,1100,70,300);
				buttons.push_back(exit_button);
				
				Button* logo=new Button("Logo",renderer,"./../assets/logo.png");
				logo->set_cor(100,100,100,100);
				buttons.push_back(logo);
			}else if(menuType==2){
				Button* resume_button=new Button("Resume",renderer,"./../assets/resume.png");
				resume_button->set_cor(1920,900,70,300);
				buttons.push_back(resume_button);
				
				Button* exit_button=new Button("Exit",renderer,"./../assets/exit.png");
				exit_button->set_cor(1920,1100,70,300);
				buttons.push_back(exit_button);
			}else if(menuType==4){
				Button* playAgain=new Button("Play Again",renderer,"./../assets/playagain.jpeg");
				playAgain->set_cor(1920,1500,70,300);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer,"./../assets/exit.png");
				exit_button->set_cor(1920,1800,70,300);
				buttons.push_back(exit_button);
			}
		}
		
		int locatePointer(int a,int b){
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		void render(){
			SDL_RenderCopy(renderer,background,NULL,NULL);
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void update(){
			
		}
		
		void handle_event(SDL_Event e,int* state){
			if(e.type==SDL_QUIT){
				*state=5;
			}else if(e.type==SDL_MOUSEBUTTONDOWN){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					buttons[i]->handle_event(state);
				}
			}else if(e.type==SDL_KEYDOWN){
				if(e.key.keysym.sym==SDLK_ESCAPE && *state==2){
					*state=0;
				}
			}
		}
	
};







