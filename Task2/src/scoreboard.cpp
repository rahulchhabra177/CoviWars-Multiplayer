#include "scoreboard.h"


ScoreBoard::ScoreBoard(vector<Character*>player,SDL_Renderer* render){
	players=player;
	renderer=render;
	heading=Texture::LoadText("ScoreBoard",renderer);
	timing=Texture::LoadText(time_string,renderer);
	// head_rect=new SDL_Rect();
	// time_rect=new SDL_Rect();
	head_rect.x=1131;
	head_rect.y=22;
	head_rect.h=100;
	head_rect.w=230;
	time_rect.x=1131;
	time_rect.y=132;
	time_rect.h=50;
	time_rect.w=120;
	score_rect.x=1131;
	score_rect.h=50;
	score_rect.w=100;
	for (int i=0;i<players.size();i++){
		player_score.push_back(Texture::LoadText(players[i]->name,renderer));
		}


}

void ScoreBoard::update(){
			// cout<<time_min_t<<time_min_u<<":"<<time_sec_t<<time_sec_u<<"\n";

	counter++;
	if (counter==100){
		counter=0;
		time_sec_u++;
		if (time_sec_u==10){time_sec_t++;time_sec_u=0;}

		if (time_sec_t==6){time_sec_t=0;time_min_u++;}
		if (time_min_u==10){time_min_u=0;
			time_min_t++;}
		if (time_min_t==6){time_min_t=0;}	

		string temp_s="";
		temp_s.push_back((char)(time_min_t+'0'));
		temp_s.push_back((char)(time_min_u+'0'));
		temp_s.push_back(':');
		temp_s.push_back((char)(time_sec_t+'0'));
		temp_s.push_back((char)(time_sec_u+'0'));
		time_string=&temp_s[0];				


		timing=Texture::LoadText(time_string,renderer);

	for (int i=0;i<players.size();i++){
		player_score[i]=Texture::LoadText(players[i]->name,renderer);
		}

		}

}
void ScoreBoard::render(){
		SDL_RenderCopy(renderer,heading,NULL,&head_rect);
		SDL_RenderCopy(renderer,timing,NULL,&time_rect);
		for (int i=0;i<player_score.size();i++){
			score_rect.y=200+60*i;
		SDL_RenderCopy(renderer,player_score[i],NULL,&score_rect);

		}

}

