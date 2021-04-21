#include "game.hpp";
class Button{
	
	public:
		char* label;
		int xpos,ypos,height,width;
		SDL_Rect src,dest;
		SDL_Texture * LoadButtonFromImage(char * path,SDL_Renderer* renderer,char* label_1,int x,int y,int a,int b);
		void handle_event(SDL_Event e,int*state);
		bool isinside(int a,int b);
		void render(SDL_Renderer *renderer,SDL_Texture* tect);
		void set_cor(int x,int y,int a ,int b);






};