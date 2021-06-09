#ifndef MAZE_H

#define MAZE_H
#include<bits/stdc++.h>
#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Maze{

	public:
		
		int m_width=27;			
		int m_height=21;
		int lvl = 1;
		SDL_Texture* wTexture = NULL;
		SDL_Texture* sTexture = NULL;
		SDL_Texture* dTexture = NULL;
		SDL_Texture* fTexture = NULL;
		SDL_Texture* vTexture = NULL;
		bool multiplayer=false;
		vector<vector<int>> mazeData;
		void reinitialize();
		Maze(int l,SDL_Renderer* localRenderer,bool multi,string mzData);
		void render(SDL_Renderer* renderer);
		SDL_Rect mazeCell,mazeEgg,fruitCell,vacCell;
		void update();
		string getMazeState();
		int numFruits=0, numVaccines=0, numEggs=0; 
		
	private:
		
		void constructMaze();
		void removeDeadEnds();
		int openCell(int i,int j);
		vector<int> neighbours(pair<int,int> coord);
		void setWinCondition();
		void placeFruits();
		void placeVaccine();
		void setParams();

};

#endif
