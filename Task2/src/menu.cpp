#include "button.h"
#include "Texture.h"
using namespace std;

class Menu{
	
	public:
		
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Texture* playerName;
		SDL_Renderer* renderer;
		/*SDL_Rect input_box;
		bool changed = false;
		string cur_player = "";*/
		
		Menu(char* title, int menuType, SDL_Texture* poster, SDL_Renderer* localRenderer,int width,int height){
			name = title;
			background = poster;
			renderer = localRenderer;
			
			if(menuType==1){
				Button* start_button=new Button("Start",renderer,width,height,"./../assets/start.png");
				start_button->set_cor(1700,700,300,70);
				buttons.push_back(start_button);
				
				Button* options_button=new Button("Options",renderer,width,height,"./../assets/options.png");
				options_button->set_cor(1700,900,300,70);
				buttons.push_back(options_button);
				
				Button* exit_button=new Button("Exit",renderer,width,height,"./../assets/exit.png");
				exit_button->set_cor(1700,1100,300,70);
				buttons.push_back(exit_button);
				
				Button* logo=new Button("COROMAN",renderer,width,height,"./../assets/logo.png");
				logo->set_cor(1450,200,800,200);
				buttons.push_back(logo);
				
				/*input_box.x=2926;
				input_box.y=2034;
				input_box.h=308;
				input_box.w=660;
				playerName=Texture::LoadText("Enter Some Text",renderer);*/
				
			}else if(menuType==2){
				Button* resume_button=new Button("Resume",renderer,width,height,"./../assets/resume.png");
				resume_button->set_cor(1700,900,300,70);
				buttons.push_back(resume_button);
				
				Button* exit_button=new Button("Exit",renderer,width,height,"./../assets/exit.png");
				exit_button->set_cor(1700,1100,300,70);
				buttons.push_back(exit_button);
			}else if(menuType==4){
				Button* playAgain=new Button("Play Again",renderer,width,height,"./../assets/playagain.jpeg");
				playAgain->set_cor(1700,1500,300,70);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer,width,height,"./../assets/exit.png");
				exit_button->set_cor(1700,1800,300,70);
				buttons.push_back(exit_button);
			}else if(menuType==5){
				Button* playAgain=new Button("Play Again",renderer,width,height,"./../assets/playagain.jpeg");
				playAgain->set_cor(1700,1500,300,70);
				buttons.push_back(playAgain);
				
				Button* exit_button=new Button("Exit",renderer,width,height,"./../assets/exit.png");
				exit_button->set_cor(1700,1800,300,70);
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
			
			/*if(changed){
				changed = false;
				if(cur_player!=""){
					playerName = Texture::LoadText(&cur_player[0],renderer);
				}
			}*/
			
			//SDL_RenderCopy(renderer,playerName,NULL,&input_box);
			
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void update(){
			
		}
		
		void handle_event(SDL_Event e,int* state,SoundClass *m,bool music_on){
			if(e.type==SDL_QUIT){
				*state=5;
			/*}else if(e.type==SDL_TEXTINPUT){
				changed = true;
				cur_player+=e.text.text;
			}else if(e.key.keysym.sym == SDLK_BACKSPACE && cur_player.length()>0){
				cur_player.pop_back();
				changed = true;*/
			}else if(e.type==SDL_MOUSEBUTTONDOWN /*|| e.type==SDL_MOUSEMOTION*/){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					buttons[i]->handle_event(state,m,music_on);
				}/*else{
					for(int i=0;i<buttons.size();i++){
						buttons[i]->set_original();
					}
				}*/
			}else if(e.type==SDL_KEYDOWN){
				if(e.key.keysym.sym==SDLK_ESCAPE && *state==2){
					*state=0;
				}
			}
		}
	
};







