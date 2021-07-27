#ifndef GAME_HPP

#define GAME_HPP
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include "./../playstate/play.cpp";
using namespace std;


class Game{

	public:
		Game(string title, int x,int y,int h,int w,bool isServer);
		void handle_event();
		void process();
		void render();
		void close();
		bool isRunning();
		bool running;
		SDL_Renderer *renderer;
		int state,prevstate;
		int player_id;
		bool isServer=false;
		int s_width,s_height;
		
	private:

		SDL_Window *window;
		SDL_Texture* menuback= NULL,*gameback=NULL,*overback=NULL,*winback=NULL;
	
};
#endif
















