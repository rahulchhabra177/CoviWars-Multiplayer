#ifndef SCORE_H

#define SCORE_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "./../character/coviwars.h"
#include "./../button/button.h"

class ScoreBoard{

public:
	SDL_Renderer* renderer;
	int time_sec_u=0;
	int time_sec_t=0;
	int time_min_u=0;
	int time_min_t=0;
	int counter=0;
	bool multiplayer=false;
	char * time_string="00:00";
	ScoreBoard(SDL_Renderer* render,bool multi);
	Button* heading,*timing,*pl1=nullptr,*pl2=nullptr;
	void render();
	void update(int player,string p1,int s1,string p2,int s2);
};
#endif