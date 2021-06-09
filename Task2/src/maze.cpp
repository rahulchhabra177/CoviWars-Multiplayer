#include "maze.h"
#include <time.h>
using namespace std;
bool maze_debug=true;

Maze::Maze(int l,SDL_Renderer* localRenderer,bool multi,string mzData){
	if (maze_debug)cout<<"Maze.cpp.cpp:Maze\n";
	wTexture = Texture::LoadT("./../assets/wall.png",localRenderer);
	sTexture= Texture::LoadT("./../assets/tab.xcf",localRenderer);
	dTexture = Texture::LoadT("./../assets/door.png",localRenderer);
	fTexture = Texture::LoadT("./../assets/fruit.png",localRenderer);
	vTexture = Texture::LoadT("./../assets/vaccine.jpeg",localRenderer);
	multiplayer = multi;

	mazeCell.h = 100;
	mazeCell.w = 100;
	mazeCell.x = 0;
	mazeCell.y = 0;
	mazeEgg.h = 20;
	mazeEgg.w = 20;
	mazeEgg.x = 0;
	mazeEgg.y = 0;
	fruitCell.h = 30;
	fruitCell.w = 0;
	fruitCell.x = 0;
	fruitCell.y = 0;
	vacCell.h = 30;
	vacCell.w = 30;
	vacCell.x = 0;
	vacCell.y = 0;

	lvl = l;
	setParams();

	numEggs = numEggs - numFruits - numVaccines;

	if(mzData=="" || !multiplayer){
		for(int i=0;i<m_width;i++){
			vector<int> v;
			for(int j=0;j<m_height;j++){
				v.push_back(1);
			}
			mazeData.push_back(v);
		}
		
		srand(time(0));
		constructMaze();
		removeDeadEnds();
		placeFruits();
		placeVaccine();

		if(!multiplayer){
			setWinCondition();
		}
	}else{
		int k=0;
		if (mzData.size()<568){
			cout<<mzData<<"\n";
			cout<<"Data Insufficient\n";
			exit(1);
		}
		cout<<"mazeData->size:"<<mzData.size()<<"\n";

		for(int i=0;i<m_width;i++){
			vector<int> v;
			for(int j=0;j<m_height;j++){
				// cout<<mzData[k];
				v.push_back(stoi(mzData.substr(k+1,1)));
				k++;
			}
			mazeData.push_back(v);
		}
	}
}

string Maze::getMazeState(){
	cout<<"gettingMazeState\n";
	string s="";
	for (int i=0;i<m_width;i++){
		for(int j=0;j<m_height;j++){
			s+=to_string(mazeData[i][j]);
		}
	}
	return s;
}

void Maze::reinitialize(){
	if (maze_debug)cout<<"Maze.cpp.cpp:reinitialize\n";
	
	for(int i=0;i<m_width;i++){
		for(int j=0;j<m_height;j++){
			if(mazeData[i][j]==2){
				mazeData[i][j]=0;
			}
		}
	}
	
	setWinCondition();
}

void Maze::render(SDL_Renderer* renderer){
	if (maze_debug)cout<<"Maze.cpp.cpp:render\n";
	for(int i=0;i<m_width;i++){
		mazeCell.x = (mazeCell.h)*i;
		mazeEgg.x = (mazeCell.h)*i+(mazeCell.h)/2-mazeEgg.h/2;
		fruitCell.x = (mazeCell.h)*i+(mazeCell.h)/2-fruitCell.h/2;
		vacCell.x = (mazeCell.h)*i+(mazeCell.h)/2-vacCell.h/2;
		for(int j=0;j<m_height;j++){
			mazeCell.y = (mazeCell.h)*j;
			mazeEgg.y = (mazeCell.h)*j+(mazeCell.h)/2-mazeEgg.h/2;
			fruitCell.y = (mazeCell.h)*j+(mazeCell.h)/2-fruitCell.h/2;
			vacCell.y = (mazeCell.h)*j+(mazeCell.h)/2-vacCell.h/2;
			if(mazeData[i][j]==0){
				SDL_RenderCopy(renderer,sTexture,NULL,&mazeEgg);			
			}else if(mazeData[i][j]==1){
				SDL_RenderCopy(renderer,wTexture,NULL,&mazeCell);
			}else if(mazeData[i][j]==3){
				SDL_RenderCopy(renderer,dTexture,NULL,&mazeCell);
			}else if(mazeData[i][j]==4){
				SDL_RenderCopy(renderer,fTexture,NULL,&fruitCell);
			}else if(mazeData[i][j]==5){
				SDL_RenderCopy(renderer,vTexture,NULL,&vacCell);
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
	if (maze_debug)cout<<"Maze.cpp.cpp:removeDeadEnds\n";
	for(int i=1;i<m_width-1;i++){
		for(int j=1;j<m_height-1;j++){
			if(mazeData[i][j]==0){
				int n = openCell(i,j);
				if(n>=0){
					switch(n){
						case 0:  {
							if(i==m_width-2){
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
							if(j==m_height-2){
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
	if (maze_debug)cout<<"Maze.cpp.cpp:Maze\n";
	stack<pair<int,int>> cells;
	int x = 2*(rand()%(m_width/2))+1;
	int y = 2*(rand()%(m_height/2))+1;
	cells.push(make_pair(x,y));
	numEggs++;
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
			numEggs+=2;
		}
	}
}

vector<int> Maze::neighbours(pair<int,int> p){
	if (maze_debug)cout<<"Maze.cpp.cpp:neighbours\n";
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

void Maze::placeFruits(){
	for(int i=0;i<numFruits;i++){
		while(true){
			int x = 2*(rand()%((m_width-1)/2))+1;
			int y = 2*(rand()%((m_height-1)/2))+1;
			if(mazeData[x][y]==0){
				mazeData[x][y]=4;
				break;
			}
		}
	}
}

void Maze::placeVaccine(){
	for(int i=0;i<numVaccines;i++){
		while(true){
			int x = 2*(rand()%((m_width-1)/2))+1;
			int y = 2*(rand()%((m_height-1)/2))+1;
			if(mazeData[x][y]==0){
				mazeData[x][y]=5;
				break;
			}
		}
	}
}

void Maze::setParams(){
	switch(lvl){
		case 1:{numFruits=7;numVaccines=3;break;}
		case 2:{numFruits=6;numVaccines=2;break;}
		case 3:{numFruits=5;numVaccines=2;break;}
		case 4:{numFruits=4;numVaccines=1;break;}
		case 5:{numFruits=3;numVaccines=1;break;}
	}
}