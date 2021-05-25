#include "game.hpp";
#include "Texture.h";
using namespace std;

int main(int argc,char* args[]){
	Game *game=new Game("COROMAN",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
	while (game->isRunning()){
		game->handle_event();
		game->process();
		game->render();
	}
	game->close();
	return 0;
}
