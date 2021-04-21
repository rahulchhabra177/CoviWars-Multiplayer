#include "game.hpp";
#include "button.h";

class Map{
public:
	int mat[20][20];
	void LoadMap(SDL_Renderer*renderer);
	void RenderMap(SDL_Renderer *renderer);
	SDL_Texture* text1,*text2;
	Button* tape=nullptr;
	

};
