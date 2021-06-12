#ifndef SOUNDS_H

#define SOUNDS_H
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "./../network/network.h";

using namespace std;

class SoundClass{
public:
	SoundClass();
	void LoadSound(char * path,string label);
	void LoadMusic(char * path,string label);
	void InitializeAll();
	void PlaySound(string label);
	void PlayMusic(string label);
	void changeMusicState(bool state);
	void changeSoundState(bool state);
	int size_it = 0,size_it1=0;	
	bool music_on=true,sound_on=true;
private:
	vector<Mix_Chunk*>SoundVector;
	vector<Mix_Music*>MusicVector;
	unordered_map<string,int>LabelToInt;
	unordered_map<string,int>LabelToInt1;
};
#endif