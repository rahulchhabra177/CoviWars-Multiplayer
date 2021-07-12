#include "Texture.h";
using namespace std;
bool texture_debug=false;

SDL_Texture* Texture::LoadT(char * path,SDL_Renderer* renderer){
if (texture_debug)cout<<"Texture.cpp::LoadT"<<path<<"\n";
	SDL_Surface* tmp;
	tmp=IMG_Load(path);
	SDL_Texture* returng=NULL;
	if (tmp==NULL){
		cout<<"Error:Couldn't initialize image\n";
		cout<<SDL_GetError();
		exit(1);
	}
	else{	
		returng=SDL_CreateTextureFromSurface(renderer,tmp);
		if (returng==NULL){
			cout<<"Error:"<<SDL_GetError()<<"\n";
			exit(1);
		}
		SDL_FreeSurface(tmp);
	}
	return returng;
}

SDL_Texture* Texture::LoadText(char* label,SDL_Renderer* renderer){

	if (texture_debug)cout<<"Texture.cpp::LoadText\n";
	TTF_Init();
	TTF_Font * font=nullptr;
	font=TTF_OpenFont("./../fonts/batmfa.ttf",20);
	if (font==NULL){
		cout<<"Error:Couldn't initialize font\n";
		exit(1);
	}
	
	SDL_Color color={255,255,25,255};
	SDL_Texture* text;
	SDL_Surface *textSurface=TTF_RenderText_Solid(font,label,color);

	if (textSurface==NULL){
		cout<<"Error:Couldn't initialize text surface for:"<<label<<"\n";	
		exit(1);
	}else{
		text=SDL_CreateTextureFromSurface(renderer,textSurface);
		if (text==NULL){
			cout<<"Error:Couldn't initialize text Texture for:"<<label<<":::"<<SDL_GetError()<<"\n";	
			exit(1);
		}else{
			SDL_FreeSurface(textSurface);
		}
	}
	return text;
}


