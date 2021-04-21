#include "Texture.h";
#include "pacman.h";
#include "game.hpp";
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

	
	// cout<<x<<" "<<y<<"\n";
	// srcr.h=32;
	// srcr.w=32;
	temp=(temp+1)%10;
	dstr.h=height;
	dstr.w=width;
	// if (isenemy and temp%2==0){y+=temp/9;temp+=18;}
	// if (isenemy and temp%2==1){x+=temp/9;temp+=21;}
	dstr.x=x;
	dstr.y=y;

}


void pacman::render(){


SDL_RenderCopy(renderer,character,NULL,&dstr);

}

