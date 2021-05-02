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

		SDL_Window *window;
		SDL_Texture* menuback= NULL,*gameback=NULL,*overback=NULL;
	
};
#endif

















