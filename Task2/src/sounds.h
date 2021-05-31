#ifndef SOUNDS_H

#define SOUNDS_H
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "network.h";

using namespace std;

class SoundClass{
public:
	SoundClass();
	void LoadSound(char * path,string label);
	void InitializeAll();
	void PlaySound(string label);
	void changeMusicState();
	int size_it = 0;	
	bool music_on=true;
private:
	vector<Mix_Chunk*>SoundVector;
	unordered_map<string,int>LabelToInt;
};
#endif