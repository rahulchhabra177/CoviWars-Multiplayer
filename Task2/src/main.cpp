#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#include "game.hpp";
#include "Texture.h";
using namespace std;

//Game *game=nullptr;

int main(int argc,char* args[]){
	Game *game=new Game("Pacman",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,3840,2160);
	cout<<"run:"<<(int)(game->isRunning())<<"\n";
	while (game->isRunning()){
		game->handle_event();
		game->process();
		game->render();
	}
	game->close();
	return 0;
}
