#include "game.hpp"
#include "Map.h";
#include "menu.cpp";
#include "play.cpp";


using namespace std;

pacman *mainplayer=nullptr,*enemy1=nullptr,*tile=nullptr;
Button *start_button=nullptr,*exit_button=nullptr,*logo=nullptr;

int SCREENWIDTH=3840;
int SCREENHEIGHT=2160;
int SPEED=20;

Map *lvl1=nullptr;

vector<State*> stateList;

Game::Game(char* title, int xcor,int ycor,int width_window,int height_window){
	int flag=SDL_WINDOW_SHOWN;
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
				
				start_button=new Button();
				exit_button=new Button();
				logo=new Button();
				
				play* playState = new play("Play");
				stateList.push_back(playState);
				
				vector<Button> newList;
				men* newMenu = new men("Start",newList);
				stateList.push_back(newMenu);
				
				menuback=Texture::LoadT("./../assets/welcome.jpg",renderer);
				gameback=Texture::LoadT("./../assets/black.jpg",renderer);
				logos=logo->LoadButtonFromImage("./../assets/logo.png",renderer,"LOGO");
				logo->set_cor(SCREENWIDTH/4,SCREENHEIGHT/20,SCREENWIDTH/10,SCREENHEIGHT/2);
				menu=start_button->LoadButtonFromImage("./../assets/start].png",renderer,"START");
				start_button->set_cor(297,358,49,217);
				menu1=exit_button->LoadButtonFromImage("./../assets/start].png",renderer,"EXIT");
				exit_button->set_cor(297,438,49,217);
				state=1;
				if (menuback==NULL){
					running=false;
					cout<<"Error:Couldn't initialize background image\n";
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
	cnt=(cnt+1)%20;
	if(cnt==0){
		enemy1->x++;
	}
	start_button->handle_event(event,&state);
	// exit_button->handle_event(event,&state);
	switch (event.type){
		case SDL_QUIT:	
			{running=false;
			break;}
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
			cout<<"button\n";
			int a,b;
			SDL_GetMouseState( &a, &b );
			cout<<a<<" "<<b<<"\n";
			break;	
		default:
			break;
	}
}

void Game::process(){
	if (state==1){
		mainplayer->update();
		enemy1->update();
	}
	//Add waiting animation
}

void Game::render(){
	SDL_RenderClear(renderer);
	if (state==0){
		SDL_RenderCopy(renderer,menuback,NULL,NULL);
		exit_button->render(renderer,menu1);
		logo->render(renderer,logos);
		start_button->render(renderer,menu);
	}
	else if(state==1){
		SDL_RenderCopy(renderer,gameback,NULL,NULL);
		mainplayer->render();
		enemy1->render();
		lvl1->RenderMap(renderer);
		// exit_button->render(renderer,menu1);
	}else if(state==2){
	
	}else if(state==3){
	
	}else{
		running = false;
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
