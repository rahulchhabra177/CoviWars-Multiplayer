#include "game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Texture.h";
#include "pacman.h";
using namespace std;
int rooot=0;
pacman * mainplayer=nullptr,*enemy1=nullptr;
int SCREENWIDTH=400;
int SCREENHEIGHT=300;

Game::Game(){

}

void Game::init(char* title, int xcor,int ycor,int width_window,int height_window){
	int flag=SDL_WINDOW_SHOWN;
	if (SDL_Init(SDL_INIT_EVERYTHING)==0){
		if (true){
			cout<<"SDL Initialised succesfully....\n";
		}
		window=SDL_CreateWindow(title,xcor,ycor,width_window,height_window,flag);

		if (window==NULL){
			running=false;
			cout<<"Error:Couldn't initialize window\n";
		}
		else{
			if (true){
				cout<<"Window Inititalised Successfully....\n";
			}
			renderer=SDL_CreateRenderer(window,-1,0);
			if (renderer==NULL){
				running=false;
				cout<<"Error:Couldn't initialize Renderer\n";
			}
			else{
				if (true){
					cout<<"Renderer initialized Successfully...\n";
				}
				SDL_SetRenderDrawColor(renderer,255,255,255,255);
				backg=Texture::LoadT("/home/rahul/Downloads/welcome.bmp",renderer);
				if (backg==NULL){
					running=false;
					cout<<"Error:Couldn't initialize image\n";
				}
				
				else{
				running=true;
				mainplayer=new pacman("./../assets/hero.bmp",renderer,SCREENWIDTH/2,SCREENHEIGHT,false);
				enemy1=new pacman("/home/rahul/Downloads/try.bmp",renderer,0,0,true);
				
    			}
			}

		}
	}
	else{
		running=false;
	}
}


void Game::handle_event(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type){
		case SDL_QUIT:	
			running=false;
			break;
		case SDL_KEYDOWN:
			switch ( event.key.keysym.sym ){
				case SDLK_UP:
					mainplayer->y--;
					break;
				case SDLK_DOWN:
					mainplayer->y++;
					break;
				case SDLK_RIGHT:
					mainplayer->x++;
					break;
				case SDLK_LEFT:
					mainplayer->x--;
					break;
				default:
					break;					
			}	
		default:
			break;
	}

}


void Game::process(){
	mainplayer->update();
	enemy1->update();
	

}

void Game::render(){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,backg,NULL,NULL);
	mainplayer->render();
	enemy1->render();
	

	SDL_RenderPresent(renderer);
}

void Game::close(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	if (true){
		cout<<"Game Quitted...\n";
	}

}
bool Game::isrunning(){
	return running;
}