#include "DataWindow.h"
#include "game.hpp"
SDL_Rect heading;


DataWindow::DataWindow(){

	
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
			SDL_SetWindowFullscreen( window,SDL_WINDOW_FULLSCREEN);
			cout<<"Window Inititalised Successfully....\n";
			renderer=SDL_CreateRenderer(window,-1,0);

			if (renderer==NULL){
				running=false;
				cout<<"Error:Couldn't initialize Renderer\n";
			}
			else{
				cout<<"Renderer initialized Successfully...\n";
				SDL_SetRenderDrawColor(renderer,255,255,255,255);
				heading.x=0;
				heading.y=0;
				heading.w=300;
				heading.h=200;

				
					


			}
		}









}
}




void DataWindow::close(){
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}