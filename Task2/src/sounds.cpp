#include "sounds.h";

using namespace std;
bool sound_debug=true;

SoundClass::SoundClass(){
	if (sound_debug)cout<<"sounds.cpp:SoundClass\n";

	int res=Mix_OpenAudio(22050,AUDIO_S16SYS,2,4069);
	//Here First parameter is audio rate ,Second paramerter is audio_format ,Third parameter is number of audio channels,last parameter is for audio buffer
	if (res!=0){
		cout<<"Couldn't initialize audio:"<<Mix_GetError()<<"\n";
		exit(1);
	}	
}


void SoundClass::LoadSound(char* path,string label){
	if (sound_debug)cout<<"sounds.cpp:LoadSound\n";
	Mix_Chunk * sound_chunk=Mix_LoadWAV(path);
	if (sound_chunk==nullptr){
		cout<<"Couldn't initialize sound at :"<<path<<"::"<<Mix_GetError()<<"\n";
		exit(1);
	}
	LabelToInt[label]=size_it;
	SoundVector.push_back(sound_chunk);
	size_it++;
}

void SoundClass::InitializeAll(){
	if (sound_debug)cout<<"sounds.cpp:InitializeAll\n";
	LoadSound("./../Sounds/start.wav","start");
	LoadSound("./../Sounds/pauseState.wav","pause");
	LoadSound("./../Sounds/collision.wav","collision");
	LoadSound("./../Sounds/windowstart.wav","gamestart");
	LoadSound("./../Sounds/button.wav","button");
}

void SoundClass::PlaySound(string label){
	if (music_on){
		if (sound_debug)cout<<"sounds.cpp:PlaySound\n";
		Mix_HaltChannel(-1);
		int loc=LabelToInt[label];
		Mix_PlayChannel(-1,SoundVector.at(loc),0);
	}
}

void SoundClass::changeMusicState(){
	music_on=!music_on;
}