#include "./../button/button.h";
#include "./../scoreboard/scoreboard.h";
#include "./../maze/maze.h";
#include "./../menu/menu.cpp";
#include<time.h>

using namespace std;

class play{
	
	public:
	
		//Null initialisations of member variables for global access
		char* name;
		int lvl;
		vector<Button*> buttons;
		SDL_Texture* background;
		SDL_Renderer* renderer;
		SDL_Texture *heading=nullptr;
		bool play_debug=false;
		Maze* maze=nullptr,*maze_copy=nullptr;
		Character* pacman=nullptr,*pacman2=nullptr,*fireball=nullptr;
		ScoreBoard *score=nullptr;
		vector<Enemy*> enemies;
		SDL_Rect* dst_hdng;
		Menu* menu_n=nullptr;
		bool winCondition=false;
		bool isServer=false;
		bool multiplayer=false;
		vector<vector<int>> occupied;
		bool keyPlaced = false;
		int numFruitsPlaced=0;
		vector<bool> fruits;
		int numVaccinesPlaced=0;
		vector<bool> vaccines;
		int numMasksPlaced=0;
		vector<bool> masks;
		int numEnemiesPlaced=0;
		vector<bool> extra_enemies;
		vector<SDL_Texture*> texture_e;     	
		vector<SDL_Texture*> texture_e0;				
		vector<SDL_Texture*> texture_e1;
		vector<SDL_Texture*> texture_e2;
		vector<SDL_Texture*> texture_e3;
		SDL_Texture* texture_p[4][8]={NULL};
		SDL_Texture* texture_pv[4][8]={NULL};
		SDL_Texture* texture_pa[4][8]={NULL};
		SDL_Texture* texture_ball[2]={NULL};
		int numFballs=10;
		string pl2name="Client";
		int nextEnemy=0;
		int scoreCounter1=0;
		int scoreCounter2=0;

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
			SDL_Texture* waitback=Texture::LoadT("./../assets/backgrounds/please.jpg",renderer);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer,waitback,NULL,NULL);
			SDL_RenderPresent(renderer);

			int numEnemies = f(lvl);
			//Multiple textures(here 8) of the enemy for animation effect
			for (int i=0;i<8;i++){
				string path="./../assets/enemy/corona"+to_string(i)+".png";
				char* a=&path[0];
				texture_e.push_back(Texture::LoadT(a,localRenderer));
			}
			for (int i=0;i<8;i++){
				string path="./../assets/enemy/corona2.png";
				char* a=&path[0];
				texture_e0.push_back(Texture::LoadT(a,localRenderer));
			}
			for (int i=0;i<8;i++){
				string path="./../assets/enemy/corona0.png";
				char* a=&path[0];
				texture_e1.push_back(Texture::LoadT(a,localRenderer));
			}
			for (int i=0;i<8;i++){
				string path="./../assets/enemy/corona1.png";
				char* a=&path[0];
				texture_e2.push_back(Texture::LoadT(a,localRenderer));
			}
			for (int i=0;i<8;i++){
				string path="./../assets/enemy/corona3.png";
				char* a=&path[0];
				texture_e3.push_back(Texture::LoadT(a,localRenderer));
			}

			//Initialising textures for our main character(pacman), one for each 
			//direction in which it will be moving. We have also animated the pacman
			//so each direction will also have several textures(here 8), for a total
			//of 32 textures. 
			for (int i=0;i<4;i++){
				for (int j=0;j<8;j++){
					string path="./../assets/coviwars/normal/pac"+to_string(i)+to_string(j%2+1)+".png";
					char* a=&path[0];
					texture_p[i][j]=Texture::LoadT(a,localRenderer);
				}
			}
			for (int i=0;i<4;i++){
				for (int j=0;j<8;j++){
					string path="./../assets/coviwars/vaccinated/pacvac"+to_string(i)+to_string(j%2+1)+".png";
					char* a=&path[0];
					texture_pv[i][j]=Texture::LoadT(a,localRenderer);
				}
			}
			for (int i=0;i<4;i++){
				for (int j=0;j<8;j++){
					string path="./../assets/coviwars/invincible/pacapp"+to_string(i)+to_string(j%2+1)+".png";
					char* a=&path[0];
					texture_pa[i][j]=Texture::LoadT(a,localRenderer);
				}
			}
			for (int i=0;i<2;i++){
					string path="./../assets/maze_items/fireball"+to_string(i)+".png";
					char* a=&path[0];
					texture_ball[i]=Texture::LoadT(a,localRenderer);
			}

			if(!multiplayer){
				for(int i=0;i<numEnemies*4;i++){
					Enemy* enemy=nullptr;
					enemies.push_back(enemy);
				}
			}else{
				for(int i=0;i<numEnemies*2;i++){
					Enemy* enemy=nullptr;
					enemies.push_back(enemy);
				}
			}
	
			maze = new Maze(lvl,renderer,multi,mzData);
			maze_copy = maze;
			score = new ScoreBoard(renderer,multi);
			if(mzData=="" || !multiplayer){
				
				//In case of a single player game or server in a multiplayer
				//game, the enemies are randomly initialised on the empty 
				//cells of the maze.
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
				
				//The 2D vector 'occupied' stores which cells are available
				//for enemies to spawn, because enemies cannot spawn on walls
				//or directly on players to give the player a fair chance to win
				occupied[1][1]=1;
				
				if(!multiplayer){
					for(int i=0;i<numEnemies*4;i++){
						while(true){
							srand(time(0));
							int x = 2*(rand()%(maze->m_width/2))+1;
							int y = 2*(rand()%(maze->m_height/2))+1;
							if(maze->mazeData[x][y]==0 && occupied[x][y]==0 && (!x<menu_n->s_width/3 || !y<menu_n->s_height/3)){
								vector<SDL_Texture*> newTexture;
								switch(i){
									case 0:{newTexture=texture_e0;break;}
									case 1:{newTexture=texture_e1;break;}
									case 2:{newTexture=texture_e2;break;}
									case 3:{newTexture=texture_e3;break;}
								}
								enemies[i]=new Enemy(renderer,i,100*x,100*y,menu_n->s_width,newTexture);
								occupied[x][y]=1;
								break;
							}
						}
					}
				}else{
					for(int i=0;i<numEnemies*2;i++){
						while(true){
							srand(time(0));
							int x = 2*(rand()%(maze->m_width/2))+1;
							int y = 2*(rand()%(maze->m_height/2))+1;
							if(maze->mazeData[x][y]==0 && occupied[x][y]==0 && !y<(3*menu_n->s_height)/4){
								enemies[i]=new Enemy(renderer,100*x,100*y,menu_n->s_width,texture_e);
								occupied[x][y]=1;
								break;
							}
						}
					}
				}

				//In case of server and in single player game, only the local
				//pacman is rendered initially, and in server, other players
				//are rendered only after they have joined the network hosted
				//by the server
				pacman = new Character("./../assets/corona.bmp",renderer,100,100,false,menu->s_width,texture_p,texture_pv,texture_pa);
				pacman->name=menu_n->cplayer;

				while (pacman->name.size()!=0 && pacman->name[pacman->name.size()-1]==' '){
					pacman->name.pop_back();
				}
				if (pacman->name==""){
					pacman->name="Player 1 ";
				}
				for (int i=0;i<maze->numFruits;i++){
					fruits.push_back(false);
				}
				for (int i=0;i<maze->numVaccines;i++){
					vaccines.push_back(false);
				}
				for (int i=0;i<maze->numMasks;i++){
					masks.push_back(false);
				}
				for (int i=0;i<maze->extra_enemies;i++){
					extra_enemies.push_back(false);
				}
			}else{

				//In case of a client, no initialisations of the enemies or
				//the maze are required as they can be received from the server
				//which has already created the. Only the local pacman is created
				//and its information is sent to the server through the network
				//manager. So, each server or client controls the movement of its 
				//own character and sends its information like location and
				//speed to other players so that the game state is synchronised
				
				//Creating both the local and non-local pacman(created by server)
				pacman = new Character("./../assets/corona.bmp",renderer,(maze->m_width-2)*100-100,100,false,menu->s_width,texture_p,texture_pv,texture_pa);
				pacman->name=menu_n->cplayer;
				while (pacman->name.size()!=0 && pacman->name[pacman->name.size()-1]==' '){
					pacman->name.pop_back();
				}
				if (pacman->name==""){
					pacman->name="Player 1 ";
				}
				pacman2 = new Character("./../assets/corona.bmp",renderer,100,100,true,menu_n->s_width,texture_p,texture_pv,texture_pa);
				pacman2->name=mzData.substr(585,10);
				while (pacman2->name.size()!=0 && pacman2->name[pacman2->name.size()-1]==' '){
					pacman2->name.pop_back();
				}
				if (pacman2->name==""){
					pacman2->name="Player 2 ";
				}
				//Importing the location of enemies
				int index = 569;
				for(int i=0;i<stoi(mzData.substr(568,1));i++){
					enemies[i] = new Enemy(renderer,stoi(mzData.substr(index,4)),stoi(mzData.substr(index+4,4)),menu_n->s_width,texture_e);
					index+=8;
				}
			}
		}
		
		//To reinitialise the play state in case the player wants to play again
		void reinitialize(int a,int b){
			
			pacman->x = 100;
			pacman->y = 100;
			pacman->score = 0;
			numFballs=10;
			score->time_string = "00:00";
			maze=maze_copy;
			numFruitsPlaced=0;
			numVaccinesPlaced=0;
			numMasksPlaced=0;
			fireball=nullptr;
			for (int i=0;i<maze->numFruits;i++){
					fruits[i]=false;
			}
			for (int i=0;i<maze->numVaccines;i++){
				vaccines[i]=false;
			}
			for (int i=0;i<maze->numMasks;i++){
				masks[i]=false;
			}
			for (int i=0;i<maze->extra_enemies;i++){
				extra_enemies[i]=false;
			}
			enemyReinitialize(a,b);
			numEnemiesPlaced=0;
			
		}
		
		//Reinitialising the enemies, same procedure as the constructor
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
			for(int i=0;i<numEnemiesPlaced;i++){enemies.pop_back();}
			//This part makes sure that when the play state is recreated, the 
			//enemies are not rendered in close proximity to the player, to give
			//the player a fair chance of survival
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
						enemies[i]->active=true;
						enemies[i]->explodeCounter=0;
						occupied[x][y]=1;
						break;
					}
				}
			}
		}
		
		//Local render funtion
		void render(){
			if (play_debug)cout<<"play.cpp:render\n";
			SDL_RenderCopy(renderer,background,NULL,NULL);

			//Note that the order of rendering matters for visibility. If two
			//objects are rendered at the same position on the screen, then the
			//object which is rendered later in the same frame, will be observed 
			//on top of the object which was rendered earlier

			//So, we have rendered the maze before the enemies and the pacman, so that
			//whenever the pacman or the enemies pass through the special cells of 
			//the maze, they pass over them instead of getting shadowed by them
			
			score->render();
			maze->render(renderer);
			for(int i=0;i<enemies.size();i++){
				if(enemies[i]->active){
					enemies[i]->render(renderer);
				}
			}
			pacman->render(renderer);
			if (pacman2!=nullptr){
				pacman2->render(renderer);
			}
			for(int i=0;i<buttons.size();i++){
				buttons[i]->render(renderer);
			}
			while (pacman2!=nullptr && pacman2->name.size()!=0 && pacman2->name[pacman2->name.size()-1]==' '){
				pacman2->name.pop_back();
			}
			if (pacman2!=nullptr && pacman2->name==""){
				pacman2->name="Player 2";
			}
			if (fireball!=nullptr){
				fireball->render(renderer);
			}
			if (play_debug)cout<<"play.cpp:render\n";
		}
		
		//This helper function manages the requests and responses for 
		//data transfer between the server and the client(s) 
		void handle_request(string response,int* state,int* prevstate){
			if (play_debug)cout<<"play.cpp:handle_request:"<<response<<"\n";
			
			//An empty string means no request/response
			if (response==""){
				return;

			//A string starting with '$' means a response to a request which
			//demands the data of non-local pacman and the enemies
			}
			*prevstate=0;
			if(response[0]=='$'){
				pacman2->set_x_y(stoi(response.substr(2,4)),stoi(response.substr(6,4)));
				pacman2->set_speed(stoi(response.substr(1,1)));
				for(int i=0;i<stoi(response.substr(10,1));i++){
					enemies[i]->set_x_y(stoi(response.substr(11+i*8,4)),stoi(response.substr(15+i*8,4)));
				}

			//A string starting with '!' means a request for data of the 
			//non -local pacman
			}else if(response[0]=='!'){
				if (pacman2==nullptr){
					cout<<"Pacman Not Initialised\n";
					exit(1);
				}
				pacman2->set_x_y(stoi(response.substr(2,4)),stoi(response.substr(6,4)));
				pacman2->set_speed(stoi(response.substr(1,1)));
			}else{
				*prevstate=*state;
				*state=101;
			}	
		}

		//Local update function for play state
		void update(int* state,bool doUpdate,SoundClass* m,int* prevstate,network*nmanager){
			if (play_debug)cout<<"play.cpp:update\n";
			maze->update();

			//Checking the current status of main(local) pacman
			pacman->updateCounter(lvl);
			checkQuarantine(pacman);
			if (!multiplayer && numFruitsPlaced<maze->numFruits &&  pacman->score > ((numFruitsPlaced+1)*maze->numEggs)/maze->numFruits && !fruits[numFruitsPlaced]){
				maze->placeFruits();
				fruits[numFruitsPlaced]=true;
				numFruitsPlaced++;
			}

			if (!multiplayer && numVaccinesPlaced<maze->numVaccines &&  pacman->score > ((numVaccinesPlaced+1)*maze->numEggs)/maze->numVaccines && !vaccines[numVaccinesPlaced]){
				maze->placeVaccine();
				vaccines[numVaccinesPlaced]=true;
				numVaccinesPlaced++;
			}

			if (!multiplayer && numMasksPlaced<maze->numMasks && pacman->score > ((numMasksPlaced+1)*maze->numEggs)/maze->numMasks && !masks[numMasksPlaced]){
				maze->placeMasks();
				masks[numMasksPlaced]=true;
				numMasksPlaced++;
			}

			if (!multiplayer && numEnemiesPlaced<maze->extra_enemies && pacman->score > ((numEnemiesPlaced+1)*maze->numEggs)/maze->extra_enemies && !extra_enemies[numEnemiesPlaced]){
				extra_enemies[numEnemiesPlaced]=true;
				placeEnemy();
			}

			if(eatPowerUp(pacman,0)){
				pacman->score++;
				scoreCounter1++;
			}
			if(eatPowerUp(pacman,4)){
				pacman->isInvincible=true;
				if(!pacman->isVaccinated){
					pacman->counter=0;
				}
				m->PlaySound("eatFruit");
			}
			if(eatPowerUp(pacman,5)){
				pacman->isVaccinated=true;
				pacman->isInvincible=false;
				pacman->counter=0;
				m->PlaySound("eatVaccine");
			}
			if(eatPowerUp(pacman,6)){
				pacman->isMasked=true;
			}

			//This option is only available for the single player, as 
			//obtaining a key is a win condition of single player version of this game
			if (!multiplayer && eatPowerUp(pacman,8)){
				maze->keyEaten=true;
				maze->setWinCondition();
				m->PlaySound("pause");
			}

			//The key appears only after the player has reached a minimum score
			if(!multiplayer && (pacman->score*100)>(60*maze->numEggs) && !keyPlaced){
				maze->placeKey();
				keyPlaced=true;
			}

			//Checking the current status of non-local pacman in case of
			//multiplayer 
			if(pacman2!=nullptr){
				checkQuarantine(pacman2);
				pacman2->updateCounter(lvl);
				if(eatPowerUp(pacman2,0)){
					pacman2->score++;
					scoreCounter2++;
				}
				if(eatPowerUp(pacman2,4)){
					pacman2->isInvincible=true;
					pacman2->counter=0;
				}
				if(eatPowerUp(pacman2,5)){
					pacman2->isVaccinated=true;
					pacman2->counter=0;
				}
				if(eatPowerUp(pacman2,6)){
					pacman2->isMasked=true;
				}
			}

			//Update the data requests and their responses between the server
			//and the client in multiplayer mode 
			if(multiplayer){
				if(nmanager->connected && nmanager->isPlaying && !isServer){
					if (*prevstate!=-1){
						nmanager->send("!"+pacman->getPlayerState(),state,prevstate);
					}
					string response=nmanager->receive(11+8*(enemies.size()),state,prevstate);
					handle_request(response,state,prevstate);
				}else if (nmanager->connected && nmanager->isPlaying && isServer){
					string enemyState="";
					for (int i=0;i<enemies.size();i++){
						enemyState+=enemies[i]->getEnemyState();
					}
					if (*prevstate!=-1){
						nmanager->send("$"+pacman->getPlayerState()+to_string(enemies.size())+enemyState,state,prevstate);
					}
					string response=nmanager->receive(10,state,prevstate);
					handle_request(response,state,prevstate);
				}
			}

			//Scoreboard and timer updates
			if (!multiplayer){
				score->update(1,pacman->name,pacman->score,"",0);
			}else{
				if(pacman2!=nullptr){
					score->update(1,pacman->name,pacman->score,pacman2->name,pacman2->score);
				}
			}

			//Checking for collision of the local player will the walls
			if(!collidePlayer(pacman,last_key_x(pacman),last_key_y(pacman)) && !pacman->knockback){
				pacman->x_speed=last_key_x(pacman);
				pacman->y_speed=last_key_y(pacman);
				pacman->cur_dir=pacman->lastKey;
			}

			//Updating the position of all the player characters
			if(!collidePlayer(pacman,pacman->x_speed,pacman->y_speed) || pacman->freeze){
				pacman->updatePlayer(false);
			}else{
				pacman->knockback = false;
				pacman->knockbackCounter = 0;
			}

			if (fireball!=nullptr){
				if (collideProjectile(fireball,fireball->x_speed/5,fireball->y_speed/5)){
					fireball=nullptr;
				}
				else{
				fireball->updatePlayer(false);
				}
			}
			
			if(pacman2!=nullptr){
				pacman2->updatePlayer(true);
			}

			//Checking win conditions for both single and multi player modes
			if(!multiplayer){

				//In single player mode, the player loses if his/her health, 
				//which is the number of tablets/eggs collected(i.e. score),
				//drops below zero
				if(pacman->score<0){
					*state=4;
				}

			}else{

				//In multiplayer mode, the player whose health drops loses and
				//the last player alive automatically wins
				if(pacman->score<0){
					*state=4;
				}else if(pacman2->score<0){
					*state=5;
				}

				//If more than one players are alive when all the tablets/eggs
				//are collected, then the player with greater score wins
				if(scoreCounter1+scoreCounter2==maze->numEggs){
					if(pacman->score>pacman2->score){
						*state=5;
					}else if(pacman->score<pacman2->score){
						*state=4;
					}
				}

			}

			//In single player mode, if the player reaches a particular minimum
			//score, a key and a door appears. The player can unlock this door
			//to the next level only after collecting the key. The player wins
			//after completing all the levels in this fashion.
			if(!multiplayer){
				if(maze->mazeData[pacman->x/100][pacman->y/100]==3){
					winCondition = true;
				}
				if(winCondition){
					if(maze->lvl<5){
						*state=-3;
						return;
					}else{
						*state=5;
						return;
					}
				}
			}

			//Managing the interaction between the player characters and the 
			//different types of enemies
			for(int i=0;i<enemies.size();i++){
				if(enemies[i]->active){

					//In case the player collides with an enemy
					if(pacman->collide(enemies[i],m)){

						//The enemies cannot affect the player if it currently
						//has a powerup
						if(pacman->isInvincible || pacman->isVaccinated){
							if(pacman->isVaccinated){
								enemies[i]->active=false;
							}

						//Otherwise the player collides
						}else{
							m->PlaySound("collision");
							if(enemies[i]->type==0){		//Divides
								pacman->score-=10;
								enemies[i]->active=false;
							}else if(enemies[i]->type==1){	//Freeze
								pacman->score-=15;
								pacman->freezeCounter=0;
								pacman->knockbackCounter=0;
								pacman->freeze=true;
								pacman->knockback=false;
								enemies[i]->active=false;
							}else if(enemies[i]->type==2){	//Knockback
								pacman->score-=20;
								pacman->freezeCounter=0;
								pacman->knockbackCounter=0;
								pacman->freeze=false;
								pacman->knockback=true;
								enemies[i]->active=false;
							}else if(enemies[i]->type==3){	//Explode
								pacman->score-=25;
								enemies[i]->explodeCounter=60*15;   	
							}else{
								pacman->score-=20;
								enemies[i]->active=false;
							}
						}
					}
					
					//Similar logic for other players
					if(pacman2!=nullptr){
						if(enemies[i]->active){
							if(pacman2->collide(enemies[i],m)){
								if(pacman2->isInvincible || pacman2->isVaccinated){
									if(pacman2->isVaccinated){
										enemies[i]->active = false;
									}
								}else{
									m->PlaySound("collision");
									if(enemies[i]->type==0){
										pacman2->score-=15;
									}else if(enemies[i]->type==1){
										pacman2->score-=10;
									}else if(enemies[i]->type==2){
										pacman2->score-=20;
									}else if(enemies[i]->type==3){
										pacman2->score-=25;
									}else{
										pacman2->score-=20;
									}
									enemies[i]->active=false;
								}
							}
						}
					}
					if (fireball!=nullptr && fireball->collide(enemies[i],m)){
						enemies[i]->active = false;
						fireball=nullptr;
					}
					//Updating the movement of enemies
					if(enemies[i]->active){	
						enemyAI(i);
					}
				}	
			}
		}

		void placeEnemy(){
			int n = rand()%4;
			vector<SDL_Texture*> newTexture;
			switch(n){
				case 0:{newTexture=texture_e0;break;}
				case 1:{newTexture=texture_e1;break;}
				case 2:{newTexture=texture_e2;break;}
				case 3:{newTexture=texture_e3;break;}
			}
			enemies.push_back(new Enemy(renderer,n,(maze->m_width-2)*100,(maze->m_height-2)*100,menu_n->s_width,newTexture));
			numEnemiesPlaced++;
		}
		
		//To keep track of the last key pressed
		int last_key_x(Character* pacman){
			if (pacman->lastKey==1 || pacman->lastKey==3){
				return 0;
			}
			else if (pacman->lastKey==2){
				return (-1)*pacman->speed;
			}
			else{
				return pacman->speed;
			}
		}
		int last_key_y(Character* pacman){
			if (pacman->lastKey==2 || pacman->lastKey==0){
				return 0;
			}
			else if (pacman->lastKey==1){
				return (-1)*pacman->speed;
			}
			else{
				return pacman->speed;
			}
		}

		//Local event handler for play state 
		void handle_event(SDL_Event e,int* state,SoundClass* m,bool music_on,network* nmanager){
			if (play_debug)cout<<"play.cpp:handle_event\n";
			
			if(pacman->knockback){
				return;
			}

			if(e.type==SDL_QUIT){
				*state=6;				
			}else if(e.type==SDL_MOUSEBUTTONDOWN){
				int a,b;
				SDL_GetMouseState(&a,&b);
				int i = locatePointer(a,b);
				if(i>=0){
					//buttons[i]->handle_event(state,m,prevstate,e);
				}
			}else if(e.type==SDL_KEYDOWN){
				changeSpeed(pacman,e);

				if(e.key.keysym.sym==SDLK_ESCAPE){
					*state=2;
				}else if(e.key.keysym.sym==SDLK_p){
					*state=2;
				}
				else if(e.key.keysym.sym==SDLK_a && !multiplayer){
					maze->placeFruits();
				}
				else if(e.key.keysym.sym==SDLK_v && !multiplayer){
					maze->placeVaccine();
				}
				else if(e.key.keysym.sym==SDLK_e && !multiplayer){
					placeEnemy(); 
				}
				else if(e.key.keysym.sym==SDLK_SPACE && !multiplayer && numFballs>0){
					fireball=new Character(renderer,pacman->x,pacman->y,pacman->x_speed*4,pacman->y_speed*4,texture_ball); 
					numFballs--;
				}
			}
		}

		//To get the location of the enemies when the server is created in
		//string form so as to pass this data to other client(s) through
		//the network manager
		string getEnemiesPos(){
			string enemy_state="";
			for(int i=0;i<enemies.size();i++){
				enemy_state+=enemies[i]->getEnemyState();
			}
			return enemy_state;
		}
		
		//Combination of maze data and enemy data in string form
		string getPlayState(){
			string name=menu_n->cplayer;
			if (name.size()>10){
				name=name.substr(0,10);
			}
			else{
				while (name.size()!=10){
					name.push_back(' ');
				}
			}
			string result= maze->getMazeState()+to_string(enemies.size())+getEnemiesPos()+name;
			return result;
		}
		
		//Function to add a client to the server
		void addPlayer(){
			pacman2 = new Character("./../assets/corona.bmp",renderer,(maze->m_width-2)*100-90,110,true,menu_n->s_width,texture_p,texture_pv,texture_pa);
			pacman2->name=pl2name;
			
		}

	private:

		//To check whether the pacman is standing on a quarantine block
		void checkQuarantine(Character* pacman){
			int x = pacman->x/(maze->mazeCell.w);
			int y = pacman->y/(maze->mazeCell.h);
			if(maze->mazeData[x][y]==7){
				if(pacman->inQuarantine){
					pacman->hazardCounter++;
					if(pacman->hazardCounter%60==0 && !pacman->isMasked){
						pacman->score=pacman->score-pacman->hazardCounter/60;
					}
				}else{
					pacman->inQuarantine = true;
					pacman->hazardCounter = 0;
				}
			}else{
				if(pacman->inQuarantine){
					pacman->inQuarantine = false;
					pacman->hazardCounter = 0;
				}
			}
		}

		//This function return the number of enemies as a function of the current level of the game
		int f(int n){
			return 1;
		}

		//To track the current location of the mouse pointer
		int locatePointer(int a,int b){
			if (play_debug)cout<<"play.cpp:locatePointer\n";
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
		
		//This function is used for smooth movement of pacman. This function
		//is not required for an enemy because enemies are controlled by the 
		//program itself, and so the movement of enemies are accurate. But on
		//the other hand the pacman is controlled by a human player, and because
		//of some margin of error, a player might find it difficult to change 
		//directions across T-shape junctions because human reflexes are not as
		//fast as the decision making process of a computer program

		//So, we have implemented a key buffer for pacman which remembers the 
		//last key pressed by the player after the most recent direction change.
		//And thus, when the next junction comes, the player can have more time
		//to decide which direction to choose next, and pressing the key beforehand
		//will store the key in the key buffer and the effect corresponding to this
		//key press will still be observed even if the player didn't press the key
		//at the exact required movement. 
		void changeSpeed(Character* pacman,SDL_Event e){
			if (play_debug)cout<<"play.cpp::changeSpeed\n";
			if(e.type==SDL_KEYDOWN){
				switch(e.key.keysym.sym){
					case SDLK_UP:{
						if (pacman->cur_dir!=1){pacman->lastKey=1;}
						if (!collidePlayer(pacman,0,(-1)*pacman->speed)){
							pacman->y_speed=(-1)*pacman->speed;
							pacman->x_speed=0;
							pacman->cur_dir=1;
						}
						break;
					}
					case SDLK_DOWN:{
						if (pacman->cur_dir!=3){pacman->lastKey=3;}
						if (!collidePlayer(pacman,0,pacman->speed)){
							pacman->y_speed=pacman->speed;
							pacman->x_speed=0;
							pacman->cur_dir=3;
						}
						break;
					}
					case SDLK_RIGHT:{
						if (pacman->cur_dir!=0){pacman->lastKey=0;}
						if (!collidePlayer(pacman,pacman->speed,0)){
							pacman->y_speed=0;
							pacman->x_speed=pacman->speed;
							pacman->cur_dir=0;
						}
						break;
					}
					case SDLK_LEFT:{
						if (pacman->cur_dir!=2){pacman->lastKey=2;}
						if (!collidePlayer(pacman,(-1)*pacman->speed,0)){
							pacman->y_speed=0;
							pacman->x_speed=(-1)*pacman->speed;
							pacman->cur_dir=2;		
						}
						break;
					}
				}
			}
		}

		//For checking the collision between the player and the walls of the maze
		bool collidePlayer(Character *pacman,int x_speed,int y_speed){
			int x = pacman->x;
			int y = pacman->y;
			int pw = pacman->width;
			int ph = pacman->height;
			int w = maze->mazeCell.w;
			int h = maze->mazeCell.h;

			//As evident, the collision is checked on the basis of the 
			//current direction of motion of pacman/enemy
			if(x_speed!=0){
				if(x_speed>0){
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
				if(y_speed>0){
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
		
		//For checking the collision between the player and the walls of the maze
		bool collideProjectile(Character *pacman,int x_speed,int y_speed){
			int x = pacman->x;
			int y = pacman->y;
			int pw = pacman->width;
			int ph = pacman->height;
			int w = maze->mazeCell.w;
			int h = maze->mazeCell.h;

			//As evident, the collision is checked on the basis of the 
			//current direction of motion of pacman/enemy
			if(x_speed!=0){
				if(x_speed>0){
					bool check1 = maze->mazeData[(x+pw)/w][y/h]!=1;
					bool check2 = maze->mazeData[(x+pw)/w][(y+ph-1)/h]!=1;
					if(check1 && check2){
						return false;
					}else{
						return true;
					}
				}
				else{
					
					bool check1 = maze->mazeData[(x-1)/w][y/h]!=1;
					bool check2 = maze->mazeData[(x-1)/w][(y+ph-1)/h]!=1;
					if(check1 && check2){
						return false;
					}
					else{
						return true;
					}
					
				}
			}else{
				if(y_speed>0){
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


		//The following function manage the collision between the pacman
		//and different power-ups
		bool eatPowerUp(Character* pacman,int powerup){
			if (play_debug)cout<<"play.cpp:EatPowerUP\n";
			
			if(pacman->x_speed!=0){
				if(pacman->x_speed>0){
					if(maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==powerup){
						maze->mazeData[(pacman->x+pacman->width/3+1)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]==powerup){
						maze->mazeData[(pacman->x+(pacman->width)/3)/(maze->mazeCell.h)][(pacman->y)/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}else{
				if(pacman->y_speed>0){
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]==powerup){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+pacman->height/3+1)/(maze->mazeCell.h)]=2;
						return true;
					}
				}else{
					if(maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]==powerup){
						maze->mazeData[(pacman->x)/(maze->mazeCell.h)][(pacman->y+(pacman->height/3))/(maze->mazeCell.h)]=2;
						return true;
					}
				}
			}
			return false;
		}

		//This method controls the motion of the enemies, which is randomised
		//in the sense that an enemy will try to consider different possible 
		//directions in which to travel at every moment, and out of all of them
		//it will decide a random direction to travel in 
		void enemyAI(int i){
			Enemy* enemy = enemies[i];

			//The checking of possible directions will take place only when
			//the enemy reaches a particular position, which is when the
			//co-ordinates of its bounding box are exactly aligned with a 
			//maze cell because we have taken the size of the enemy to be 
			//exactly equal to the size of the maze cell.

			//We don't check this at every moment just because any other
			//position will definitely lead to a collision with a wall, and 
			//so we decrease the number of computations using this strategy
			
			//This strategy also prevents the enemy to unnaturally change its
			//in the middle of any cell 
			if(enemy->x%100==0 && enemy->y%100==0){
				int x = enemy->x;
				int y = enemy->y;
				int pw = enemy->width;
				int ph = enemy->height;
				int prevDirection;
				int nextDirection;

				//Handling special types of enemies
				if(enemy->explodeCounter==15*60){
					if(enemy->type==0){
						vector<SDL_Texture*> newTexture;
						switch(nextEnemy){
							case 0:{newTexture=texture_e0;break;}
							case 1:{newTexture=texture_e1;break;}
							case 2:{newTexture=texture_e2;break;}
							case 3:{newTexture=texture_e3;break;}
						}
						Enemy* newEnemy = new Enemy(renderer,nextEnemy,x,y,menu_n->s_width,newTexture);
						newEnemy->x_speed = (-1)*enemy->x_speed;
						newEnemy->y_speed = (-1)*enemy->y_speed;
						enemies.push_back(newEnemy);
						numEnemiesPlaced++;
						enemy->explodeCounter=0;
						nextEnemy=(nextEnemy+1)%4;		
					}else if(enemy->type==3){
						enemy->active=false;
						explode(x/100,y/100);
					}
				}

				//This obtains the previous direction of the enemy so that
				//the enemy doesn't randomly choose the previous direction, 
				//because if it did, then the enemy would be able to revert 
				//its direction at any junction or collision, which is an
				//irregular movement. So, we make sure that the enemy never
				//reverses its direction(except in case of a dead-end)
				if(enemy->x_speed>0){
					prevDirection=2;	
				}else if(enemy->x_speed<0){
					prevDirection=0;
				}else if(enemy->y_speed>0){
					prevDirection=1;
				}else{
					prevDirection=3;
				}

				//A list of open directions
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

				//Dead end case, in which the enemy can do nothing except
				//reversing its direction
				if(n==1){
					nextDirection = unvisited[0];
				}else{

					//In all the other cases, the enemy randomly chooses a
					//possible open direction and proceeds along that direction
					//except the one where it already came from(i.e. no reversal)
					while(true){
						int k = rand()%n;
						if(abs(unvisited[k]-prevDirection)!=2){
							nextDirection = unvisited[k];
							break;
						}
					}
				}

				//Apart from a junction, an enemy must also change its direction
				//in case it cannot move in the current direction due to a collision
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

		void explode(int a,int b){
			int w = maze->m_width;
			int h = maze->m_height;
			if(a==1){
				maze->mazeData[a+1][b]=2;
				if(b==1){
					maze->mazeData[a][b+1]=2;
					maze->mazeData[a+1][b+1]=2;
				}else if(b==h-2){
					maze->mazeData[a][b-1]=2;
					maze->mazeData[a+1][b-1]=2;
				}else{
					maze->mazeData[a][b+1]=2;
					maze->mazeData[a+1][b+1]=2;
					maze->mazeData[a][b-1]=2;
					maze->mazeData[a+1][b-1]=2;
				}
			}else if(a==w-2){
				maze->mazeData[a-1][b]=2;
				if(b==1){
					maze->mazeData[a][b+1]=2;
					maze->mazeData[a-1][b+1]=2;
				}else if(b==h-2){
					maze->mazeData[a][b-1]=2;
					maze->mazeData[a-1][b-1]=2;
				}else{
					maze->mazeData[a][b+1]=2;
					maze->mazeData[a-1][b+1]=2;
					maze->mazeData[a][b-1]=2;
					maze->mazeData[a-1][b-1]=2;
				}
			}else{
				maze->mazeData[a+1][b]=2;
				maze->mazeData[a-1][b]=2;
				if(b==1){
					maze->mazeData[a][b+1]=2;
					maze->mazeData[a+1][b+1]=2;
					maze->mazeData[a-1][b+1]=2;
				}else if(b==h-2){
					maze->mazeData[a+1][b-1]=2;
					maze->mazeData[a-1][b-1]=2;
					maze->mazeData[a][b-1]=2;
				}else{
					maze->mazeData[a+1][b-1]=2;
					maze->mazeData[a-1][b-1]=2;
					maze->mazeData[a][b-1]=2;
					maze->mazeData[a][b+1]=2;
					maze->mazeData[a+1][b+1]=2;
					maze->mazeData[a-1][b+1]=2;
				}
			}
		}
		
		//For checking the collision between an enemy and the walls of the maze
		//Similar checking as in collidePlayer function
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