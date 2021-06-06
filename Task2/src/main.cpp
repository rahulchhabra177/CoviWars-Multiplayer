#include "game.hpp";
#include "SDL2/SDL_net.h"
using namespace std;

struct data{

	int unique_id;
	TCPsocket socket;
	int timeout;

};

int main(int argc,char* args[]){
	int sw,sh;
	cout<<"Enter your resolution: ";
	cin>>sw>>sh;
	SDL_Init(SDL_INIT_EVERYTHING);
	const int FPS=60;
	const int frameDelay=1000/FPS;
	long long frameStart,frameTime;

	int player_id=0;
	bool isServer=false;
	if (stoi(args[1])==1){isServer=true;}
	Game *game=new Game("COROMAN",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,sw,sh,isServer);
	while (game->isRunning()){
		frameStart=SDL_GetTicks();
		game->handle_event();
		game->process();
		game->render();
		frameTime=SDL_GetTicks()-frameStart;
		if (frameTime<frameDelay){
			cout<<"Delaying...\n";
			SDL_Delay(frameDelay-frameTime);
		}
	}
	game->close();
	SDL_Quit(); 
	return 0;
}
