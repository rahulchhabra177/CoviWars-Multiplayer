#include "game.hpp";
#include "SDL2/SDL_net.h"
using namespace std;

int main(int argc,char* args[]){

	//Enter resolution
	int sw,sh;
	cout<<"Enter your resolution: ";
	cin>>sw>>sh;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	//Setting custom FPS of the game to synchronise in-game timers and counters 
	//(which depend on number of frames) with real-world time
	const int FPS=60;
	const int frameDelay=1000/FPS;
	long long frameStart,frameTime;

	//To determine whether the game is single player or multiplayer anf if 
	//it is multiplayer, then whether is a server or a client.
	int player_id=0;
	bool isServer=false;
	if (stoi(args[1])==1){isServer=true;}
	string nm=(isServer?"CoviWars-server":"CoviWars-client");

	//Actual frame-by-frame processing of the game	
	Game *game=new Game(nm,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,sw,sh,isServer);
	while (game->isRunning()){
		frameStart=SDL_GetTicks();
		
		game->handle_event();
		game->process();
		game->render();
		
		frameTime=SDL_GetTicks()-frameStart;
		if (frameTime<frameDelay){
			SDL_Delay(frameDelay-frameTime);
		}
	}

	game->close();
	SDL_Quit(); 
	return 0;
}