#ifndef BUTTON_H

#define BUTTON_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sounds.h"

class Button{
	
	public:
		Button(char* name, SDL_Renderer* renderer,int width,int height,char* path);
		char* label;
		int s_width,s_height;
		SDL_Rect dest;
		SDL_Texture* texture;
		//int cur_color = 0;
		//std::vector<SDL_Texture*> colors;
		void handle_event(int*state,SoundClass* m,bool music_on/*,SDL_Event*/);
		bool isInside(int a,int b);
		void render(SDL_Renderer *renderer);
		void set_cor(int x,int y,int w,int h);
		void set_rect(int x,int y,int w,int h);
		//void set_original();
};
#endif
