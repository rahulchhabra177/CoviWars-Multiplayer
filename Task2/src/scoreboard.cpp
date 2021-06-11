#include "scoreboard.h"
bool score_debug=true;

//Constructor
ScoreBoard::ScoreBoard(SDL_Renderer* render,bool multi){
	if (score_debug)cout<<"scoreboard.cpp::Score\n";
	renderer=render;
	multiplayer = multi;

	//Texture for heading
	heading=Texture::LoadText("ScoreBoard",renderer);

	//Texture for in-game timer
	timing=Texture::LoadText(time_string,renderer);
	
	//Texture for player 1
	pl1=Texture::LoadText("Player1: 0",renderer);
	
	//Dimensions of different cells
	head_rect.x=2887;
	head_rect.y=66;
	head_rect.h=300;
	head_rect.w=709;
	time_rect.x=2887;
	time_rect.y=396;
	time_rect.h=150;
	time_rect.w=370;
	score_rect.x=2887;
	score_rect.y=596;
	score_rect.h=150;
	score_rect.w=378;
}

//Update function which managers the updation of the score of all the players
//as well as the in-game timer
void ScoreBoard::update(int player,string p1,int s1,string p2,int s2){
	if (score_debug)cout<<"scoreboard.cpp::update\n";

	if(multiplayer){

		//In case of multiplayer, the scoreboard will only start updating
		//once all the players have joined, and until then it waits
		if(p2!=""){
			counter++;
			if (counter==60){
				counter=0;

				//Timer
				time_sec_u++;
				if (time_sec_u==10){time_sec_t++;time_sec_u=0;}
				if (time_sec_t==6){time_sec_t=0;time_min_u++;}
				if (time_min_u==10){time_min_u=0;time_min_t++;}
				if (time_min_t==6){time_min_t=0;}	
				string temp_s="Time:"+to_string(time_min_t)+to_string(time_min_u)+":"+to_string(time_sec_t)+to_string(time_sec_u);
				time_string=&temp_s[0];				
				timing=Texture::LoadText(time_string,renderer);
				
				//Player1
				string player1=p1+":"+to_string(s1);
				char * sc=&player1[0];
				pl1=Texture::LoadText(sc,renderer);

				//Player2
				string player2=p2+":"+to_string(s2);
				char * sc2=&player2[0];
				pl2=Texture::LoadText(sc2,renderer);
			}
		}

	//Normal updation for single player mode
	}else{
		//The counter here is used to synchronise the game with real world 
		//time by converting no of frames to seconds, and because the game
		//runs at 60 FPS, 60 frames make one second
		counter++;
		if (counter==60){
			counter=0;

			//Timer
			time_sec_u++;
			if (time_sec_u==10){time_sec_t++;time_sec_u=0;}
			if (time_sec_t==6){time_sec_t=0;time_min_u++;}
			if (time_min_u==10){time_min_u=0;time_min_t++;}
			if (time_min_t==6){time_min_t=0;}	
			string temp_s="Time:"+to_string(time_min_t)+to_string(time_min_u)+":"+to_string(time_sec_t)+to_string(time_sec_u);
			time_string=&temp_s[0];				
			timing=Texture::LoadText(time_string,renderer);
			
			//Player 1
			string player1=p1+":"+to_string(s1);
			char * sc=&player1[0];
			pl1=Texture::LoadText(sc,renderer);
		}
	}
}

//Local renderer for score board
void ScoreBoard::render(){
	if (score_debug)cout<<"scoreboard.cpp::render\n";
	SDL_RenderCopy(renderer,heading,NULL,&head_rect);
	SDL_RenderCopy(renderer,timing,NULL,&time_rect);
	
	//Player 1 scoreboard
	if (pl1!=nullptr ){
		SDL_RenderCopy(renderer,pl1,NULL,&score_rect);
	}

	//Player 2 scoreboard in case of multiplayer
	if (pl2!=nullptr ){
		score_rect.y+=200;
		SDL_RenderCopy(renderer,pl2,NULL,&score_rect);
		score_rect.y-=200;
	}
}
