#include "game.hpp";
#include "Texture.h";
using namespace std;

int main(int argc,char* args[]){
	int sw,sh;
	cout<<"Enter your resolution: ";
	cin>>sw>>sh;
	Game *game=new Game("COROMAN",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,sw,sh);
	while (game->isRunning()){
		game->handle_event();
		game->process();
		game->render();
	}
	game->close();
	return 0;
}
