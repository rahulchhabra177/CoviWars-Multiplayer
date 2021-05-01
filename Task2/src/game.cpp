#include "game.hpp"
#include "Map.h";
#include "menu.cpp";
#include "play.cpp";
#include "sounds.h";
int SCREENWIDTH=800;
int SCREENHEIGHT=600;

using namespace std;

Character * tile=nullptr;
SoundClass *MusicManager=nullptr;
Map *lvl1=nullptr;
// SoundClass* dj=nullptr;
vector<Menu*> menuList;
play* playState=nullptr;

Game::Game(char* title, int xcor,int ycor,int width_window,int height_window){
	int flag=SDL_WINDOW_SHOWN;
	running = true;
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
			if (renderer==NULL){
				running=false;
				cout<<"Error:Couldn't initialize Renderer\n";
			}
			else{
				cout<<"Renderer initialized Successfully...\n";
				SDL_SetRenderDrawColor(renderer,255,255,255,255);
				
				menuback=Texture::LoadT("./../assets/welcome.jpg",renderer);
				gameback=Texture::LoadT("./../assets/black.jpg",renderer);
				
				if (menuback==NULL){
					running=false;
					cout<<"Error:Couldn't initialize background image\n";
					cout<<IMG_GetError()<<"\n";
				}
				else{
					lvl1=new Map();
					lvl1->LoadMap(renderer);
    				}
				
				playState = new play("Play",1,gameback,renderer);
				
				Menu* startMenu = new Menu("Start",1,menuback,renderer);
				menuList.push_back(startMenu);
				
				Menu* pauseMenu = new Menu("Pause",2,menuback,renderer);
				menuList.push_back(pauseMenu);
				
				Menu* optionsMenu = new Menu("Options",3,menuback,renderer);
				menuList.push_back(optionsMenu);
				MusicManager=new SoundClass();
				MusicManager->InitializeAll();
				MusicManager->PlaySound("a");
				state=1;
				// dj=new SoundClass();
			}

		}
	}
	else{
		cout<<"Initialisation unsuccesful...\n";
		running=false;
	}
}


void Game::handle_event(){
	SDL_Event event;
	SDL_PollEvent(&event);
	if(state==0){
		playState->handle_event(event,&state);
	}
	else{
		menuList[state-1]->handle_event(event,&state);
	}
}

void Game::process(){
	if (state==0){
		playState->update();
	}else if(state==4){
		running = false;
	}else{
		menuList[state-1]->update();
	}
}

void Game::render(){
	SDL_RenderClear(renderer);
	if(state==0){
		playState->render();
	}
	else{
		cout<<"renfering menu list\n";
		menuList[state-1]->render();
	}	
	SDL_RenderPresent(renderer);
}

void Game::close(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout<<"Game Closed...\n";
}

bool Game::isRunning(){
	return running;
}
