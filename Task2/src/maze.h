#ifndef MAZE_H

#define MAZE_H
#include<bits/stdc++.h>
#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Maze{

	public:
		
		int m_width=38;
		int m_height=21;
		int lvl=1;
		SDL_Texture* wTexture = NULL;
		SDL_Texture* sTexture = NULL;
		vector<vector<int>> mazeData;
		void reinitialize();
		Maze(int s_width,int s_height,int l,SDL_Renderer* localRenderer);
		void render(SDL_Renderer* renderer);
		SDL_Rect mazeCell,maze_egg;
		void update();
		
	private:
		
		void constructMaze();
		vector<int> neighbours(pair<int,int> coord);

};

#endif

