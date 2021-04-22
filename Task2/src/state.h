#ifndef STATE_H

#define STATE_H
#include "game.hpp"
#include "button.h"
#include "Texture.h"

class State{

	public:
		char* name;
		vector<Button*> buttons;
		SDL_Texture* background;
		void render(SDL_Renderer *renderer);
		int locatePointer(int a,int b);
		void handle_event(SDL_Event e,int* state);
		
};
#endif


