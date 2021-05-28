#ifndef SBOARD_H

#define SBOARD_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "character.h"
#include "Texture.h"

class ScoreBoard{

	public:
	
		vector<Character*> players;
		SDL_Renderer* renderer;
		int time_sec_u=0;
		int time_sec_t=0;
		int time_min_u=0;
		int time_min_t=0;
		int counter=0;
		char* time_strings = "00:00";
		ScoreBoard(vector<Character*> characters,SDL_Renderer* localRenderer);
		SDL_Texture* heading;
		SDL_Texture* timing;
		vector<SDL_Texture*> player_score;
		SDL_Rect head_rect,time_rect,score_rect;
		void render();
		void update();

};

#endif
