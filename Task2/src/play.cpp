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
			
			for(int i=0;i<numEnemies;i++){
				Character* enemy=nullptr;
				enemies.push_back(enemy);
			}
			
			for(int i=0;i<numEnemies;i++){
				enemies[i]=new Character("./../assets/corona.bmp",renderer,1000,1000,false);
			}
			
			pacman = new Character("./../assets/hero.bmp",renderer,100,100,false);
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
			pacman->render(renderer);
			for(int i=0;i<enemies.size();i++){
				enemies[i]->render(renderer);
			}
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void update(int* state){
			pacman->updatePlayer();
			/*for(int i=0;i<enemies.size();i++{
				enemies[i].updatePlayer();
			}*/
			for(int i=0;i<enemies.size();i++){
				if(pacman->collide(enemies[i])){
					*state = 4;
				}	
			}
		}
		
		void handle_event(SDL_Event e,int* state){
			pacman->changeSpeed(e);
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
				if(e.key.keysym.sym==SDLK_ESCAPE){
					*state=5;
				}else if(e.key.keysym.sym==SDLK_p){
					*state=2;
				}
			}
		} 
};
