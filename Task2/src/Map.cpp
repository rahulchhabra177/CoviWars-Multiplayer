#include "Map.h";
#include "button.h";


void Map::LoadMap(SDL_Renderer*renderer){

	Button* tape=new Button();
	mat[2][5]=1;
	for (int i=0;i<40;i++){
		for (int j=0;j<30;j++){
			if (mat[i][j]==1){
				text=tape->LoadButtonFromImage("./../assets/police.xcf",renderer,"Play",-1,-1,-1,-1);
				tape->set_cor(0,0,50,80);
				break;
			}
		}
	}

}


void Map::RenderMap(SDL_Renderer* renderer){
for (int i=0;i<40;i++){
		for (int j=0;j<30;i++){
			if (mat[i][j]==1){
				SDL_Rect rect;
				rect.x=10;
				rect.y=80;
				rect.h=60;
				rect.w=300;
				SDL_RenderCopy(renderer,text,NULL,&rect);
				break;
			}
		}
	}
}