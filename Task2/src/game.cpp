#include "game.hpp"
#include "sounds.h";

int SCREEN_WIDTH=3840;
int SCREEN_HEIGHT=2160;
bool music=true;

using namespace std;

vector<Menu*> menuList;
play* playState=nullptr;
Menu* gameOver=nullptr;

SoundClass* MusicManager=nullptr;

Game::Game(char* title, int xcor,int ycor,int width_window,int height_window){
	int flag=SDL_WINDOW_SHOWN;
	SCREEN_HEIGHT = height_window;
	SCREEN_WIDTH = width_window;
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
				overback=Texture::LoadT("./../assets/gameover.jpg",renderer);
				
				if (menuback==NULL){
					running=false;
					cout<<"Error:Couldn't initialize background image\n";
					cout<<IMG_GetError()<<"\n";
				}
				
				playState = new play("Play",1,gameback,renderer,SCREEN_WIDTH,SCREEN_WIDTH);
				
				Menu* startMenu = new Menu("Start",1,menuback,renderer,SCREEN_WIDTH,SCREEN_WIDTH);
				menuList.push_back(startMenu);
				
				Menu* pauseMenu = new Menu("Pause",2,menuback,renderer,SCREEN_WIDTH,SCREEN_WIDTH);
				menuList.push_back(pauseMenu);
				
				Menu* optionsMenu = new Menu("Options",3,menuback,renderer,SCREEN_WIDTH,SCREEN_WIDTH);
				menuList.push_back(optionsMenu);
				
				Menu* gameOver = new Menu("Game Over",4,overback,renderer,SCREEN_WIDTH,SCREEN_WIDTH);
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
	SDL_Event event;
	SDL_PollEvent(&event);
	if(state==0){
		playState->handle_event(event,&state,MusicManager,music);
	}else if(state==-1){
		gameOver->handle_event(event,&state,MusicManager,music);
	}else{
		menuList[state-1]->handle_event(event,&state,MusicManager,music);
	}
}

void Game::process(){
	if (state==0){
		playState->update(&state,true,MusicManager,music);
	}else if(state==5){
		running = false;
	}else if(state==-2){
		playState = new play("Play",1,gameback,renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
		state = 0;
	}else{
		menuList[state-1]->update();
	}
}

void Game::render(){
	SDL_RenderClear(renderer);
	if(state==0){
		playState->render();
	}else{
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
