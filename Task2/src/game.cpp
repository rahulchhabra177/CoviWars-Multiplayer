#include "game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Texture.h";
#include "pacman.h";
#include "button.h";
#include "Map.h";
using namespace std;
int rooot=0;
pacman * mainplayer=nullptr,*enemy1=nullptr,*tile=nullptr;
Button* start_button=nullptr;
int SCREENWIDTH=400;
int SCREENHEIGHT=300;
Map *lvl1=nullptr;
SDL_Rect dst,src;
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
				// dst={32,32,32,32};
				dst.x=100;dst.y=100;dst.h=80;dst.w=180;
				src.x=150;src.y=75;src.h=60,src.w=323;
				start_button=new Button();
				menuback=Texture::LoadT("./../assets/welcome.jpg",renderer);
				gameback=Texture::LoadT("./../assets/black.jpg",renderer);
				menu=start_button->LoadButtonFromImage("./../assets/menu.jpg",renderer,"Play",160,80,60,300);
				start_button->set_cor(297,358,49,217);
				state=0;
				if (menuback==NULL){
					running=false;
					cout<<"Error:Couldn't initialize image\n";
					cout<<IMG_GetError()<<"\n";
				}
				
				else{
					
				running=true;
				mainplayer=new pacman("./../assets/hero.bmp",renderer,SCREENWIDTH/2,SCREENHEIGHT,false);
				enemy1=new pacman("./../assets/corona.xcf",renderer,0,0,true);
				lvl1=new Map();
				lvl1->LoadMap(renderer);
				
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
	start_button->handle_event(event,&state);
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
		case SDL_MOUSEBUTTONDOWN:
			cout<<"butten\n";
			int a,b;
			SDL_GetMouseState( &a, &b );
			cout<<a<<" "<<b<<"\n";	
		default:
			break;
	}
// backg=Texture::LoadT("/home/rahul/Downloads/hell.bmp",renderer);
}

void Game::process(){
	if (state==1){
		mainplayer->update();
		enemy1->update();
}
	

}
//state=0 means menu and 1 means game
void Game::render(){

	SDL_RenderClear(renderer);
	if (state==0){
		SDL_RenderCopy(renderer,menuback,NULL,NULL);
		// SDL_RenderCopy(renderer,menu,&src,&dst);
		start_button->render(renderer,menu);
	}
	else{

		SDL_RenderCopy(renderer,gameback,NULL,NULL);
	mainplayer->render();
	enemy1->render();
	lvl1->RenderMap(renderer);
	}
	

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