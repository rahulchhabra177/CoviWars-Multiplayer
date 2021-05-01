#include "character.h";
#include "game.hpp"
#include "button.h"
#include "Texture.h"
#include "Map.h"
using namespace std;


class play{
	
	public:
	
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Renderer* renderer;
		
		Character* pacman=nullptr;
		vector<Character*> enemies;
		
		play(char* title,int numEnemies,SDL_Texture* poster, SDL_Renderer* localRenderer){
			name = title;
			background = poster;
			renderer = localRenderer;
			pacman = new Character("./../assets/hero.bmp",renderer,1920,1080,false);
			
			for(int i=0;i<numEnemies;i++){
				Character* enemy=new Character("./../assets/corona.xcf",renderer,0,0,true);
				enemies.push_back(enemy);
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
			pacman->render();
			for(int i=0;i<enemies.size();i++){
				enemies[i]->render();
			}
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void update(){
		
		}
		
		void handle_event(SDL_Event e,int* state){
			pacman->update(e);
			if(e.type==SDL_QUIT){
				*state=4;
			}else if(e.type==SDL_MOUSEBUTTONDOWN){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					buttons[i]->handle_event(state);
				}
			}else if(e.type==SDL_KEYDOWN){
				if(e.key.keysym.sym==SDLK_ESCAPE){
					*state=4;
				}else if(e.key.keysym.sym==SDLK_p){
					*state=2;
				}
			}
		} 
};
