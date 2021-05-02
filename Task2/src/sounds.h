#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

class SoundClass{
public:
	SoundClass();
	void LoadSound(char * path,char* label);
	void InitializeAll();
	void PlaySound(char* label) ;	
private:
	vector<Mix_Chunk*>SoundVector;
	unordered_map<char*,int>LabelToInt;
};