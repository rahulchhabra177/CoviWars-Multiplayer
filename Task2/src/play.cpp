#include "state.h";
#include "pacman.h";
using namespace std;

class play : public State{
	
	public:
	
		pacman* mainPlayer=nullptr;
		vector<pacman*> enemies;
		
		play(char* title,int numEnemies,SDL_Texture* poster){
			name = title;
			background = poster;
			
			
		}
		
		int locatePointer(int a,int b){
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		void render(SDL_Renderer* renderer){
			SDL_RenderCopy(renderer,background,NULL,NULL);
			mainPlayer->render();
			for(int i=0;i<enemies.size();i++){
				enemies[i]->render();
			}
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
	
};
