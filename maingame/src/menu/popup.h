#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
#include "./../button/button.h"
class Popup{
	public:
		int remaining_time=10;
		long long startTime;
		SDL_Texture* background,*congrats,*back;
		vector<Button*> buttons;
		Popup(SDL_Renderer * localRenderer,int type,bool isTimed,int width,int height);
		void render(SDL_Renderer* renderer);
		void update(int * state);
		bool timed;
		void handle_event(SDL_Event e,int* state,SoundClass* m,int* prevstate);
		int locatePointer(int a,int b);
		SDL_Renderer* renderer;
		SDL_Rect dst;
		int s_width,s_height;
};