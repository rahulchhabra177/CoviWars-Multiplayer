#ifndef SCORE_H

#define SCORE_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "character.h"
#include "Texture.h"

class ScoreBoard{

public:
	SDL_Renderer* renderer;
	int time_sec_u=0;
	int time_sec_t=0;
	int time_min_u=0;
	int time_min_t=0;
	int counter=0;
	char * time_string="00:00";
	ScoreBoard(SDL_Renderer* render);
	SDL_Texture* heading,*timing,*pl1,*pl2;
	SDL_Rect head_rect,time_rect,score_rect;
	void render();
	void update(int player,string p1,int s1,string p2,int s2);
};
#endif