#ifndef BUTTON_H

#define BUTTON_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include "sounds.h"
#include "Texture.h"

#include <SDL2/SDL_ttf.h> 
class Button{
	
	public:
		Button(char* name, SDL_Renderer* renderer,int width,int height);
		Button(char* name,char* name2, SDL_Renderer* renderer,int width,int height);
		char* label;
		SDL_Rect dest;
		bool isSelected=false;
		SDL_Texture* texture;
		int s_width,s_height;
		std::vector<SDL_Texture*> colors[2];
		int cur_color=0;
		void handle_event(int*state,SoundClass* m,int* prevstate,SDL_Event e);
		bool isInside(int a,int b);
		void render(SDL_Renderer *renderer);
		void set_cor(int x,int y,int a ,int b);
		void set_rect(int a,int b,int q,int w);
		void set_original();

};
#endif
