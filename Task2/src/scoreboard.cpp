#include "scoreboard.h"
bool score_debug=true;

ScoreBoard::ScoreBoard(SDL_Renderer* render,bool multi){
	if (score_debug)cout<<"scoreboard.cpp::Score\n";
	renderer=render;
	multiplayer = multi;
	heading=Texture::LoadText("ScoreBoard",renderer);
	timing=Texture::LoadText(time_string,renderer);
	pl1=Texture::LoadText("Player1: 0",renderer);
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

void ScoreBoard::update(int player,string p1,int s1,string p2,int s2){
	if (score_debug)cout<<"scoreboard.cpp::update\n";
	if(multiplayer){
		if(p2!=""){
			counter++;
			if (counter==100){
				counter=0;
				time_sec_u++;
				if (time_sec_u==10){time_sec_t++;time_sec_u=0;}
				if (time_sec_t==6){time_sec_t=0;time_min_u++;}
				if (time_min_u==10){time_min_u=0;time_min_t++;}
				if (time_min_t==6){time_min_t=0;}	
				string temp_s="Time:"+to_string(time_min_t)+to_string(time_min_u)+":"+to_string(time_sec_t)+to_string(time_sec_u);
				time_string=&temp_s[0];				
				timing=Texture::LoadText(time_string,renderer);
				string player1=p1+":"+to_string(s1);
				char * sc=&player1[0];
				pl1=Texture::LoadText(sc,renderer);
				string player2=p2+":"+to_string(s2);
				char * sc2=&player2[0];
				pl2=Texture::LoadText(sc2,renderer);
			}
		}
	}else{
		counter++;
		if (counter==100){
			counter=0;
			time_sec_u++;
			if (time_sec_u==10){time_sec_t++;time_sec_u=0;}
			if (time_sec_t==6){time_sec_t=0;time_min_u++;}
			if (time_min_u==10){time_min_u=0;time_min_t++;}
			if (time_min_t==6){time_min_t=0;}	
			string temp_s="Time:"+to_string(time_min_t)+to_string(time_min_u)+":"+to_string(time_sec_t)+to_string(time_sec_u);
			time_string=&temp_s[0];				
			timing=Texture::LoadText(time_string,renderer);
			string player1=p1+":"+to_string(s1);
			char * sc=&player1[0];
			pl1=Texture::LoadText(sc,renderer);
		}
	}
}

void ScoreBoard::render(){
	if (score_debug)cout<<"scoreboard.cpp::render\n";
	SDL_RenderCopy(renderer,heading,NULL,&head_rect);
	SDL_RenderCopy(renderer,timing,NULL,&time_rect);
	if (pl1!=nullptr ){
		SDL_RenderCopy(renderer,pl1,NULL,&score_rect);
	}
	if (pl2!=nullptr ){
		score_rect.y+=200;
		SDL_RenderCopy(renderer,pl2,NULL,&score_rect);
		score_rect.y-=200;
	}
}
