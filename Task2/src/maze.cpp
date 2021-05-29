#include "maze.h"
using namespace std;
bool debug_maze=false;
Maze::Maze(int l,SDL_Renderer* localRenderer){
	if (debug_maze)cout<<"maze.cpp:Maze\n";
	lvl = l;
	sTexture = Texture::LoadT("./../assets/wall.png",localRenderer);
	wTexture = Texture::LoadT("./../assets/wall.jpeg",localRenderer);
	
	mazeCell.h = 40;
	mazeCell.w = 40;
	mazeCell.x = 0;
	mazeCell.y = 0;

	maze_egg.h = 5;
	maze_egg.w = 5;
	maze_egg.x = 0;
	maze_egg.y = 0;

	m_width = 24;
	m_height = 18;
	for(int i=0;i<m_width;i++){
		vector<int> v;
		for(int j=0;j<m_height;j++){
			v.push_back(1);
		}
		mazeData.push_back(v);
	}
	
	constructMaze();
	cout<<"Maze"<<m_width<<" "<<m_height<<"\n"; 
	for (int i=1;i<4;i++){
		for (int j=1;j<4;j++){
			mazeData[i][j]=0;
		}
	}

}

void Maze::reinitialize(){
	if (debug_maze)cout<<"maze.cpp:reinitialize\n";
	for(int i=0;i<m_width;i++){
		for(int j=0;j<m_height;j++){
			mazeData[i][j] = 1;
		}
	}
	constructMaze();
}

void Maze::render(SDL_Renderer* renderer){
	if (debug_maze)cout<<"maze.cpp:render\n";
	for(int i=0;i<m_width;i++){
		mazeCell.x = (mazeCell.h)*(i)+120;
		maze_egg.x=(mazeCell.h)*i+mazeCell.h/2;
		for(int j=0;j<m_height;j++){
			mazeCell.y = (mazeCell.h)*(j);
			maze_egg.y=(mazeCell.h)*i+mazeCell.h/2;
			if(mazeData[i][j]==1){
				SDL_RenderCopy(renderer,wTexture,NULL,&mazeCell);
			}
			else if (mazeData[i][j]==2){
				SDL_RenderCopy(renderer,sTexture,NULL,&maze_egg);
			}
		}
	}
	mazeCell.x=m_width*(mazeCell.h)+120;
	for(int i=0;i<m_height;i++){
		mazeCell.y = (mazeCell.h)*i;
		SDL_RenderCopy(renderer,wTexture,NULL,&mazeCell);
	}

	mazeCell.y=m_height*(mazeCell.w);
	for(int i=0;i<=m_width;i++){
		mazeCell.x = (mazeCell.h)*i+120;
		SDL_RenderCopy(renderer,wTexture,NULL,&mazeCell);
	}
}

void Maze::update(){
if (debug_maze)cout<<"maze.cpp:update\n";
}

void Maze::constructMaze(){
	if (debug_maze)cout<<"maze.cpp::constructMaze\n";
	stack<pair<int,int>> cells;
	cells.push(make_pair(1,1));
	while(!cells.empty()){
		vector<int> unvisited = neighbours(cells.top());
		int x = cells.top().first;
		int y = cells.top().second;
		int n = unvisited.size();
		if(n==0){
			cells.pop();
		}else{
			int k = unvisited[rand()%n];
			switch(k){
				case 0:
					mazeData[x][y-1] = 0;
					y = y - 2;
					break;
				case 1:
					mazeData[x-1][y] = 0;
					x = x - 2;
					break;
				case 2:
					mazeData[x][y+1] = 0;
					y = y + 2;
					break;
				case 3:
					mazeData[x+1][y] = 0;
					x = x + 2;
					break;
			}
			mazeData[x][y] = 0;
			cells.push(make_pair(x,y));
		}
	}
}

vector<int> Maze::neighbours(pair<int,int> p){
if (debug_maze)cout<<"maze.cpp::neighbours\n";

	vector<int> unvisited;
	int x = p.first;
	int y = p.second;
	if(y>=2){
		if(mazeData[x][y-2]==1){
			unvisited.push_back(0);
		}
	}
	if(x>=2){
		if(mazeData[x-2][y]==1){
			unvisited.push_back(1);
		}
	}
	if(y+2<=m_height){
		if(mazeData[x][y+2]==1){
			unvisited.push_back(2);
		}
	}
	if(x+2<=m_width){
		if(mazeData[x+2][y]==1){
			unvisited.push_back(3);
		}
	}
	return unvisited;
}
