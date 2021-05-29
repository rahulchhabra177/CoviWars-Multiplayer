#include "button.h";
#include "scoreboard.h";
#include "maze.h";
using namespace std;

class play{
	
	public:
	
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Renderer* renderer;
		SDL_Texture *heading=nullptr;
		bool debug_play=false;
		Maze* maze=nullptr;
		Character* pacman=nullptr,*pacman2=nullptr;
		ScoreBoard *score=nullptr;
		vector<Enemy*> enemies;
		SDL_Rect* dst_hdng;
		play(char* title,int numEnemies,SDL_Texture* poster, SDL_Renderer* localRenderer){
			if (debug_play)cout<<"play.cpp:play\n";

			// cout<<1;
			name = title;
			background = poster;
			renderer = localRenderer;
			heading=Texture::LoadText("Scoreboard",renderer);
			for(int i=0;i<numEnemies;i++){
				Enemy* enemy=nullptr;
				enemies.push_back(enemy);
			}
			// cout<<2;
			
			for(int i=0;i<numEnemies;i++){
				enemies[i]=new Enemy(renderer,161,41,false);
			}
			// cout<<3;
			pacman = new Character("./../assets/corona.bmp",renderer,10,10,false);
			
			maze = new Maze(1,renderer);
			vector<Character*> temp;
			temp.push_back(pacman);
			// 
			score=new ScoreBoard(temp,renderer);
			// cout<<5;
// 



		}
		
		void render(){
			if (debug_play)cout<<"play.cpp:render\n";
			SDL_RenderCopy(renderer,background,NULL,NULL);
			// SDL_RenderCopy(renderer,score,NULL,NULL);
			score->render();

			pacman->render(renderer);
			if (pacman2!=nullptr){
				pacman2->render(renderer);
			}
			maze->render(renderer);
			for(int i=0;i<enemies.size();i++){
				enemies[i]->render(renderer);
			}
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}



		}
		
		void update(int* state,bool doUpdate,SoundClass* m,bool music_on,network*nmanager){
			if (debug_play)cout<<"play.cpp:update\n";
			maze->update();

			// score->update();
			if(true || (collidePlayer()) ){
				pacman->updatePlayer(nmanager,false);
				if (pacman2!=nullptr){
				pacman2->updatePlayer(nmanager,true);
				}	

			}
			for(int i=0;i<enemies.size();i++){
				if(pacman->collide(enemies[i],m,music_on)){
					*state = 4;
				}	
			}
		}
		
		void handle_event(SDL_Event e,int* state,SoundClass* m,bool music_on,network* nmanager){
			if (debug_play)cout<<"play.cpp:handle_event\n";
			pacman->changeSpeed(e);
			if(e.type==SDL_QUIT){
				*state=5;
			}
			else if(e.type==SDL_MOUSEBUTTONDOWN){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					buttons[i]->handle_event(state,m,music_on,e);
				}
			}
			else if(e.type==SDL_KEYDOWN){
				if(e.key.keysym.sym==SDLK_ESCAPE){
					*state=5;
				}
				else if(e.key.keysym.sym==SDLK_p){
					*state=2;
				}
			}
		}
		string getPlayerState(){
			return pacman->getPlayerState();
		}
		
		void addPlayer(string s){

			pacman2 = new Character("./../assets/corona.bmp",renderer,50,10,false);
 
		}

	private:
	
		int locatePointer(int a,int b){
			if (debug_play)cout<<"play.cpp:locatePointer\n";
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		bool collidePlayer(){
			if (debug_play)cout<<"play.cpp:collidePlayer\n";
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					if(maze->mazeData[(pacman->x+pacman->width+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==1){
						return false;
					}else{
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x-1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==1){
						return false;
					}else{
						return true;
					}
				}
			}else{
				if(pacman->y_speed>0){
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height+1)/(maze->mazeCell.h)]==1){
						return false;
					}else{
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y-1)/(maze->mazeCell.h)]==1){
						return false;
					}else{
						return true;
					}
				}
			}
		} 
};
