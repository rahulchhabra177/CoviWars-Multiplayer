#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "game.hpp";
#include "Texture.h";
using namespace std;

Game *game=nullptr;

int main(int argc,char* args[]){
	game=new Game();
	game->init("Pacman",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600);
			cout<<"run:"<<(int)(game->isrunning())<<"\n";

	while (game->isrunning()){
		game->handle_event();
		game->process();
		game->render();
		cout<<"run:"<<(int)(game->isrunning())<<"\n";
	}
	game->close();




	return 0;
}