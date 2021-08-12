#include "sounds.h";

using namespace std;
bool sound_debug=false;

//Sound vector stores all the sound effects which are heard when certain actions
//take place in the game, like collisions, button presses, state changes, etc.

//While the music vector stores the background music

//Constructor of sound manager 
SoundClass::SoundClass(){
	if (sound_debug)cout<<"sounds.cpp:SoundClass\n";

	int res=Mix_OpenAudio(22050,AUDIO_S16SYS,2,4069);
	//Here First parameter is audio rate ,Second paramerter is audio_format ,Third parameter is number of audio channels,last parameter is for audio buffer
	
	if (res!=0){
		cout<<"Couldn't initialize audio:"<<Mix_GetError()<<"\n";
		exit(1);
	}	
}

//For loading sound from an external path, and labelling the sound with the
//given name for subsequent uses
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

//For loading music from an external path, with desired label
void SoundClass::LoadMusic(char* path,string label){
	if (sound_debug)cout<<"sounds.cpp:LoadSound\n";
	Mix_Music * musicchunk=Mix_LoadMUS(path);
	if (musicchunk==nullptr){
		cout<<"Couldn't initialize sound at :"<<path<<"::"<<Mix_GetError()<<"\n";
		exit(1);
	}
	LabelToInt1[label]=size_it1;
	MusicVector.push_back(musicchunk);
	size_it1++;
}

void SoundClass::InitializeAll(){
	if (sound_debug)cout<<"sounds.cpp:InitializeAll\n";
	LoadSound("./../sounds/start.wav","start");
	LoadSound("./../sounds/pauseState.wav","pause");
	LoadSound("./../sounds/collision.wav","collision");
	LoadSound("./../sounds/windowstart.wav","gamestart");
	LoadSound("./../sounds/button.wav","button");
	LoadSound("./../sounds/pacman_eatghost.wav","eatCorona");
	LoadSound("./../sounds/pacman_eatfruit.wav","eatFruit");
	LoadSound("./../sounds/pacman_extrapac.wav","eatVaccine");
	LoadSound("./../sounds/pacman_chomp.wav","wallAdded");
	LoadSound("./../sounds/explode.wav","explode");
	LoadMusic("./../music/bMusic.mp3","bMusic");
}

//For playing the stored sounds on demand
void SoundClass::PlaySound(string label){
	if (sound_on){
		if (sound_debug)cout<<"sounds.cpp:PlaySound\n";
		Mix_HaltChannel(-1);
		int loc=LabelToInt[label];
		Mix_PlayChannel(-1,SoundVector.at(loc),0);
	}
}

//For playing the background music
void SoundClass::PlayMusic(string label){
	if (music_on){
		if (sound_debug)cout<<"sounds.cpp:PlaySound\n";
		int loc=LabelToInt1[label];
		Mix_PlayMusic(MusicVector.at(loc),-1);
	}
}

//For controlling the pause/play of music from other states of the game
void SoundClass::changeMusicState(bool state){
	if (!state){Mix_PauseMusic();}
	else{Mix_ResumeMusic();}
	music_on=state;
}

//For controlling sounds from other states of the game 
void SoundClass::changeSoundState(bool state){
	if (!state){Mix_HaltChannel(-1);}
	sound_on=state;
}