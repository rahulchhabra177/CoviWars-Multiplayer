#include "Map.h";

void Map::LoadMap(SDL_Renderer*renderer){

	tape=new Button();
	mat[2][5]=1;mat[15][14]=1;mat[22][10]=1;
	// text=tape->LoadButtonFromImage("./../assets/police.jpeg",renderer,"Play",-1,-1,-1,-1);
	// 			tape->set_cor(50,80,25,80);
	int arr[20][20]={{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


	for (int i=0;i<20;i++){
		for (int j=0;j<20;j++){
			mat[i][j]=arr[i][j];
		}}

	for (int i=0;i<20;i++){
		for (int j=0;j<20;j++){
			if (mat[i][j]==1){
				// std::cout<<i<<" "<<j<<"\n";
				text1=tape->LoadButtonFromImage("./../assets/police1.jpeg",renderer,"Play");
				tape->set_cor(20*i,20*j,15,80);

				
			}
			else if (mat[i][j]==2){
				// std::cout<<i<<" "<<j<<"\n";
				text2=tape->LoadButtonFromImage("./../assets/police2.jpeg",renderer,"Play");
				tape->set_cor(20*i,20*j,15,80);
				
			}

		}
	}

}


void Map::RenderMap(SDL_Renderer* renderer){
					// tape->render(renderer,text);

for (int i=0;i<20;i++){

		for (int j=0;j<20;j++){
			if (mat[i][j]==1){
				SDL_Rect rect;
				rect.x=i*40;
				rect.y=j*40;
				rect.h=6;
				rect.w=40;
				// std::cout<<rect.x<<" : "<<rect.y<<"\n";
				// std::cout<<i<<"--"<<j<<"\n";
				SDL_RenderCopy(renderer,text1,NULL,&rect);

				
			}
			else if (mat[i][j]==2){
				SDL_Rect rect;
				rect.x=i*40;
				rect.y=j*40;
				rect.h=40;
				rect.w=6;
				// std::cout<<rect.x<<" : "<<rect.y<<"\n";
				// std::cout<<i<<"--"<<j<<"\n";
				SDL_RenderCopy(renderer,text2,NULL,&rect);

				
			}
		}
		// break;
	}
}
