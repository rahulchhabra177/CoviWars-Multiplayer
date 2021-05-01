#ifndef TEXTURE_H

#define TEXTURE_H
#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Texture{

	public:
		static SDL_Texture* LoadT(char * path,SDL_Renderer* renderer);

};
#endif
