#ifndef MAZE_H

#define MAZE_H
#include<bits/stdc++.h>
#include "./../texture/Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Maze{

	public:
		
		int m_width=27;			
		int m_height=21;
		int lvl = 1;
		int mazeTimer = 0;
		SDL_Texture* wTexture = NULL;
		SDL_Texture* sTexture = NULL;
		SDL_Texture* dTexture = NULL;
		SDL_Texture* fTexture = NULL;
		SDL_Texture* vTexture = NULL;
		SDL_Texture* qTexture = NULL;
		SDL_Texture* mTexture = NULL;
		SDL_Texture* kTexture = NULL;
		SDL_Texture* orangeWall = NULL;
		SDL_Texture* lTexture = NULL;
		bool multiplayer=false;
		vector<vector<int>> mazeData;
		void reinitialize();
		Maze(int l,SDL_Renderer* localRenderer,bool multi,string mzData);
		void render(SDL_Renderer* renderer);
		SDL_Rect mazeCell,mazeEgg,fruitCell,vacCell,quarCell,maskCell,keyCell,mazeLab;
		void update();
		string getMazeState();
		int numFruits=0, numVaccines=0, numEggs=0, numDeadends=0, numMasks=0, qSize=0 , extra_enemies=0; 
		void setWinCondition();
		void placeFruits();
		void placeVaccine();
		void setQuarantine();
		void placeMasks();
		void placeKey();
		bool keyEaten = false;

	private:
		
		void constructMaze();
		void removeDeadEnds();
		int openCell(int i,int j);
		vector<int> neighbours(pair<int,int> coord);
		void setParams();

};

#endif
