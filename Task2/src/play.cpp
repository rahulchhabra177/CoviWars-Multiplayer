#include "button.h";
#include "scoreboard.h";
#include "maze.h";
#include "menu.cpp";
#include<time.h>

using namespace std;

class play{
	
	public:
	
		char* name;
		int lvl;
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
		bool winCondition=false;
		bool isServer=false;
		bool multiplayer=false;
		vector<vector<int>> occupied;
		bool keyPlaced=false;
		bool fruitPlaced=false;
		bool vaccinePlaced=false;
		bool fruit2Placed=false;

		
		play(char* title,int level,SDL_Texture* poster, SDL_Renderer* localRenderer,Menu* menu,bool multi,string mzData=""){
			if (play_debug)cout<<"play.cpp:play\n";
			menu_n=menu;
			name = title;
			lvl = level;
			multiplayer = multi;
			isServer = (mzData=="");
			background = poster;
			renderer = localRenderer;
			heading=Texture::LoadText("Scoreboard",renderer);
			SDL_Texture* waitback=Texture::LoadT("./../assets/please.jpg",renderer);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer,waitback,NULL,NULL);
			SDL_RenderPresent(renderer);

			int numEnemies = f(lvl);

			for(int i=0;i<numEnemies;i++){
				Enemy* enemy=nullptr;
				enemies.push_back(enemy);
			}
	
			maze = new Maze(lvl,renderer,multi,mzData);
			score = new ScoreBoard(renderer,multi);

			if(mzData=="" || !multiplayer){

				for(int i=0;i<maze->m_width;i++){
					vector<int> v;
					for(int j=0;j<maze->m_height;j++){
						if(i==0 || i==maze->m_width-1 || j==0 || j==maze->m_height-1){
							v.push_back(1);
						}else{
							v.push_back(0);
						}
					}
					occupied.push_back(v);
				}
				
				occupied[1][1]=1;
				
				for(int i=0;i<numEnemies;i++){
					while(true){
						srand(time(0));
						int x = 2*(rand()%(maze->m_width/2))+1;
						int y = 2*(rand()%(maze->m_height/2))+1;
						if(maze->mazeData[x][y]==0 && occupied[x][y]==0){
							enemies[i]=new Enemy(renderer,100*x,100*y,menu_n->s_width);
							occupied[x][y]=1;
							break;
						}
					}
				}

				pacman = new Character("./../assets/corona.bmp",renderer,110,110,false,menu->s_width);

			}else{
				pacman = new Character("./../assets/corona.bmp",renderer,(maze->m_width-2)*100-90,110,false,menu->s_width);
				pacman2 = new Character("./../assets/corona.bmp",renderer,110,110,true,menu_n->s_width);

				int index = 569;
				for(int i=0;i<stoi(mzData.substr(568,1));i++){
					enemies[i] = new Enemy(renderer,stoi(mzData.substr(index,4)),stoi(mzData.substr(index+4,4)),menu_n->s_width);
					index+=8;
				}
			}
		}
		
		void reinitialize(int a,int b){
			
			pacman->x = 110;
			pacman->y = 110;
			pacman->score = 0;
			score->time_string = "00:00";
			maze->reinitialize();
			enemyReinitialize(a,b);
			
		}
		
		void enemyReinitialize(int a,int b){

			for(int i=0;i<maze->m_width;i++){
				for(int j=0;j<maze->m_height;j++){
					if(i==0 || i==maze->m_width-1 || j==0 || j==maze->m_height-1){
						occupied[i][j]=1;
					}else{
						occupied[i][j]=0;
					}
				}
			}
			
			occupied[1][1]=1;
			occupied[a/100][b/100]=1;
			occupied[a/100-1][b/100]=1;
			occupied[a/100+1][b/100]=1;
			occupied[a/100][b/100-1]=1;
			occupied[a/100][b/100+1]=1;

			for(int i=0;i<enemies.size();i++){
				while(true){
					srand(time(0));
					int x = 2*(rand()%((maze->m_width-1)/2))+1;
					int y = 2*(rand()%((maze->m_height-1)/2))+1;
					if(maze->mazeData[x][y]!=1 && occupied[x][y]==0){
						enemies[i]->x = 100*x;
						enemies[i]->y = 100*y;
						occupied[x][y]=1;
						break;
					}
				}
			}
		}
		
		void render(){
			if (play_debug)cout<<"play.cpp:render\n";
			SDL_RenderCopy(renderer,background,NULL,NULL);
			score->render();
			pacman->render(renderer);
			if (pacman2!=nullptr){
				pacman2->render(renderer);
			}
			maze->render(renderer);
			for(int i=0;i<enemies.size();i++){
				if(enemies[i]->active){
					enemies[i]->render(renderer);
				}
			}
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
		}
		
		void handle_request(string response,int* state,int* prevstate){
			if (play_debug)cout<<"play.cpp:handle_request:"<<response<<"\n";
			if (response==""){
				return;
			}else if(response[0]=='$'){
				pacman2->set_x_y(stoi(response.substr(2,4)),stoi(response.substr(6,4)));
				pacman2->set_speed(stoi(response.substr(1,1)));
				for(int i=0;i<stoi(response.substr(10,1));i++){
					enemies[i]->set_x_y(stoi(response.substr(11+i*8,4)),stoi(response.substr(15+i*8,4)));
				}
			}else if(response[0]=='!'){
				if (pacman2==nullptr){
					cout<<"Pacman Not Initialised\n";
					exit(1);
				}
				pacman2->set_x_y(stoi(response.substr(2,4)),stoi(response.substr(6,4)));
				pacman2->set_speed(stoi(response.substr(1,1)));
			}
			else{
				*prevstate=*state;
				*state=101;

					}	
		}

		void update(int* state,bool doUpdate,SoundClass* m,int* prevstate,network*nmanager){
			if (play_debug)cout<<"play.cpp:update\n";
			maze->update();
			pacman->updateCounter(lvl);
			if(eatEgg(pacman)){
				pacman->score++;
			}
			if(eatFruit(pacman)){
				pacman->isInvincible=true;
				pacman->counter=0;
			}
			if(eatVaccine(pacman)){
				pacman->isVaccinated=true;
				pacman->counter=0;
			}
			if (!multiplayer && eatKey(pacman)){
				maze->keyEaten=true;
				if(!multiplayer){
				maze->setWinCondition();
		}
			}

			if(!multiplayer && pacman->score>(88*maze->numEggs)/100 && !keyPlaced){
				maze->placeKey();
				keyPlaced=true;

			}
			if(pacman->score>(2*maze->numEggs)/5 && !vaccinePlaced){
				maze->placeVaccine();
				vaccinePlaced=true;

			}
			if( pacman->score>(1*maze->numEggs)/4 && !fruitPlaced){
				maze->placeFruits();
				fruitPlaced=true;

			}if(pacman->score>(5*maze->numEggs)/7 && !fruit2Placed){
				maze->placeFruits();
				fruit2Placed=true;

			}
			
			if(pacman2!=nullptr){
				pacman2->updateCounter(lvl);
				if(eatEgg(pacman2)){
					pacman2->score++;
				}
				if(eatFruit(pacman2)){
					pacman2->isInvincible=true;
					pacman2->counter=0;
				}
				if(eatVaccine(pacman2)){
					pacman2->isVaccinated=true;
					pacman2->counter=0;
				}
			}
			if(multiplayer){
				if(nmanager->connected && nmanager->isPlaying && !isServer){
					nmanager->send("!"+pacman->getPlayerState(),state,prevstate);
					string response=nmanager->receive(11+8*(enemies.size()),state,prevstate);
					handle_request(response,state,prevstate);
				}else if (nmanager->connected && nmanager->isPlaying && isServer){
					string enemyState="";
					for (int i=0;i<enemies.size();i++){
						enemyState+=enemies[i]->getEnemyState();
					}
					nmanager->send("$"+pacman->getPlayerState()+to_string(enemies.size())+enemyState,state,prevstate);
					string response=nmanager->receive(10,state,prevstate);
					cout<<"handle\n";
					handle_request(response,state,prevstate);
					cout<<"request handled\n";
				}
			}
			if (menu_n->cur_player!=""){
				score->update(1,menu_n->cplayer,pacman->score,"",0);
			}else{
				if(pacman2!=nullptr){
					score->update(1,"Player1",pacman->score,"Player2",0);
				}else{
					score->update(1,"Player1",pacman->score,"",0);
				}
			}
			if(!collidePlayer()){
				pacman->updatePlayer(nmanager,false);
			}
			if(pacman2!=nullptr){
				pacman2->updatePlayer(nmanager,true);
			}
			if(!multiplayer){
				if(maze->mazeData[pacman->x/100][pacman->y/100]==3){
					winCondition = true;
				}
				if(winCondition){
					if(maze->lvl<5){
						*state=-3;
					}else{
						*state=5;
					}
				}
			}
			for(int i=0;i<enemies.size();i++){
				if(enemies[i]->active){
					if(pacman->collide(enemies[i],m)){
						if(pacman->isInvincible || pacman->isVaccinated){
							if(pacman->isVaccinated){
								enemies[i]->active=false;
							}
						}else{
							m->PlaySound("collision");
							*state=4;
						}
					}
					if(pacman2!=nullptr){
						if(enemies[i]->active){
							if(pacman2->collide(enemies[i],m)){
								if(pacman2->isInvincible || pacman2->isVaccinated){
									if(pacman2->isVaccinated){
										enemies[i]->active = false;
									}
								}else{
									m->PlaySound("collision");
									*state=5;
								}
							}
						}
					}
					if(enemies[i]->active){	
						enemyAI(i);
					}
				}	
			}
		}
		
		void handle_event(SDL_Event e,int* state,SoundClass* m,bool music_on,network* nmanager){
			if (play_debug)cout<<"play.cpp:handle_event\n";
			pacman->changeSpeed(e,nmanager);
			if(e.type==SDL_QUIT){
				*state=6;				//TODO:Change here for synchronised exit in multiplayer
			}else if(e.type==SDL_MOUSEBUTTONDOWN){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					//buttons[i]->handle_event(state,m,prevstate,e);
				}
			}else if(e.type==SDL_KEYDOWN && !multiplayer){
				if(e.key.keysym.sym==SDLK_ESCAPE){
					*state=6;
				}else if(e.key.keysym.sym==SDLK_p){
					*state=2;
				}
			}
		}

		string getEnemiesPos(){
			string enemy_state="";
			for(int i=0;i<enemies.size();i++){
				enemy_state+=enemies[i]->getEnemyState();
			}
			return enemy_state;
		}
		
		string getPlayState(){
			return maze->getMazeState()+to_string(enemies.size())+getEnemiesPos();
		}
		
		void addPlayer(){
			pacman2 = new Character("./../assets/corona.bmp",renderer,(maze->m_width-2)*100-90,110,true,menu_n->s_width);
		}

	private:

		int f(int n){
			return 2*n;
		}

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
			int x = pacman->x;
			int y = pacman->y;
			int pw = pacman->width;
			int ph = pacman->height;
			int w = maze->mazeCell.w;
			int h = maze->mazeCell.h;
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					bool check1 = maze->mazeData[(x+pw)/w][y/h]!=1;
					bool check2 = maze->mazeData[(x+pw)/w][(y+ph-1)/h]!=1;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(x%w==0){
						bool check1 = maze->mazeData[(x-1)/w][y/h]!=1;
						bool check2 = maze->mazeData[(x-1)/w][(y+ph-1)/h]!=1;
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
					bool check1 = maze->mazeData[x/w][(y+ph)/h]!=1;
					bool check2 = maze->mazeData[(x+pw-1)/w][(y+ph)/h]!=1;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					if(y%h==0){
						bool check1 = maze->mazeData[x/w][(y-1)/h]!=1;
						bool check2 = maze->mazeData[(x+pw-1)/w][(y-1)/h]!=1;
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
		
		bool eatEgg(Character* pacman){
			if (play_debug)cout<<"play.cpp:collidePlayer\n";
			
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					if(maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==0){
						maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
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
				}else{
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]==0){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}
			return false;
		}

		bool eatFruit(Character* pacman){
			if (play_debug)cout<<"play.cpp:collidePlayer\n";
			
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					if(maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==4){
						maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==4){
						maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}else{
				if(pacman->y_speed>0){
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]==4){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]==4){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}
			return false;
		}

		bool eatVaccine(Character* pacman){
			if (play_debug)cout<<"play.cpp:collidePlayer\n";
			
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					if(maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==5){
						maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==5){
						maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}else{
				if(pacman->y_speed>0){
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]==5){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]==5){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}
			return false;
		}



		bool eatKey(Character* pacman){
			if (play_debug)cout<<"play.cpp:collidePlayer\n";
			
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					if(maze->mazeData[(pacman->x+pacman->width/30+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==6){
						maze->mazeData[(pacman->x+pacman->width/30+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x+(pacman->width)/30)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==6){
						maze->mazeData[(pacman->x+(pacman->width)/30)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}else{
				if(pacman->y_speed>0){
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/30+1)/(maze->mazeCell.h)]==6){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/30+1)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/30))/(maze->mazeCell.h)]==6){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/30))/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}
			return false;
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
				if(maze->mazeData[x/100-1][y/100]!=1){
					unvisited.push_back(0);
				}
				if(maze->mazeData[x/100][y/100+1]!=1){
					unvisited.push_back(1);
				}
				if(maze->mazeData[x/100+1][y/100]!=1){
					unvisited.push_back(2);
				}
				if(maze->mazeData[x/100][y/100-1]!=1){
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
					bool check1 = maze->mazeData[(x+pw)/w][y/h]!=1;
					bool check2 = maze->mazeData[(x+pw)/w][(y+ph-1)/h]!=1;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					bool check1 = maze->mazeData[(x-1)/w][y/h]!=1;
					bool check2 = maze->mazeData[(x-1)/w][(y+ph-1)/h]!=1;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}	
				}
			}else{
				if(enemies[i]->y_speed>0){
					bool check1 = maze->mazeData[x/w][(y+ph)/h]!=1;
					bool check2 = maze->mazeData[(x+pw-1)/w][(y+ph)/h]!=1;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}else{
					bool check1 = maze->mazeData[x/w][(y-1)/h]!=1;
					bool check2 = maze->mazeData[(x+pw-1)/w][(y-1)/h]!=1;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}
			}
		}
};
