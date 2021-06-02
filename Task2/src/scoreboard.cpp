#include "scoreboard.h"
bool score_debug=true;

ScoreBoard::ScoreBoard(SDL_Renderer* render/*,int swidth,int sheight*/){
	if (score_debug)cout<<"scoreboard.cpp::Score\n";
	// players=player;
	renderer=render;
	heading=Texture::LoadText("ScoreBoard",renderer);
	timing=Texture::LoadText(time_string,renderer);
	pl1=Texture::LoadText("Player1:0",renderer);
	// head_rect=new SDL_Rect();
	// time_rect=new SDL_Rect();
	head_rect.x=3487;
	head_rect.y=66;
	head_rect.h=300;
	head_rect.w=709;
	time_rect.x=3487;
	time_rect.y=396;
	time_rect.h=150;
	time_rect.w=370;
	score_rect.x=3487;
	score_rect.y=596;
	score_rect.h=150;
	score_rect.w=308;
	// for (int i=0;i<players.size();i++){
	// 	player_score.push_back(Texture::LoadText(players[i]->name,renderer));
	// 	}


}

void ScoreBoard::update(int player,string p1,int s1,string p2,int s2){
			// cout<<time_min_t<<time_min_u<<":"<<time_sec_t<<time_sec_u<<"\n";
	if (score_debug)cout<<"scoreboard.cpp::update\n";
	counter++;
	if (counter==100){
		counter=0;
		time_sec_u++;
		if (time_sec_u==10){time_sec_t++;time_sec_u=0;}

		if (time_sec_t==6){time_sec_t=0;time_min_u++;}
		if (time_min_u==10){time_min_u=0;
			time_min_t++;}
		if (time_min_t==6){time_min_t=0;}	

		string temp_s="Time:"+to_string(time_min_t)+to_string(time_min_u)+":"+to_string(time_sec_t)+to_string(time_sec_u);
		
		time_string=&temp_s[0];				
// cout<<time_string<<"\n";

		timing=Texture::LoadText(time_string,renderer);
		string player1=p1+":"+to_string(s1);
		char * sc=&player1[0];
		pl1=Texture::LoadText(sc,renderer);



		}

}
void ScoreBoard::render(){
	if (score_debug)cout<<"scoreboard.cpp::render\n";
		SDL_RenderCopy(renderer,heading,NULL,&head_rect);
		SDL_RenderCopy(renderer,timing,NULL,&time_rect);
		if (pl1!=nullptr ){
		SDL_RenderCopy(renderer,pl1,NULL,&score_rect);
		}
		else{
			cout<<"issue found\n";
		}
		// for (int i=0;i<player_score.size();i++){
		// 	score_rect.y=200+60*i;
		// SDL_RenderCopy(renderer,player_score[i],NULL,&score_rect);

		// }

}

