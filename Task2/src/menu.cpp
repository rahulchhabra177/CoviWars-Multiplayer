#include "button.h"
#include "Texture.h"
using namespace std;
extern char* cplayer;

class Menu{
	
	public:
		
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background,*playerName;
		SDL_Renderer* renderer;
		bool menu_debug=true;
		SDL_Rect input_box;
		bool changed=true;
		string cur_player="";
		char* cplayer=&cur_player[0];
		Menu(char* title, int menuType, SDL_Texture* poster, SDL_Renderer* localRenderer,int width,int height){
			if (menu_debug)cout<<"menu.cpp::Menu\n";
			name = title;
			background = poster;
			renderer = localRenderer;
			
			if(menuType==1){
				Button* start_button=new Button("Start",renderer,width,height);
				start_button->set_cor(1700,900,500,170);
				buttons.push_back(start_button);
				
				Button* options_button=new Button("Options",renderer,width,height);
				options_button->set_cor(1700,1200,500,170);
				buttons.push_back(options_button);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1500,500,170);
				buttons.push_back(exit_button);
				
				Button* logo=new Button("COROMAN",renderer,width,height);
				logo->set_cor(1250,250,1200,400);
				buttons.push_back(logo);
				
				input_box.x=0/*2926*/;
				input_box.y=0/*2034*/;
				input_box.h=308;
				input_box.w=660;
				playerName=Texture::LoadText("Enter Your Name",renderer);
				
			}else if(menuType==2){
				Button* resume_button=new Button("Resume",renderer,width,height);
				resume_button->set_cor(1700,900,300,70);
				buttons.push_back(resume_button);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1100,300,70);
				buttons.push_back(exit_button);
			}else if(menuType==4){
				Button* playAgain=new Button("Play Again",renderer,width,height);
				playAgain->set_cor(1700,1500,300,70);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1800,300,70);
				buttons.push_back(exit_button);
			}else if(menuType==5){
				Button* playAgain=new Button("Play Again",renderer,width,height);
				playAgain->set_cor(1700,1500,300,70);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer,width,height);
				exit_button->set_cor(1700,1800,300,70);
				buttons.push_back(exit_button);
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
		
		void render(){
			if (menu_debug)cout<<"menu.cpp::render\n";

			SDL_RenderCopy(renderer,background,NULL,NULL);
			if (changed){
				
				changed=false;
				if (cur_player!=""){
				playerName=Texture::LoadText(&cur_player[0],renderer);
			}
			else{
				playerName=Texture::LoadText("Eneter Your Name",renderer);
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
			if (menu_debug)cout<<"menu.cpp::handle_event\n";
			// cout<<1;
			// cout<<e.type<<"|"<<SDL_MOUSEBUTTONDOWN<<"\n";
			if(e.type==SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE ){
				*state=6;
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
				// cout<<i<<"::::"<<a<<":::"<<b<<"\n\n";
				if(i>=0){
// cout<<6;
					buttons[i]->handle_event(state,m,music_on,e);
				}
				else{
					// cout<<7;
					for(int i=0;i<buttons.size();i++){buttons[i]->set_original();}
				}
			}
			else if(e.type==SDL_KEYDOWN){
				// cout<<9;
				if(e.key.keysym.sym==SDLK_ESCAPE && *state==2){
					// cout<<10;
					*state=0;
				}
			}
			// cout<<"menu.cpp::handle_Event...Comlpleted\n";
		}
	
};







