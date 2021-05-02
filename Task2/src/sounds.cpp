#include "sounds.h";

using namespace std;
SoundClass::SoundClass(){

	int res=Mix_OpenAudio(22050,AUDIO_S16SYS,2,4069);
	//Here First parameter is audio rate ,Second paramerter is audio_format ,Third PArameter is number of audio channels,last parameter is for audio buffer
	if (res!=0){
		cout<<"Couldn't initialize audio:"<<Mix_GetError()<<"\n";
		exit(-1);
	}	
}


void SoundClass::LoadSound(char* path,char* label){

	Mix_Chunk * sound_chunk=Mix_LoadWAV(path);
	if (sound_chunk==nullptr){
		cout<<"Couldn't initialize sound at :"<<path<<"::"<<Mix_GetError()<<"\n";
		exit(-1);
	}
	cout<<"work1\n";
	LabelToInt[label]=SoundVector.size();
	cout<<LabelToInt.size();
	for (auto u:LabelToInt){
		cout<<u.first<<":"<<u.second<<"\n";
	}
	cout<<"Done\n";
	SoundVector.push_back(sound_chunk);



}

// void SoundClass::LoadMusic(char* path,char* label){

// 	Mix_Music * Music_chunk=Mix_LoadMUS(path);
// 	if (Music_chunk==nullptr){
// 		cout<<"Couldn't initialize sound at :"<<path<<"::"<<Mix_GetError()<<"\n";
// 		exit(-1);
// 	}
// 	cout<<"work1\n";
// 	LabelToInt[label]=MusicVector.size();
// 	cout<<LabelToInt.size();
// 	for (auto u:LabelToInt){
// 		cout<<u.first<<":"<<u.second<<"\n";
// 	}
// 	cout<<"Done\n";
// 	MusicVector.push_back(Music_chunk);



// }



void SoundClass::InitializeAll(){
	LoadSound("./../Sounds/pacman_beginning.wav","Entry");
}

void SoundClass::PlaySound(char* label){
	cout<<LabelToInt.size();
	for (auto u:LabelToInt){
		cout<<u.first<<":"<<u.second<<"\n";
	}
	cout<<"Done\n";
	// if (LabelToInt.find(label)==LabelToInt.end()){
		// cout<<"Couldn't find sound with specified label:"<<label<<"\n";
		// exit(-1);
	// }
	int loc=LabelToInt[label];
	Mix_PlayChannel(-1,SoundVector[loc],0);




}
