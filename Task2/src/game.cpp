#include "game.hpp"
#include "sounds.h";

bool music=true;

using namespace std;

vector<Menu*> menuList;
play* playState=nullptr;
Menu* gameOver=nullptr;
bool debug_game=false;
SoundClass* MusicManager=nullptr;
int SCREEN_WIDTH=1200;
int SCREEN_HEIGHT=700;
Game::Game(char* title, int xcor,int ycor){
	if (debug_game)cout<<"game.cpp::Game\n";
	int flag=SDL_WINDOW_FULLSCREEN;
	running = true;
	if (SDL_Init(SDL_INIT_EVERYTHING)==0){
		cout<<"SDL Initialised succesfully....\n";
		window=SDL_CreateWindow(title,xcor,ycor,1300,650,flag);
		if (window==NULL){
			running=false;
			cout<<"Error:Couldn't initialize window\n";
		}
		else{
			cout<<"Window Inititalised Successfully....\n";
			renderer=SDL_CreateRenderer(window,-1,0);
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
				
				if (menuback==NULL){
					running=false;
					cout<<"Error:Couldn't initialize background image\n";
					cout<<IMG_GetError()<<"\n";
				}
				
				playState = new play("Play",1,gameback,renderer);
				
				Menu* startMenu = new Menu("Start",1,menuback,renderer);
				menuList.push_back(startMenu);
				
				Menu* pauseMenu = new Menu("Pause",2,menuback,renderer);
				menuList.push_back(pauseMenu);
				
				Menu* optionsMenu = new Menu("Options",3,menuback,renderer);
				menuList.push_back(optionsMenu);
				
				Menu* gameOver = new Menu("Game Over",4,overback,renderer);
				menuList.push_back(gameOver);
				
				MusicManager = new SoundClass();
				MusicManager->InitializeAll();
				MusicManager->PlaySound("gamestart");
				music = true;

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
	
	if (debug_game)cout<<"game.cpp::handle_event\n";
	SDL_Event event;
	SDL_PollEvent(&event);
	// cout<<event.type<<":"<<SDL_MOUSEMOTION<<":event\n";
	if (event.type==SDL_MOUSEBUTTONDOWN){
		int a,b;
				SDL_GetMouseState(&a,&b);
				
				cout<<"\n\n\n\n\ncoordinates:"<<a<<" "<<b<<"\n\n\n";


			}
	if(state==0){
		playState->handle_event(event,&state,MusicManager,music);
	}else if(state==-1){
		gameOver->handle_event(event,&state,MusicManager,music);
	}else{
		menuList[state-1]->handle_event(event,&state,MusicManager,music);
	}
}

void Game::process(){
	if (debug_game)cout<<"game.cpp::process\n";
	if (state==0){
		playState->update(&state,true,MusicManager,music);
	}else if(state==5){
		running = false;
	}else if(state==-2){
		playState = new play("Play",1,gameback,renderer);
		state = 0;
	}else{
		menuList[state-1]->update();
	}
}

void Game::render(){
	if (debug_game)cout<<"game.cpp::render\n";
	SDL_RenderClear(renderer);
	if(state==0){
		playState->render();
	}else{
		menuList[state-1]->render();
	}	
	SDL_RenderPresent(renderer);
}

void Game::close(){
	if (debug_game)cout<<"game.cpp::close\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout<<"Game Closed...\n";
}

bool Game::isRunning(){
	return running;
}
