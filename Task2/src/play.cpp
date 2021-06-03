#include "character.h";
#include "button.h";
#include "Texture.h";
#include "maze.h";
#include <time.h>
using namespace std;


class play{
	
	public:
	
		char* name;
		int lvl;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Renderer* renderer;
		int s_width,s_height;
		bool winCondition=false;
		
		//SDL_Texture* heading = Texture::LoadText("Scoreboard",renderer);
		
		Maze* maze=nullptr;
		Character* pacman=nullptr;
		vector<Character*> players;
		vector<Enemy*> enemies;
		vector<vector<int>> occupied;
		//ScoreBoard* score=nullptr;
		//SDL_Rect* dst_hdng;
		
		play(char* title,int level,SDL_Texture* poster, SDL_Renderer* localRenderer,int width,int height){
			winCondition=false;
			name = title;
			background = poster;
			renderer = localRenderer;
			s_width = width;
			s_height = height;
			lvl = level;

			for(int i=0;i<lvl;i++){
				Enemy* enemy=nullptr;
				enemies.push_back(enemy);
			}
			
			pacman = new Character("./../assets/hero.bmp",renderer,110,110);
			
			maze = new Maze(lvl,renderer);
			players.push_back(pacman);
			
			for(int i=0;i<maze->m_width;i++){
				vector<int> v;
				for(int j=0;j<maze->m_height;j++){
					v.push_back(0);
				}
				occupied.push_back(v);
			}
			
			occupied[1][1]=1;
			
			for(int i=0;i<lvl;i++){
				while(true){
					srand(time(0));
					int x = 2*(rand()%((maze->m_width-1)/2))+1;
					int y = 2*(rand()%((maze->m_height-1)/2))+1;
					if(maze->mazeData[x][y]==0 && occupied[x][y]==0){
						enemies[i]=new Enemy(renderer,100*x,100*y);
						occupied[x][y]=1;
						break;
					}
				}
			}
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
			if(maze->mazeData[pacman->x/100][pacman->y/100]==3){
				winCondition = true;
			}
			for(int i=0;i<enemies.size();i++){
				if(pacman->collide(enemies[i],m,music_on)){
					*state = 4;
				}
				enemyAI(i);	
			}
			if(winCondition){
				if(maze->lvl<5){
					*state=-2;
				}else{
					*state=5;
				}
			}
		}
		
		void handle_event(SDL_Event e,int* state,SoundClass* m,bool music_on){
			pacman->changeSpeed(e);
			if(e.type==SDL_QUIT){
				*state=6;
			}else if(e.type==SDL_MOUSEBUTTONDOWN){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					buttons[i]->handle_event(state,m,music_on);
				}
			}else if(e.type==SDL_KEYDOWN){
				if(e.key.keysym.sym==SDLK_ESCAPE){
					*state=6;
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
					bool check1 = maze->mazeData[x/w+1][y/h]==0 || maze->mazeData[x/w+1][y/h]==3;
					bool check2 = maze->mazeData[x/w+1][(y+ph-1)/h]==0 || maze->mazeData[x/w+1][(y+ph-1)/h]==3;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(x%w==0){
						bool check1 = maze->mazeData[x/w-1][y/h]==0 || maze->mazeData[x/w-1][y/h]==3;
						bool check2 = maze->mazeData[x/w-1][(y+ph-1)/h]==0 || maze->mazeData[x/w-1][(y+ph-1)/h]==3;
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
					bool check1 = maze->mazeData[x/w][y/h+1]==0 || maze->mazeData[x/w][y/h+1]==3;
					bool check2 = maze->mazeData[(x+pw-1)/w][y/h+1]==0 || maze->mazeData[(x+pw-1)/w][y/h+1]==3;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(y%h==0){
						bool check1 = maze->mazeData[x/w][y/h-1]==0 || maze->mazeData[x/w][y/h-1]==3;
						bool check2 = maze->mazeData[(x+pw-1)/w][y/h-1]==0 || maze->mazeData[(x+pw-1)/w][y/h-1]==3;
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
		
		void enemyAI(int i){
			Enemy* enemy = enemies[i];
			if(enemy->x%100==0 && enemy->y%100==0){
				int x = enemy->x;
				int y = enemy->y;
				int pw = enemy->width;
				int ph = enemy->height;
				int prevDirection;
				int nextDirection;
				if(enemy->x_speed>0){
					prevDirection=2;	
				}else if(enemy->x_speed<0){
					prevDirection=0;
				}else if(enemy->y_speed>0){
					prevDirection=1;
				}else{
					prevDirection=3;
				}
				vector<int> unvisited;
				if(maze->mazeData[x/100-1][y/100]==0){
					unvisited.push_back(0);
				}
				if(maze->mazeData[x/100][y/100+1]==0){
					unvisited.push_back(1);
				}
				if(maze->mazeData[x/100+1][y/100]==0){
					unvisited.push_back(2);
				}
				if(maze->mazeData[x/100][y/100-1]==0){
					unvisited.push_back(3);
				}
				srand(time(0));
				int n = unvisited.size();
				if(n==1){
					nextDirection = unvisited[0];
				}else{
					while(true){
						int k = rand()%n;
						if(abs(unvisited[k]-prevDirection)!=2){
							nextDirection = unvisited[k];
							break;
						}
					}
				}
				if(collideEnemy(i)){
					switch(nextDirection){
						case 0:{enemies[i]->x_speed=(-1)*enemies[i]->speed;enemies[i]->y_speed=0;break;}
						case 1:{enemies[i]->x_speed=0;enemies[i]->y_speed=enemies[i]->speed;break;}
						case 2:{enemies[i]->x_speed=enemies[i]->speed;enemies[i]->y_speed=0;break;}
						case 3:{enemies[i]->x_speed=0;enemies[i]->y_speed=(-1)*enemies[i]->speed;break;}
					}
				}else{
					if(n>2){
						switch(nextDirection){
							case 0:{enemies[i]->x_speed=(-1)*enemies[i]->speed;enemies[i]->y_speed=0;break;}
							case 1:{enemies[i]->x_speed=0;enemies[i]->y_speed=enemies[i]->speed;break;}
							case 2:{enemies[i]->x_speed=enemies[i]->speed;enemies[i]->y_speed=0;break;}
							case 3:{enemies[i]->x_speed=0;enemies[i]->y_speed=(-1)*enemies[i]->speed;break;}
						}	
					}
				}
			}
			enemies[i]->updateEnemy();
		}

		bool collideEnemy(int i){
			int x = enemies[i]->x;
			int y = enemies[i]->y;
			int pw = enemies[i]->width;
			int ph = enemies[i]->height;
			int w = maze->mazeCell.w;
			int h = maze->mazeCell.h;
			if(enemies[i]->x_speed!=0){
				if(enemies[i]->x_speed>0){
					bool check1 = maze->mazeData[(x+pw)/w][y/h]==0;
					bool check2 = maze->mazeData[(x+pw)/w][(y+ph-1)/h]==0;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(x%w==0){
						bool check1 = maze->mazeData[(x-1)/w][y/h]==0;
						bool check2 = maze->mazeData[(x-1)/w][(y+ph-1)/h]==0;
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
				if(enemies[i]->y_speed>0){
					bool check1 = maze->mazeData[x/w][(y+ph)/h]==0;
					bool check2 = maze->mazeData[(x+pw-1)/w][(y+ph)/h]==0;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(y%h==0){
						bool check1 = maze->mazeData[x/w][(y-1)/h]==0;
						bool check2 = maze->mazeData[(x+pw-1)/w][(y-1)/h]==0;
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
