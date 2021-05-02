#include "game.hpp"
#include "menu.cpp";
#include "play.cpp";
#include "sounds.h";
#include "maze.h";

int SCREEN_WIDTH=3840;
int SCREEN_HEIGHT=2160;

using namespace std;

vector<Menu*> menuList;
play* playState=nullptr;
Menu* gameOver=nullptr;
Maze* maze=nullptr;

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
				overback=Texture::LoadT("./../assets/gameover.jpg",renderer);
				
				if (menuback==NULL){
					running=false;
					cout<<"Error:Couldn't initialize background image\n";
					cout<<IMG_GetError()<<"\n";
				}
				
				maze = new Maze(SCREEN_WIDTH/100,SCREEN_HEIGHT/100,1,renderer);
				
				playState = new play("Play",1,gameback,renderer);
				
				Menu* startMenu = new Menu("Start",1,menuback,renderer);
				menuList.push_back(startMenu);
				
				Menu* pauseMenu = new Menu("Pause",2,menuback,renderer);
				menuList.push_back(pauseMenu);
				
				Menu* optionsMenu = new Menu("Options",3,menuback,renderer);
				menuList.push_back(optionsMenu);
				
				Menu* gameOver = new Menu("Game Over",4,overback,renderer);
				menuList.push_back(gameOver);
				
				state=0;
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
	}else if(state==-1){
		gameOver->handle_event(event,&state);
	}else{
		menuList[state-1]->handle_event(event,&state);
	}
}

void Game::process(){
	if (state==0){
		maze->update();
		playState->update(&state);
	}else if(state==5){
		running = false;
	}else if(state==-2){
		playState = new play("Play",1,gameback,renderer);
		maze->reinitialize();
		state = 0;
	}else{
		menuList[state-1]->update();
	}
}

void Game::render(){
	SDL_RenderClear(renderer);
	if(state==0){
		playState->render();
		maze->render(renderer);
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
