#include "game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Texture.h";
using namespace std;



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
    			}
			}

		}
	}
	else{
		cout<<"Shit!!\n";
		running=false;
	}
}


void Game::handle_event(){

}


void Game::process(){
	cnt++;
	cout<<cnt<<"\n";
}

void Game::render(){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,backg,NULL,NULL);
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