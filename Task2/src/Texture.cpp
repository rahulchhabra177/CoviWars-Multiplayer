#include "Texture.h";
using namespace std;


SDL_Texture* Texture::LoadT(char * path,SDL_Renderer* renderer){

	SDL_Surface* tmp;
	tmp=IMG_Load(path);
	SDL_Texture* returng=NULL;
	if (tmp==NULL){
		cout<<"Error:Couldn't initialize image\n";
	}
	else{	
		returng=SDL_CreateTextureFromSurface(renderer,tmp);
		SDL_FreeSurface(tmp);
	}
	return returng;

}

/*SDL_Texture* Texture::LoadText(char* label,SDL_Renderer* renderer){
	TTF_Init();
	TTF_Font* font;
	font = TTF_OpenFont("./../fonts/batmfa.ttf",20);
	SDL_Color color={255,255,255,255};
	SDL_Texture* text;
	SDL_Surface* textSurface=TTF_RenderText_Solid(font,label,color);
	if(textSurface==NULL){
		cout<<"Error: Couldn't initialise button: "<<label<<"\n";
		exit(1);
	}else{
		text = SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_FreeSurface(textSurface);
	}
	return text;
}*/
