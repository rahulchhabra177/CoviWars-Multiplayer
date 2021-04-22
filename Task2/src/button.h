#ifndef BUTTON_H

#define BUTTON_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>

class Button{
	
	public:
		char* label;
		SDL_Rect dest;
		SDL_Texture * LoadButtonFromImage(char * path,SDL_Renderer* renderer,char* label_1);
		void handle_event(SDL_Event e,int*state);
		bool isInside(int a,int b);
		void render(SDL_Renderer *renderer,SDL_Texture* tect);
		void set_cor(int x,int y,int a ,int b);

};
#endif
