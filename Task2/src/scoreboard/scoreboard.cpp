#include "scoreboard.h"
bool score_debug=false;
using namespace std;

//Constructor
ScoreBoard::ScoreBoard(SDL_Renderer* render,bool multi){
	if (score_debug)cout<<"scoreboard.cpp::Score\n";
	renderer=render;
	multiplayer = multi;
	heading=new Button("ScoreBoard",renderer,"",255,255,25);
	heading->changeLabel("ScoreBoard","",255,255,25);
	timing=new Button(time_string,renderer,"",255,255,25);
	pl1=new Button("Player1:  0",renderer,"",255,255,25);
	pl2=new Button("Player2:  0",renderer,"",255,255,25);

	//Dimensions and coordinates for Textures
	heading->set_cor(2737,66,980,300);
	timing->set_cor(2887,396,370,150);
	pl1->set_cor(2887,596,378,150);
	pl2->set_cor(2887,796,378,150);
	
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
			if (counter%10==0){
				//Player1
				string player1=p1+" : "+to_string(s1);
				pl1->changeLabel(player1,"",255,255,25);
				//Player2
				string player2=p2+" : "+to_string(s2);
				pl2->changeLabel(player2,"",255,255,25);
			}
			if (counter==60){
				counter=0;

				//Timer
				time_sec_u++;
				if (time_sec_u==10){time_sec_t++;time_sec_u=0;}
				if (time_sec_t==6){time_sec_t=0;time_min_u++;}
				if (time_min_u==10){time_min_u=0;time_min_t++;}
				if (time_min_t==6){time_min_t=0;}	
				string temp_s="Time:"+to_string(time_min_t)+to_string(time_min_u)+":"+to_string(time_sec_t)+to_string(time_sec_u);
				timing->changeLabel(temp_s,"",255,255,25);
				
			}
		}

	//Normal updation for single player mode
	}else{
		//The counter here is used to synchronise the game with real world 
		//time by converting no of frames to seconds, and because the game
		//runs at 60 FPS, 60 frames make one second
		counter++;
		if (counter%20==0){
				//Player1
				string player1=p1+" : "+to_string(s1);
				pl1->changeLabel(player1,"",255,255,25);
			}
		if (counter==60){
			counter=0;

			//Timer
			time_sec_u++;
			if (time_sec_u==10){time_sec_t++;time_sec_u=0;}
			if (time_sec_t==6){time_sec_t=0;time_min_u++;}
			if (time_min_u==10){time_min_u=0;time_min_t++;}
			if (time_min_t==6){time_min_t=0;}	
			string temp_s="Time : "+to_string(time_min_t)+to_string(time_min_u)+":"+to_string(time_sec_t)+to_string(time_sec_u);
			timing->changeLabel(temp_s,"",255,255,25);
			
		}
	}
}

//Local renderer for score board
void ScoreBoard::render(){
	if (score_debug)cout<<"scoreboard.cpp::render\n";
	heading->render(renderer);
	timing->render(renderer);
//Multiplayer score board
	if (multiplayer){
		int a=strlen(pl1->label);
		int b=strlen(pl2->label);

		pl1->set_cor(2887,596,min(900,a*50),150);
		pl1->render(renderer);

		pl2->set_cor(2887,796,min(900,b*50),150);
		pl2->render(renderer);
	}
	//Single Player Score Board
	else{
		int a=strlen(pl1->label);
		pl1->set_cor(2887,596,min(900,a*50),150);
		pl1->render(renderer);
	}
}
