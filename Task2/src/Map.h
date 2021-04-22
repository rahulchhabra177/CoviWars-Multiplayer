#ifndef MAP_H

#define MAP_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include "button.h";

class Map{
public:
	int mat[20][20];
	void LoadMap(SDL_Renderer*renderer);
	void RenderMap(SDL_Renderer *renderer);
	SDL_Texture* text1,*text2;
	Button* tape=nullptr;
};
#endif
