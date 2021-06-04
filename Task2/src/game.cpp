#include "game.hpp"
#include "sounds.h";

bool music=true;

using namespace std;

vector<Menu*> menuList;
play* playState=nullptr;
Menu* gameOver=nullptr;
bool game_debug=true;
SoundClass* MusicManager=nullptr;
network* nmanager=nullptr;
bool client_started=false;

Game::Game(char* title, int xcor,int ycor,int width_window,int height_window,bool isServer){
	if (game_debug)cout<<"game.cpp::Game\n";
	int flag=SDL_WINDOW_SHOWN;
	running = true;
	s_width = width_window;
		s_height = height_window;
	if (SDL_Init(SDL_INIT_EVERYTHING)==0){
		cout<<"SDL Initialised succesfully....\n";
		window=SDL_CreateWindow(title,xcor,ycor,width_window,height_window,flag);
		if (window==NULL){
			running=false;
			cout<<"Error:Couldn't initialize window\n";
		}
		else{
			cout<<"Window Inititalised Successfully....\n";
			renderer=SDL_CreateRenderer(window,-1,0);
			SDL_RenderSetLogicalSize(renderer,3700,2100);   

			if (renderer==NULL){
				running=false;
				cout<<"Error:Couldn't initialize Renderer\n";
			}
			else{
				cout<<"Renderer initialized Successfully...\n";
				SDL_SetRenderDrawColor(renderer,255,255,255,255);
				menuback=Texture::LoadT("./../assets/menb.png",renderer);
				gameback=Texture::LoadT("./../assets/back.png",renderer);
				overback=Texture::LoadT("./../assets/gameover.jpg",renderer);
				winback=Texture::LoadT("./../assets/start.png",renderer);
				
				if (menuback==NULL){
					running=false;
					cout<<"Error:Couldn't initialize background image\n";
					cout<<IMG_GetError()<<"\n";
				}

				nmanager=new network(isServer);
				
				int l;
				cout<<"Select starting level: ";cin>>l;
				
				cout<<"Initialising Menus\n";
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
				
				cout<<"Menus Initialised\n";
				MusicManager = new SoundClass();
				MusicManager->InitializeAll();
				MusicManager->PlaySound("gamestart");
				music = true;
				cout<<"Initialising PlayState\n";
				
				playState = new play("Play",l,gameback,renderer,startMenu);
				cout<<"PlayState Initialised\n";
				state=1;
			}
		}
	}
	else{
		cout<<"Initialisation unsuccesful...\n";
		running=false;
	}
}


void Game::handle_event(){	
	if (game_debug)cout<<"game.cpp::handle_event\n";
	
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type==SDL_MOUSEBUTTONDOWN){
		int a,b;
		SDL_GetMouseState(&a,&b);
		cout<<"\n\nMouse Button Pressed:coordinates:"<<a<<" "<<b<<"\n\n";
	}
	if(state==0){
		playState->handle_event(event,&state,MusicManager,music,nmanager);
		string x=playState->getPlayerState();
	}else if(state==-1){
		gameOver->handle_event(event,&state,MusicManager,music);
	}else{
		menuList[state-1]->handle_event(event,&state,MusicManager,music);
	}
}

void Game::process(){
	if (game_debug)cout<<"game.cpp::process\n";
	if (state==6){running=false;return;}
	if (state==0){
		playState->update(&state,true,MusicManager,music,nmanager);
		if(state==-2){
			int l=playState->lvl;
			playState = new play("Play",l+1,gameback,renderer,menuList[0]);
			state = 0;
		}//added
	}else if(state==-2){
		playState = new play("Play",5,gameback,renderer,menuList[0]);
		state = 0;
	}else{
		menuList[state-1]->update();
	}
}

void Game::render(){
	if (game_debug)cout<<"game.cpp::render\n";
	if (state==6){running=false;return;}
	SDL_RenderClear(renderer);
	if(state==0){
		playState->render();
	}else{
		menuList[state-1]->render();
	}
	SDL_RenderPresent(renderer);
}

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