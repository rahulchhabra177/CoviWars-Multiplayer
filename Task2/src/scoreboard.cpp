#include "scoreboard.h"
using namespace std;

ScoreBoard::ScoreBoard(vector<Character*> characters,SDL_Renderer* localRenderer){
	players = characters;
	renderer = localRenderer;
	heading = Texture::LoadText("Scoreboard",renderer);
	timing = Texture::LoadText(time_strings,renderer);
	
	head_rect.x=3487;
	head_rect.y=66;
	head_rect.h=300;
	head_rect.w=709;
	time_rect.x=3487;
	time_rect.y=396;
	time_rect.h=150;
	time_rect.w=370;
	score_rect.x=3487;
	score_rect.h=150;
	score_rect.w=308;
	
	for(int i=0;i<players.size();i++){
		player_score.push_back(Texture::LoadText(players[i]->name,renderer));
	}
} 

void ScoreBoard::update(){
	counter++;
	if(counter==100){
		counter = 0;
		time_sec_u++;
		if(time_sec_u==10){
			time_sec_t++;
			time_sec_u=0;
		}
		if(time_sec_t==6){
			time_min_u++;
			time_sec_t=1;
		}
		if(time_min_u==10){
			time_min_t++;
			time_min_u=0;
		}
		if(time_min_t==6){
			time_min_t=0;
		}
		
		string temp_s = "";
		temp_s.push_back((char)(time_min_t+'0'));
		temp_s.push_back((char)(time_min_u+'0'));
		temp_s.push_back(':');
		temp_s.push_back((char)(time_sec_t+'0'));
		temp_s.push_back((char)(time_sec_u+'0'));
		time_strings=&temp_s[0];
		
		timing = Texture::LoadText(time_strings,renderer);
		
		for(int i=0;i<players.size();i++){
			player_score[i] = Texture::LoadText(players[i]->name,renderer);
		}
		
	}
}

void ScoreBoard::render(){
	SDL_RenderCopy(renderer,heading,NULL,&head_rect);
	SDL_RenderCopy(renderer,timing,NULL,&time_rect);
	for(int i=0;i<player_score.size();i++){
		score_rect.y = 600 + 180*i;
		SDL_RenderCopy(renderer,player_score[i],NULL,&score_rect);
	}
}
