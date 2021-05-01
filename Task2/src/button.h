#ifndef BUTTON_H

#define BUTTON_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>

class Button{
	
	public:
		Button(char* name, SDL_Renderer* renderer, char* path);
		char* label;
		SDL_Rect dest;
		SDL_Texture* texture;
		void handle_event(int*state);
		bool isInside(int a,int b);
		void render(SDL_Renderer *renderer);
		void set_cor(int x,int y,int a ,int b);

};
#endif
