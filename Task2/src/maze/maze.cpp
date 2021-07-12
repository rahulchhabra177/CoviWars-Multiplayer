#include "./../maze/maze.h"
#include <time.h>
using namespace std;
bool maze_debug=false;

//To keep the single player version of this game fresh and interesting, we 
//have implemented a hidden walls feature, in which after every fixed interval,
//some walls are converted to empty cells and also vice versa, in such a way
//that the overall maze remains connected, so that the maze still remains 
//solvable
vector<pair<int,int>> hiddenWalls; 

//We have stored the maze as a matrix of size 27*21, all of whose cells will
//determine what type of cell will be rendered on that space, such as
//
// 0: Egg/Tablet through which pacman can pass and collect points
// 1: Wall, through which pacman cannot pass
// 2: Empty cell, through which the pacman passes normally 
// 3: Door cell, which is used by the pacman to pass to the next level, if
//    certain conditions are met
// 4: Fruit cell, which the pacman can collect as a powerup. A fruit turns
//    the pacman invincible for some time, and thus untargetable by enemies
// 5: Vaccine cell. This powerup enables pacman to eat enemies.
// 6: Mask cell. The pacman can use this powerup to decrease the damage 
//    caused by enemies and to survive on quarantine cells.
// 7: Quarantine cell. A hazardous cell which incrementally decreases the 
//    health points of pacman, if it stands on it for too long without a mask.
// 8: A key, which is required to pass through the door to the next level.
// >8: For animation of hidden walls

//Maze constructor
Maze::Maze(int l,SDL_Renderer* localRenderer,bool multi,string mzData){
	if (maze_debug)cout<<"Maze.cpp.cpp:Maze\n";

	//Initialising the textures of different parts of the maze
	wTexture = Texture::LoadT("./../assets/maze_items/wall.jpeg",localRenderer);			//Wall
	sTexture= Texture::LoadT("./../assets/maze_items/tab.xcf",localRenderer);				//Egg/Tablet
	dTexture = Texture::LoadT("./../assets/maze_items/door.png",localRenderer);				//Door
	fTexture = Texture::LoadT("./../assets/maze_items/apple.png",localRenderer);			//Fruit
	vTexture = Texture::LoadT("./../assets/maze_items/vaccine.png",localRenderer);			//Vaccine
	mTexture = Texture::LoadT("./../assets/maze_items/mask.png",localRenderer);				//Mask
	kTexture = Texture::LoadT("./../assets/maze_items/key.png",localRenderer);				//Key
	qTexture = Texture::LoadT("./../assets/maze_items/redBlur.png",localRenderer);			//Quarantine/Hazardous cell
	orangeWall = Texture::LoadT("./../assets/maze_items/wall.png",localRenderer);			//For animation of hidden wall
	lTexture = Texture::LoadT("./../assets/maze_items/lab.xcf",localRenderer);	
	//Checking if the current play state is single player or multi player
	multiplayer = multi;

	//Size paramaters of the cells to be used for rendering all the 
	//different textures mentioned above

	//Wall cell
	mazeCell.h = 100;
	mazeCell.w = 100;
	mazeCell.x = 0;
	mazeCell.y = 0;

	//Lab cell
	mazeLab.h = 300;
	mazeLab.w = 300;
	mazeLab.x = 100*(m_width-1);
	mazeLab.y = 100*(m_height-4);

	//Quarantine Cell
	quarCell.h = 100;
	quarCell.w = 100;
	quarCell.x = 0;
	quarCell.y = 0;

	//Egg/Tablet Cell
	mazeEgg.h = 20;
	mazeEgg.w = 20;
	mazeEgg.x = 0;
	mazeEgg.y = 0;

	//Fruit Cell
	fruitCell.h = 100;
	fruitCell.w = 100;
	fruitCell.x = 0;
	fruitCell.y = 0;

	//Vaccine Cell
	vacCell.h = 100;
	vacCell.w = 100;
	vacCell.x = 0;
	vacCell.y = 0;

	//Mask Cell
	maskCell.h = 100;
	maskCell.w = 100;
	maskCell.x = 0;
	maskCell.y = 0;

	//Key Cell
	keyCell.h = 100;
	keyCell.w = 100;
	keyCell.x = 0;
	keyCell.y = 0;

	//Initialising the number of various items of the maze depending on the
	//level of the game, like number of powerups, size of quarantine cell, etc.
	lvl = l;
	setParams();

	//Depending on whether the game is single player or multiplayer, and 
	//further whether it is a server or a client, the maze will either be 
	//completely constructed from scratch or the maze created in the server
	//will be sent to other clients 
	if(mzData=="" || !multiplayer){

		//The maze will be constructed if the game is single player or if
		//the current instance of the game is a server
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
		setQuarantine();
		
		if (multiplayer){
			for (int i=0;i<numFruits;i++){
				placeFruits();
			}	
			for (int i=0;i<numVaccines;i++){
				placeVaccine();
			}
			for (int i=0;i<numMasks;i++){
				placeMasks();
			}
		}
		
		numEggs = 0;

		for(int i=0;i<m_width;i++){
			for(int j=0;j<m_height;j++){
				if(mazeData[i][j]==0){
					numEggs++;
				}
			}
		}

	}else{

		//In case the current game instance is a client, it will receive the
		//structure of the maze from the server
		int k=0;
		if (mzData.size()<568){
			cout<<mzData<<"\n";
			cout<<"Data Insufficient\n";
			exit(1);
		}

		for(int i=0;i<m_width;i++){
			vector<int> v;
			for(int j=0;j<m_height;j++){
				v.push_back(stoi(mzData.substr(k+1,1)));
				k++;
			}
			mazeData.push_back(v);
			for(int j=0;j<v.size();j++){
				if(v[j]==0){
					numEggs++;
				}
			}
		}
	}
}

//Converting the structure of the maze into a string to be sent to other
//clients through the network manager
string Maze::getMazeState(){
	string s="";
	for (int i=0;i<m_width;i++){
		for(int j=0;j<m_height;j++){
			s+=to_string(mazeData[i][j]);
		}
	}
	return s;
}

//To reinitialise a level without constructing a new maze if a player wishes
//to play again in case he/she fails
void Maze::reinitialize(){
	if (maze_debug)cout<<"Maze.cpp.cpp:reinitialize\n";
	
	for(int i=0;i<m_width;i++){
		for(int j=0;j<m_height;j++){
			if(mazeData[i][j]!=1){
				mazeData[i][j]=0;
			}
		}
	}

	setQuarantine();
	
}

//For rendering the different types of cells on the screen at proper positions
void Maze::render(SDL_Renderer* renderer){
	if (maze_debug)cout<<"Maze.cpp.cpp:render\n";
	for(int i=0;i<m_width;i++){
		mazeCell.x = (mazeCell.h)*i;
		quarCell.x = (mazeCell.h)*i;
		mazeEgg.x = (mazeCell.h)*i+(mazeCell.h)/2-mazeEgg.h/2;
		fruitCell.x = (mazeCell.h)*i+(mazeCell.h)/2-fruitCell.h/2;
		vacCell.x = (mazeCell.h)*i+(mazeCell.h)/2-vacCell.h/2;
		maskCell.x = (mazeCell.h)*i+(mazeCell.h)/2-maskCell.h/2;
		keyCell.x = (mazeCell.h)*i+(mazeCell.h)/2-keyCell.h/2;
		for(int j=0;j<m_height;j++){
			mazeCell.y = (mazeCell.h)*j;
			quarCell.y = (mazeCell.h)*j;
			mazeEgg.y = (mazeCell.h)*j+(mazeCell.h)/2-mazeEgg.h/2;
			fruitCell.y = (mazeCell.h)*j+(mazeCell.h)/2-fruitCell.h/2;
			vacCell.y = (mazeCell.h)*j+(mazeCell.h)/2-vacCell.h/2;
			maskCell.y = (mazeCell.h)*j+(mazeCell.h)/2-maskCell.h/2;
			keyCell.y = (mazeCell.h)*j+(mazeCell.h)/2-keyCell.h/2;
			if(mazeData[i][j]==0){
				SDL_RenderCopy(renderer,sTexture,NULL,&mazeEgg);			
			}else if(mazeData[i][j]==1){
				if (multiplayer){
					SDL_RenderCopy(renderer,wTexture,NULL,&mazeCell);
				}
				else if ((i!=m_width-1 || j!=m_height-2)){
					
					SDL_RenderCopy(renderer,wTexture,NULL,&mazeCell);
				}
			}else if(mazeData[i][j]==3){
				SDL_RenderCopy(renderer,dTexture,NULL,&mazeCell);
			}else if(mazeData[i][j]==4){
				SDL_RenderCopy(renderer,fTexture,NULL,&fruitCell);
			}else if(mazeData[i][j]==5){
				SDL_RenderCopy(renderer,vTexture,NULL,&vacCell);
			}else if(mazeData[i][j]==6){
				SDL_RenderCopy(renderer,mTexture,NULL,&maskCell);
			}else if(mazeData[i][j]==7){
				SDL_RenderCopy(renderer,qTexture,NULL,&quarCell);
			}else if(mazeData[i][j]==8){
				SDL_RenderCopy(renderer,kTexture,NULL,&keyCell);
			}else if(mazeData[i][j]==9){
				SDL_RenderCopy(renderer,orangeWall,NULL,&mazeCell);
				mazeData[i][j]=0;
			}else if(mazeData[i][j]==10){
				SDL_RenderCopy(renderer,orangeWall,NULL,&mazeCell);
				mazeData[i][j]=1;
			}else if(mazeData[i][j]>10){
				SDL_RenderCopy(renderer,orangeWall,NULL,&mazeCell);
				mazeData[i][j]-=2;
			}
			
		}
	}
	if (!multiplayer){
		mazeLab.y=100*(m_height-4);
		mazeLab.x=100*(m_width);
		mazeLab.h=400;
		SDL_RenderCopy(renderer,wTexture,NULL,&mazeLab);
		mazeLab.y=100*(m_height-4);
		mazeLab.x=100*(m_width-1);
		mazeLab.h=300;
		SDL_RenderCopy(renderer,lTexture,NULL,&mazeLab);
	}
	// SDL_RenderCopy(renderer,lTexture,NULL,&mazeLab);

}

//This function checks whether the (i,j)th cell is a dead end or not. A dead
//end is an open cell surrounded by three walls. This function returns:
// -1: If the given cell is not a dead end
//  0: If only the left cell (i-1,j) is open
//  1: If only the bottom cell (i,j+1) is open
//  2: If only the right cell (i+1,j) is open
//  3: If only the top cell (i,j-1) is open

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

//This method removes some or all of the dead ends of the maze, to provide a
//fair chance to the player for winning. Because the originally created maze
//is a tree as it is generated by a DFS, and so there is only one path from 
//one point to another in the maze, making it significantly harder for the 
//player to complete the level in presence of enemies.
void Maze::removeDeadEnds(){
	if (maze_debug)cout<<"Maze.cpp.cpp:removeDeadEnds\n";
	int counter=0;
	for(int i=1;i<m_width-1;i++){
		for(int j=1;j<m_height-1;j++){
			if(mazeData[i][j]==0){
				int n = openCell(i,j);
				if(n>=0){
					switch(n){
						case 0:  {
							if(i==m_width-2){
								if(j==1){
									if(counter==0){
										mazeData[i][j+1]=0;
									}
								}else{
									if(counter==0){
										mazeData[i][j-1]=0;
									}
								}
							}else{
								if(counter==0){
									mazeData[i+1][j]=0;
								}
							}
							if(i!=m_width-2){
								hiddenWalls.push_back(make_pair(i+1,j));
							}
							if(j!=1){
								hiddenWalls.push_back(make_pair(i,j-1));
							}
							if(j!=m_height-2){
								hiddenWalls.push_back(make_pair(i,j+1));
							}
							break;
						}case 1: {
							if(j==1){
								if(i==1){
									if(counter==0){
										mazeData[i+1][j]=0;
									}
								}else{
									if(counter==0){
										mazeData[i-1][j]=0;
									}
								}
							}else{
								if(counter==0){
									mazeData[i][j-1]=0;
								}
							}
							if(i!=1){
								hiddenWalls.push_back(make_pair(i-1,j));
							}
							if(j!=1){
								hiddenWalls.push_back(make_pair(i,j-1));
							}
							if(i!=m_width-2){
								hiddenWalls.push_back(make_pair(i+1,j));
							}
							break;
						}case 2: {
							if(i==1){
								if(j==1){
									if(counter==0){
										mazeData[i][j+1]=0;
									}
								}else{
									if(counter==0){
										mazeData[i][j-1]=0;
									}
								}
							}else{
								if(counter==0){
									mazeData[i-1][j]=0;
								}
							}
							if(i!=1){
								hiddenWalls.push_back(make_pair(i-1,j));
							}
							if(j!=1){
								hiddenWalls.push_back(make_pair(i,j-1));
							}
							if(j!=m_height-2){
								hiddenWalls.push_back(make_pair(i,j+1));
							}
							break;
						}case 3: {
							if(j==m_height-2){
								if(i==1){
									if(counter==0){
										mazeData[i+1][j]=0;
									}
								}else{
									if(counter==0){
										mazeData[i-1][j]=0;
									}
								}
							}else{
								if(counter==0){
									mazeData[i][j+1]=0;
								}
								hiddenWalls.push_back(make_pair(i,j+1));
							}
							if(i!=1){
								hiddenWalls.push_back(make_pair(i-1,j));
							}
							if(j!=m_height-2){
								hiddenWalls.push_back(make_pair(i,j+1));
							}
							if(i!=m_width-2){
								hiddenWalls.push_back(make_pair(i+1,j));
							}
							break;
						}
					}
					counter=(counter+1)%lvl;
				}
			}
		}
	}
}

//This update function is useful for the hidden walls feature
void Maze::update(){
	if(!multiplayer){
		mazeTimer++;
		if(mazeTimer==60*(6-lvl)){
			mazeTimer=0;
			int n = rand()%hiddenWalls.size();
			pair<int,int> p = hiddenWalls[n];
			mazeData[p.first][p.second] = (mazeData[p.first][p.second]==0 || mazeData[p.first][p.second]==2)?60:59;
		}
	}
}

//This function constructs a maze, given a matrix of some size. It uses a 
//randomised DFS algorithm, in which the initial maze is taken to full of 
//walls(signifying unexplored part of the maze). Starting from a random point 
//in a maze, we start exploring other cells, until all the cells are explored
//The explored cells of the matrix are the open/empty cells which the pacman
//can use to move around 
void Maze::constructMaze(){
	if (maze_debug)cout<<"Maze.cpp.cpp:Maze\n";
	stack<pair<int,int>> cells;
	int x = 2*(rand()%(m_width/2))+1;
	int y = 2*(rand()%(m_height/2))+1;
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

//A helper function for the construction of the maze, which for a given
//co-ordinate (in pair form), returns the unexplored neighbours
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
			if(mazeData[x][y]==0){
				numEggs--;
			}
			mazeData[x][y]=3;
			break;
		}
	}
}

void Maze::placeFruits(){
		while(true){
			int x = 2*(rand()%((m_width-1)/2))+1;
			int y = 2*(rand()%((m_height-1)/2))+1;
			if(mazeData[x][y]==0){
				mazeData[x][y]=4;
				break;
			}
		}
}

void Maze::placeVaccine(){
		while(true){
			int x = 2*(rand()%((m_width-1)/2))+1;
			int y = 2*(rand()%((m_height-1)/2))+1;
			if(mazeData[x][y]==0){
				mazeData[x][y]=5;
				break;
		}
	}
}

void Maze::placeMasks(){
		while(true){
			int x = 2*(rand()%((m_width-1)/2))+1;
			int y = 2*(rand()%((m_height-1)/2))+1;
			if(mazeData[x][y]==0){
				mazeData[x][y]=6;
				break;
			}
		}
}
 
void Maze::placeKey(){
	while(true){
		int x = 2*(rand()%((m_width-1)/2))+1;
		int y = 2*(rand()%((m_height-1)/2))+1;
		if(mazeData[x][y]==0 || mazeData[x][y]==2 ){
			if(x<m_width/2 && y<m_height/2){
				mazeData[x][y]=8;
				break;
			}
		}
	}
}

void Maze::setParams(){
	switch(lvl){
		case 1:{numFruits=7;numVaccines=3;numMasks=2;qSize=5;extra_enemies=4;break;}
		case 2:{numFruits=6;numVaccines=2;numMasks=2;qSize=5;extra_enemies=8;break;}
		case 3:{numFruits=5;numVaccines=2;numMasks=2;qSize=6;extra_enemies=12;break;}
		case 4:{numFruits=4;numVaccines=1;numMasks=2;qSize=6;extra_enemies=16;break;}
		case 5:{numFruits=3;numVaccines=1;numMasks=2;qSize=7;extra_enemies=20;break;}
	}
}

//For setting a quarantine region in the maze
void Maze::setQuarantine(){
	int x = qSize + rand()%(m_width-2*qSize);
	int y = qSize + rand()%(m_height-2*qSize);
	for(int i=0;i<qSize;i++){
		for(int j=0;j<qSize;j++){
			int k = mazeData[x+i][y+j];
			if(k==0){
				mazeData[x+i][y+j]=7;
			}
		}
	}
}
