#include "state.h"
using namespace std;

class men : public State{
	
	public:
		
		men(char* title, int menuType, SDL_Texture* poster){
			name = title;
			background = poster;
			
		}
		
		int locatePointer(int a,int b){
			for(int i=0;i<buttons.size();i++){
				if(buttons[i]->isInside(a,b)){
					return i;
				}
			}
			return -1;
		}
	
};







