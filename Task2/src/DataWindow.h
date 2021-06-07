#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>


class DataWindow{

	public:
		string resolution="";
		bool multiplayer=false;
		bool server=false;
		// bool isFullScreen=false;

		DataWindow();
		void update();
		void render();
		void handle_event();
		void close();
		SDL_Window* window;
		SDL_Renderer* renderer;
		bool running=true;


}