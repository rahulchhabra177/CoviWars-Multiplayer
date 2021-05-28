#include "character.h";
#include "button.h";
#include "Texture.h";
#include "maze.h";
using namespace std;


class play{
	
	public:
	
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Renderer* renderer;
		int s_width,s_height;
		
		//SDL_Texture* heading = Texture::LoadText("Scoreboard",renderer);
		
		Maze* maze=nullptr;
		Character* pacman=nullptr;
		vector<Character*> players;
		vector<Enemy*> enemies;
		//ScoreBoard* score=nullptr;
		//SDL_Rect* dst_hdng;
		
		play(char* title,int numEnemies,SDL_Texture* poster, SDL_Renderer* localRenderer,int width,int height){
			name = title;
			background = poster;
			renderer = localRenderer;
			s_width = width;
			s_height = height;
			
			for(int i=0;i<numEnemies;i++){
				Enemy* enemy=nullptr;
				enemies.push_back(enemy);
			}
			
			for(int i=0;i<numEnemies;i++){
				enemies[i]=new Enemy(renderer,1000,1000);
			}
			
			pacman = new Character("./../assets/hero.bmp",renderer,120,120);
			
			maze = new Maze(1,renderer);
			players.push_back(pacman);
			//score = new ScoreBoard(players,renderer);
		}
		
		void render(){
			SDL_RenderCopy(renderer,background,NULL,NULL);
			//score->render();
			pacman->render(renderer);
			maze->render(renderer);
			for(int i=0;i<enemies.size();i++){
				enemies[i]->render(renderer);
			}
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void update(int* state,bool doUpdate,SoundClass* m,bool music_on){
			maze->update();
			//score->update();
			if(!collidePlayer()){
				pacman->updatePlayer();
			}
			for(int i=0;i<enemies.size();i++){
				if(pacman->collide(enemies[i],m,music_on)){
					*state = 4;
				}	
			}
		}
		
		void handle_event(SDL_Event e,int* state,SoundClass* m,bool music_on){
			pacman->changeSpeed(e);
			if(e.type==SDL_QUIT){
				*state=5;
			}else if(e.type==SDL_MOUSEBUTTONDOWN){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					buttons[i]->handle_event(state,m,music_on);
				}
			}else if(e.type==SDL_KEYDOWN){
				if(e.key.keysym.sym==SDLK_ESCAPE){
					*state=5;
				}else if(e.key.keysym.sym==SDLK_p){
					*state=2;
				}
			}
		}
		
	private:
	
		int locatePointer(int a,int b){
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		bool collidePlayer(){
			int x = pacman->x;
			int y = pacman->y;
			int pw = pacman->width;
			int ph = pacman->height;
			int w = maze->mazeCell.w;
			int h = maze->mazeCell.h;
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					bool check1 = maze->mazeData[x/w+1][y/h]==0;
					bool check2 = maze->mazeData[x/w+1][(y+ph)/h]==0;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(x%w==0){
						bool check1 = maze->mazeData[x/w-1][y/h]==0;
						bool check2 = maze->mazeData[x/w-1][(y+ph)/h]==0;
						if(check1 && check2){
							return false;
						}else{
							return true;
						}
					}else{
						return false;
					}
				}
			}else{
				if(pacman->y_speed>0){
					bool check1 = maze->mazeData[x/w][y/h+1]==0;
					bool check2 = maze->mazeData[(x+pw)/w][y/h+1]==0;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(y%h==0){
						bool check1 = maze->mazeData[x/w][y/h-1]==0;
						bool check2 = maze->mazeData[(x+pw)/w][y/h-1]==0;
						if(check1 && check2){
							return false;
						}else{
							return true;
						}
					}else{
						return false;
					}
				}
			}
		} 
};
