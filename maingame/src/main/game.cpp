#include "./../main/game.hpp"
#include "./../menu/popup.h"
bool music=true;

using namespace std;

//Null implementations of basic classes to be used in the game for global access

vector<Menu*> menuList;			//List of all menus
play* playState=nullptr;		//Play state 
Menu* gameOver=nullptr;			//Game Over state		
SoundClass* MusicManager=nullptr;	//Music and Sound Manager
network* nmanager=nullptr;		//Network/Socket manager for multiplayer

//Pop-ups for different menus
Popup* pmenu=nullptr,*optionPopup=nullptr,*lobby=nullptr,*playAgain=nullptr,*pause=nullptr,*win=nullptr,*credits=nullptr;

bool game_debug=false;
bool client_started=false;		

//For navigating throughtout the game, we have implemneted the game as a collection
//of states all of which have their own characteristics and actions, and the 
//changes in the game take place as a transition between these states:
//
// 0: The play state which displays the actual contents of the game
// 1: Start menu state
// 2: Pause menu state
// 3: Options menu state
// 4: Game Over state
// 5: Win state
// 6: Pseudostate for exiting the game
// 100: Pseudostate to transition between start menu and single player game
// 101: Pseudostate to transition between start menu and multi player game
// -1: Pseudostate to transition to game over state in case the player loses
// -2: Pseudostate to transition back to state for playing again
// -3: Pseudostate to transition between levels

//Pseudostates are not actual states which are visible during the game but are
//important in transitions between states

//Game constructor
Game::Game(string title, int xcor,int ycor,int width_window,int height_window,bool isserver){
	if (game_debug)cout<<"game.cpp::Game\n";
	
	isServer = isserver;
	int flag=SDL_WINDOW_SHOWN;
	running = true;
	s_width = width_window;
	s_height = height_window;

	string ip_addr;
	int portNo;
	cout<<"Enter your IP address: ";cin>>ip_addr;
	cout<<"Enter your port number: ";cin>>portNo;
	
	if (SDL_Init(SDL_INIT_EVERYTHING)==0){
		cout<<"SDL Initialised succesfully....\n";
		window=SDL_CreateWindow(&title[0],xcor,ycor,width_window,height_window,flag);
		if (window==NULL){
			running=false;
			cout<<"Error:Couldn't initialize window\n";
		}
		else{
			cout<<"Window Inititalised Successfully....\n";
			renderer=SDL_CreateRenderer(window,-1,0);
			
			//This function is used for resolution scaling, so that the game can
			//be played on any resolution. The logical size of our renderer is set
			//to 3700*2100 which means all the rendering is done as if it was done 
			//on a screen of this resolution, but the actual display will depend
			//on the input resolution.
			SDL_RenderSetLogicalSize(renderer,3700,2100);   

			if (renderer==NULL){
				running=false;
				cout<<"Error:Couldn't initialize Renderer\n";
			}
			else{
				cout<<"Renderer initialized Successfully...\n";
				
				//Setting up the renderer of white color so that it acts as a blank canvas
				SDL_SetRenderDrawColor(renderer,255,255,255,255);
				
				//Different backgrounds of the different states of the game
				menuback=Texture::LoadT("./../assets/backgrounds/menub.jpg",renderer);
				gameback=Texture::LoadT("./../assets/backgrounds/purple.jpeg",renderer);
				overback=Texture::LoadT("./../assets/backgrounds/gameover.jpg",renderer);
				winback=Texture::LoadT("./../assets/backgrounds/start.png",renderer);

				//Initialisations of all the null objects declared before

				nmanager = new network(isServer,&ip_addr[0],portNo);
				pmenu = new Popup(renderer,1,false,s_width,s_height);
				optionPopup = new Popup(renderer,3,false,s_width,s_height);
				lobby=new Popup(renderer,-1,false,s_width,s_height);
				playAgain=new Popup(renderer,2,false,s_width,s_height);
				pause=new Popup(renderer,4,false,s_width,s_height);
				credits=new Popup(renderer,-2,false,s_width,s_height);
				win=new Popup(renderer,5,false,s_width,s_height);
				
				Menu* startMenu = new Menu("Start",1,menuback,renderer,width_window,height_window);
				menuList.push_back(startMenu);
				
				Menu* pauseMenu = new Menu("Pause",2,menuback,renderer,width_window,height_window);
				menuList.push_back(pauseMenu);
				
				Menu* optionsMenu = new Menu("Options",3,menuback,renderer,width_window,height_window);
				menuList.push_back(optionsMenu);
				
				Menu* gameOver = new Menu("Game Over",4,overback,renderer,width_window,height_window);
				menuList.push_back(gameOver);
				
				Menu* winScreen = new Menu("Win Screen",5,winback,renderer,width_window,height_window);
				menuList.push_back(winScreen);
				
				Menu* Rules = new Menu("Rules Screen",6,gameback,renderer,width_window,height_window);
				menuList.push_back(Rules);
				
				MusicManager = new SoundClass();
				MusicManager->InitializeAll();
				music = true;
				MusicManager->PlayMusic("bMusic");
				MusicManager->PlaySound("gamestart");
				
				//Initial state when the game starts(start menu in this case)
				state=1;
			}
		}
	}else{
		cout<<"Initialisation unsuccesful...\n";
		running=false;
	}
}

//This method takes care of the input given by the player through mouse or 
//keyboard and uses the input for manipulating objects in a state or in changing 
//states
void Game::handle_event(){	
	if (game_debug)cout<<"game.cpp::handle_event:"<<state<<":"<<prevstate<<"\n";
	
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type==SDL_MOUSEBUTTONDOWN){
		int a,b;
		//This function retrieves the current position of the mouse pointer
		SDL_GetMouseState(&a,&b);
	}
	
	//Note that most of the event handling is deferred to event handlers of
	//other classes, so that every state handles its own input, thus
	//encouraging modularity
	if(state==0){
		playState->handle_event(event,&state,MusicManager,prevstate,nmanager);
	}else if(state==3){
		optionPopup->handle_event(event,&state,MusicManager,&prevstate);
	}else if (state==101){
		lobby->handle_event(event,&state,MusicManager,&prevstate);
	}else if(state==-1){
		playAgain->handle_event(event,&state,MusicManager,&prevstate);
	}else if (state==-3){
		pmenu->handle_event(event,&state,MusicManager,&prevstate);
		if(state==-2){
			int l=playState->lvl;
			playState = new play("Play",l+1,gameback,renderer,menuList[0],false);
			state = 0;
		}
	}else if (state==4){
		playAgain->handle_event(event,&state,MusicManager,&prevstate);
	}else if(state==5){
		win->handle_event(event,&state,MusicManager,&prevstate);
	}else if (state==2){
		pause->handle_event(event,&state,MusicManager,&prevstate);
	}
	else if (state==7){
		credits->handle_event(event,&state,MusicManager,&prevstate);
	}
	else if (state==8){
		menuList[5]->handle_event(event,&state,MusicManager,&prevstate);

	}
	else{
		menuList[state-1]->handle_event(event,&state,MusicManager,&prevstate);
	}

	//In case of multiplayer, the server also needs to check for other clients
	//before starting the play state
	if(playState!=nullptr && playState->multiplayer){
		if (isServer and !nmanager->connected){
			nmanager->check_new_players();
			
			//As soon as the server detects another client, it sends
			//info regarding the structure of the maze, the location
			//of all the enemies and the initial position of the
			//pacman for consistency among all the players.
			if (nmanager->connected){
				nmanager->send("$"+playState->getPlayState(),&state,&prevstate);
				playState->addPlayer();
			}
		}
	}
}

//This method updates all the objects of the game as the game goes on, and 
//similar to the event handler, this method also defers the updation process to
//other classes, depending on current state for maintaining clarity and the 
//ease of debugging.
void Game::process(){
	if (game_debug)cout<<"game.cpp::process "<<state<<":"<<prevstate<<"\n";
	
	
	if (state==0){
		playState->update(&state,true,MusicManager,&prevstate,nmanager);
	}else if(state==-3){
		pmenu->update(&state);
		if(state==-2){
			int l=playState->lvl;
			playState = new play("Play",l+1,gameback,renderer,menuList[0],false);
			state = 0;
		}
	}
	else if(state==6){
		running=false;
		return;
	}
	else if (state==3){
		optionPopup->update(&state);
	}
	else if (state==2){
		pause->update(&state);
		if(playState->multiplayer){
			playState->update(&state,true,MusicManager,&prevstate,nmanager);
		}
	}
	else if (state==7){
		credits->update(&state);
	}
	else if (state==4){
		playAgain->update(&state);
	}
	else if (state==5){
		win->update(&state);
	}
	else if(state==-2){
		int a = playState->pacman->x;
		int b = playState->pacman->y;
	 	playState->reinitialize(a,b);
	 	state = 0;
	}
	else if(state==100){
		//This pseudostate manages the transition between the start menu 
		//and the play state in case of a single player game, so a new 
		//single play state is created
		playState = new play("Play",1,gameback,renderer,menuList[0],false);
		state = 0;
	}
	else if(state==101){
	
		//This pseudostate manages the transition between the start menu 
		//and the play state in case of a multi player game
		if (!isServer){
		
			//The new clients receive the data regarding the maze,
			//the enemies and the initial position of the pacman
			//from the server through the network manager 
			string mzData=nmanager->receive(595,&state,&prevstate);
			if (mzData!=""){
				playState = new play("Play",1,gameback,renderer,menuList[0],true,mzData);
				nmanager->timeout=SDL_GetTicks();
				string plname=playState->pacman->name;
				if (plname.size()>10){
					plname=plname.substr(0,10);
				}
				else{
					while (plname.size()!=10){
						plname.push_back(' ');
					}
				}
				nmanager->send(plname,&state,&prevstate);
				state=0;
				nmanager->isPlaying=true;
			}
		}
		else{
			if (playState==nullptr){
				playState = new play("Play",1,gameback,renderer,menuList[0],true);
			}
			if (!nmanager->isPlaying){
				nmanager->timeout=SDL_GetTicks();
				string plname=nmanager->receive(10,&state,&prevstate);
				if (plname!=""){state=0;nmanager->isPlaying=true;playState->pacman2->name=plname;}
			}
		}
	}
	else if (state==8){
		menuList[5]->update();
	}
	else{
		menuList[state-1]->update();
	}
}

//For rendering the elements of the screen depending upon the current state, and
//like previous methods, rendering is also transferred to objects of other 
//classes depending upon the current state of the game
void Game::render(){
	if (game_debug)cout<<"game.cpp::render:"<<state<<":"<<prevstate<<"\n";
	if (state==6){running=false;return;}
	if(state==0){
		SDL_RenderClear(renderer);
		playState->render();
	}
	else if (state==-3){
		SDL_RenderClear(renderer);
		playState->render();
		pmenu->render(renderer);
	}
	else if (state==3){
		if (prevstate==1){
			SDL_RenderClear(renderer);
			menuList[0]->render();
			optionPopup->render(renderer);
		}
		else{
			SDL_RenderClear(renderer);
			playState->render();
			optionPopup->render(renderer);
		}
	}
	else if (state==4){
		SDL_RenderClear(renderer);
		playState->render();
		playAgain->render(renderer);
	}
	else if (state==2){
		SDL_RenderClear(renderer);
		playState->render();
		pause->render(renderer);
	}
	else if (state==5){
		SDL_RenderClear(renderer);
		playState->render();
		win->render(renderer);
	}
	else if (state==101){
		SDL_RenderClear(renderer);
		menuList[0]->render();
		lobby->render(renderer);
	}
	else if (state==7){
		SDL_RenderClear(renderer);
		menuList[0]->render();
		credits->render(renderer);
	}
	else if (state==8){
		SDL_RenderClear(renderer);
		menuList[5]->render();
	}
	else{
		SDL_RenderClear(renderer);
		menuList[state-1]->render();
	}
	SDL_RenderPresent(renderer);
}

//Freeing up memory after the game closes
void Game::close(){
	if (game_debug)cout<<"game.cpp::close\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout<<"Game Closed...\n";
}

bool Game::isRunning(){
	return running;
}
