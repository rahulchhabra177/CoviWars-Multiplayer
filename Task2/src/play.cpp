#include "button.h";
#include "scoreboard.h";
#include "maze.h";
#include "menu.cpp";

using namespace std;

class play{
	
	public:
	
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Renderer* renderer;
		SDL_Texture *heading=nullptr;
		bool play_debug=true;
		Maze* maze=nullptr;
		Character* pacman=nullptr,*pacman2=nullptr;
		ScoreBoard *score=nullptr;
		vector<Enemy*> enemies;
		SDL_Rect* dst_hdng;
		Menu* menu_n=nullptr;
		play(char* title,int numEnemies,SDL_Texture* poster, SDL_Renderer* localRenderer,Menu* menu){
			if (play_debug)cout<<"play.cpp:play\n";
			menu_n=menu;

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
			pacman = new Character("./../assets/corona.bmp",renderer,20,20,false);
			
			maze = new Maze(1,renderer);
			vector<Character*> temp;
			temp.push_back(pacman);
			// 
			score=new ScoreBoard(temp,renderer);
			// cout<<5;
// 



		}
		
		void render(){
			if (play_debug)cout<<"play.cpp:render\n";
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
			if (play_debug)cout<<"play.cpp:update\n";
			maze->update();
			if (menu_n->cur_player!=""){
			score->update(1,menu_n->cplayer,pacman->score,"",0);
			}
			else{
			score->update(1,"Player1",pacman->score,"",0);

			}
			if( (collidePlayer()) ){
				pacman->updatePlayer(nmanager,false);
				if (pacman2!=nullptr){
				pacman2->updatePlayer(nmanager,true);
				}	

			}
			if (eatEgg()){
				pacman->score++;
			}
			for(int i=0;i<enemies.size();i++){
				if(pacman->collide(enemies[i],m,music_on)){
					*state = 4;
				}	
			}
		}
		
		void handle_event(SDL_Event e,int* state,SoundClass* m,bool music_on,network* nmanager){
			if (play_debug)cout<<"play.cpp:handle_event\n";
			pacman->changeSpeed(e,nmanager);
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
			if (play_debug)cout<<"play.cpp:locatePointer\n";
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		bool collidePlayer(){
			if (play_debug)cout<<"play.cpp:collidePlayer\n";
			cout<<0<<"\n";
			if (pacman==nullptr){cout<<"hehhehe\n";}
			else{cout<<"ho"<<pacman->x_speed<<":"<<pacman->y_speed<<"\n";}

			if(pacman->x_speed!=0){
				cout<<1;
				if(pacman->x_speed>0){
					cout<<11;
					if(maze->mazeData[(pacman->x+pacman->width+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==1){
						cout<<111;
						return false;
					}else{
					cout<<112;
						return true;
					}
				}else{
					cout<<12;
					if(maze->mazeData[(pacman->x-1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==1){
						cout<<121;
						return false;
					}else{
						cout<<122;
						return true;
					}
				}
			}else{
				cout<<2;
				if(pacman->y_speed>0){
					cout<<21;
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height+1)/(maze->mazeCell.h)]==1){
						cout<<211;
						return false;
					}else{
						cout<<212;
						return true;
					}
				}else{
					cout<<22;
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y-1)/(maze->mazeCell.h)]==1){
						cout<<221;
						return false;
					}else{
						cout<<222;
						return true;
					}
				}
			}
		return true;
		} 
bool eatEgg(){
			if (play_debug)cout<<"play.cpp:collidePlayer\n";
			
			if(pacman->x_speed!=0){
				cout<<1;
				if(pacman->x_speed>0){
					cout<<11;
					if(maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==0){
						maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}
				else{
					if(maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==0){
						maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
			}
		}else{
				if(pacman->y_speed>0){
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]==0){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]=2;
						return true;
					}

				}
				else{
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]==0){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}
			return false;
		} 


};
