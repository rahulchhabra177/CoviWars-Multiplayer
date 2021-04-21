#include "game.hpp";

class Map{
public:
	int mat[40][30];
	void LoadMap(SDL_Renderer*renderer);
	void RenderMap(SDL_Renderer *renderer);
	SDL_Texture* text;
	SDL_Rect rectange;





};