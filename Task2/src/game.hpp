#ifndef GAME_HPP

#define GAME_HPP
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
using namespace std;


class Game{

	public:
		Game(char* title, int x,int y,int w,int h);
		void handle_event();
		void process();
		void render();
		void close();
		bool isRunning();
		bool running;
		SDL_Renderer *renderer;
		int state;

	private:
		int cnt=0; 

		SDL_Window *window;
		SDL_Texture* menuback= NULL,*gameback=NULL,*menu=NULL,*menu1=NULL,*logos=NULL;
	
};
#endif

//Phases of the game

// 1 : Start Menu
// 0 : Play 
// 2 : Pause
// 3 : Options
// 4 : Exit

















