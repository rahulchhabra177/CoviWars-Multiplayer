#include "maze.h"
#include <time.h>
using namespace std;

Maze::Maze(int l,SDL_Renderer* localRenderer){
	lvl = l;
	wTexture = Texture::LoadT("./../assets/wall.png",localRenderer);
	dTexture = Texture::LoadT("./../assets/door.png",localRenderer);
	
	mazeCell.h = 100;
	mazeCell.w = 100;
	mazeCell.x = 0;
	mazeCell.y = 0;

	for(int i=0;i<m_width;i++){
		vector<int> v;
		for(int j=0;j<m_height;j++){
			v.push_back(1);
		}
		mazeData.push_back(v);
	}
	
	constructMaze();
	removeDeadEnds();
	setWinCondition();
}

void Maze::reinitialize(){
	for(int i=0;i<m_width;i++){
		for(int j=0;j<m_height;j++){
			mazeData[i][j] = 1;
		}
	}
	constructMaze();
	removeDeadEnds();
	setWinCondition();
}

void Maze::render(SDL_Renderer* renderer){
	for(int i=0;i<m_width;i++){
		mazeCell.x = (mazeCell.h)*i;
		for(int j=0;j<m_height;j++){
			mazeCell.y = (mazeCell.h)*j;
			if(mazeData[i][j]==1){
				SDL_RenderCopy(renderer,wTexture,NULL,&mazeCell);
			}else if(mazeData[i][j]==3){
				SDL_RenderCopy(renderer,dTexture,NULL,&mazeCell);
			}
		}
	}
}

int Maze::openCell(int i,int j){
	int n = -1;
	if(mazeData[i-1][j]==0){
		n=0;
	}
	if(mazeData[i][j+1]==0){
		if(n<0){
			n=1;
		}else{
			return -1;
		}
	}
	if(mazeData[i+1][j]==0){
		if(n<0){
			n=2;
		}else{
			return -1;
		}
	}
	if(mazeData[i][j-1]==0){
		if(n<0){
			n=3;
		}else{
			return -1;
		}
	}
	return n;	
}

void Maze::removeDeadEnds(){
	for(int i=1;i<m_width-1;i++){
		for(int j=1;j<m_height-1;j++){
			if(mazeData[i][j]==0){
				int n = openCell(i,j);
				if(n>=0){
					switch(n){
						case 0:  {
							if(i==m_width-1){
								if(j==1){
									mazeData[i][j+1]=0;
								}else{
									mazeData[i][j-1]=0;
								}
							}else{
								mazeData[i+1][j]=0;
							}
							break;
						}case 1: {
							if(j==1){
								if(i==1){
									mazeData[i+1][j]=0;
								}else{
									mazeData[i-1][j]=0;
								}
							}else{
								mazeData[i][j-1]=0;
							}
							break;
						}case 2: {
							if(i==1){
								if(j==1){
									mazeData[i][j+1]=0;
								}else{
									mazeData[i][j-1]=0;
								}
							}else{
								mazeData[i-1][j]=0;
							}
							break;
						}case 3: {
							if(j==m_height-1){
								if(i==1){
									mazeData[i+1][j]=0;
								}else{
									mazeData[i-1][j]=0;
								}
							}else{
								mazeData[i][j+1]=0;
							}
							break;
						}
					}
				}
			}
		}
	}
}

void Maze::update(){
	
}

void Maze::constructMaze(){
	stack<pair<int,int>> cells;
	srand(time(0));
	int x = 2*(rand()%((m_width-1)/2))+1;
	int y = 2*(rand()%((m_height-1)/2))+1;
	cells.push(make_pair(x,y));
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
	if(y+2<m_height){
		if(mazeData[x][y+2]==1){
			unvisited.push_back(2);
		}
	}
	if(x+2<m_width){
		if(mazeData[x+2][y]==1){
			unvisited.push_back(3);
		}
	}
	return unvisited;
}

void Maze::setWinCondition(){
	srand(time(0));
	while(true){
		int x = 2*(rand()%((m_width-1)/2))+1;
		int y = 2*(rand()%((m_height-1)/2))+1;
		if(x>m_width/2 && y>m_height/2){
			mazeData[x][y]=3;
			break;
		}
	}
}