#include "Texture.h";
#include "pacman.h";
using namespace std;
int temp=0;

pacman::pacman(char * path,SDL_Renderer* rendere,int init_x,int init_y,bool isenem){
	character=Texture::LoadT(path,rendere);
	renderer=rendere;
	x=init_x;
	y=init_y;
	isenemy=isenem;
}


void pacman::update(){
	temp=(temp+1)%10;
	dstr.h=height;
	dstr.w=width;
	dstr.x=x;
	dstr.y=y;
}


void pacman::render(){
	SDL_RenderCopy(renderer,character,NULL,&dstr);
}

