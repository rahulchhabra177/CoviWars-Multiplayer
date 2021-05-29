#include "game.hpp";
#include "SDL2/SDL_net.h"
using namespace std;


struct data{

	int unique_id;
	TCPsocket socket;
	int timeout;
	
};


int main(int argc,char* args[]){
		
		SDL_Init(SDL_INIT_EVERYTHING);
		bool accepting=true;
		SDLNet_Init();
		int player_id=0;
		IPaddress ip;
		TCPsocket server,client;
		cout<<args[1]<<args[2]<<"\n";
		vector<TCPsocket> socket_vector;
		char temp[3];
		SDLNet_SocketSet sockets;
		sockets=SDLNet_AllocSocketSet(4);
				const char* text="01\n";

		if (stoi(args[2])==1){
			SDLNet_ResolveHost(&ip,NULL,stoi(args[1]));
			
			server = SDLNet_TCP_Open(&ip);
		}
		else{
			cout<<1;
			SDLNet_ResolveHost(&ip,"127.0.0.1",stoi(args[1]));
			cout<<2;
			client=SDLNet_TCP_Open(&ip);
			SDLNet_TCP_Send(client,temp,strlen(temp)+1);
			cout<<3;
		}
		
		SDL_Event event;

	Game *game=new Game("COROMAN",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,player_id);
		bool tempr=false;
	while (game->isRunning()){
		// cout<<4;
	
		game->handle_event();
	if (stoi(args[2])==1){
			TCPsocket tempsocket=SDLNet_TCP_Accept(server);
			if (tempsocket){
				if (player_id<2){
					cout<<"player\n\n";
					cout<<1;
					SDLNet_TCP_AddSocket(sockets,tempsocket);
					cout<<2;
					SDLNet_TCP_Send(tempsocket,text,strlen(text)+1);
					cout<<3;

					// data player_data;
					// player_data.unique_id=player_id;
					// player_data.socket=tempsocket;
					// player_data.timeout=SDL_GetTicks();
				socket_vector.push_back(tempsocket);
				// cout<<4;
					player_id++;
					temp[0]='0';
					temp[1]=player_id+'0';
					cout<<"New player joined:"<<player_id<<"\n";
				}
			else{ 
					cout<<"Entry denied:More players tried to connect\n";
					// temp='3'+'\n';
					temp[0]='3';
					temp[1]='\n';
					SDLNet_TCP_Send(tempsocket,temp,strlen(temp)+1);
				}	
			}
    }


if (stoi(args[2])==1){
			// cout<<"ReadyScokets:"<<SDLNet_CheckSockets(sockets,0)<<"\n";
			while (SDLNet_CheckSockets(sockets,0)>0){
		cout<<"555555555555";
				for (int i=0;i<socket_vector.size();i++){
					cout<<i<<"pp\n";
					// TCPsocket ttt=socket_vector.at(i);
					// if (SDLNet_SocketReady(socket_vector[i])){
					// 	SDLNet_TCP_Recv(socket_vector[i],temp,3);
					// 	cout<<"PAcket Recieved:"<<temp<<"\n";
						
						

// 						if (temp[0]=='0'){
// 								cout<<"New player joined:"<<temp[1]-'0'<<"\n";


// 						}

// 						else if (temp[0]=='2'){
// 						for (int k=0;k<socket_vector.size();k++){
// 								if (k==i){continue;}
// 								SDLNet_TCP_Send(socket_vector[k],temp,strlen(temp)+1);
// 							}

// 							SDLNet_TCP_DelSocket(sockets,socket_vector[i]);
// 							socket_vector.erase(socket_vector.begin()+i);
// 							player_id--;	 	
// 						}	
// 						else{
// 							int playerid=temp[1]-'0';
// 							int dir=temp[2]-'0';
// 							cout<<"else statementn\n";
// 							// game->updateServer(playerid,dir);


// 						}
// 
					// }
				}
			}

		}
// else{

// 	if (SDLNet_SocketReady(client)){

// SDLNet_TCP_Recv(client,temp,3);
// 						cout<<"PAcket Recieved"<<strlen(temp)<<"\n";
// }
// }

// 		for (int k=0;k<socket_vector.size();k++){
// 			if (SDL_GetTicks()-socket_vector[k].timeout>5000){

// temp[0]='2';
// temp[1]=('0'+k);
// for (int k=0;k<socket_vector.size();k++){
// 								SDLNet_TCP_Send(socket_vector[k].socket,temp,strlen(temp)+1);
// 							}
// 						}

// 				SDLNet_TCP_DelSocket(sockets,socket_vector[k].socket);
// 							socket_vector.erase(socket_vector.begin()+k);
// 							player_id--;
// 			}


		game->process();
		game->render();





		}
	

game->close();
if (tempr){cout<<"successful\n";}
else{cout<<"Failed\n";}

// for (int i=0;i<socket_vector.size();i++){
// 	SDLNet_TCP_Close(socket_vector[i].socket);
// }
// SDLNet_FreeSocketSet(sockets);

// 	SDLNet_TCP_Close(server);
// 	SDLNet_Quit();
	SDL_Quit(); 
	return 0;
}
