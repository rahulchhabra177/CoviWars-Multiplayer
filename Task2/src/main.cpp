#include "game.hpp";
#include "SDL2/SDL_net.h"
using namespace std;


struct data{

	int unique_id;
	TCPsocket socket;
	int timeout;

};


int main(int argc,char* args[]){
	int sw,sh;
	cout<<"Enter your resolution: ";
	cin>>sw>>sh;
		SDL_Init(SDL_INIT_EVERYTHING);
		// SDLNet_Init();
		int player_id=0;
		// IPaddress ip;
		// TCPsocket server,client;
		// char temp[30];
		// bool connected=false;
		// SDLNet_SocketSet sockets;
		// sockets=SDLNet_AllocSocketSet(1);
		// SDL_Event event;
		
		// 		const char* text="Hi Welcome to the Game\n";
		// 		const char* text2="Thank You for letting me in\n";

		// if (stoi(args[2])==1){
		// 	SDLNet_ResolveHost(&ip,NULL,stoi(args[1]));
		// 	server = SDLNet_TCP_Open(&ip);
		// }
		// else{
		// 	SDLNet_ResolveHost(&ip,"127.0.0.1",stoi(args[1]));
		// 	server=SDLNet_TCP_Open(&ip);
		// 	SDLNet_TCP_Send(server,text2,strlen(text2));
		// 	connected=true;
		// 	SDLNet_TCP_AddSocket(sockets,server);
		// }
		
		// SDL_Event event;
		bool isServer=false;
		if (stoi(args[1])==1){isServer=true;}
	Game *game=new Game("COROMAN",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,sw,sh,isServer);
		// bool tempr=false;
		// TCPsocket temp_soc;
	while (game->isRunning()){
		// cout<<4;
	
	game->handle_event();




	// if (stoi(args[2])==1 and !connected){
	// 		temp_soc=SDLNet_TCP_Accept(server);
	// 		if (temp_soc){
	// 			connected=true;
	// 			client=temp_soc;
	// 			SDLNet_TCP_AddSocket(sockets,client);
	// 			if (player_id<1){
					
	// 				SDLNet_TCP_Send(client,text,strlen(text));

	// 				player_id++;
	// 				cout<<"New player joined:"<<player_id<<"\n";
	// 			}
	// 		else{ 
	// 				cout<<"Entry denied:More players tried to connect\n";
	// 				const char* msg="Sorry Housefull\n";
	// 				SDLNet_TCP_Send(client,msg,strlen(msg));
	// 			}	
	// 		}
 //    }


// if (stoi(args[2])==1 and connected){

// if (!tempr){
// 		tempr=true;
// 		const char* msg="This is test message from server to client\n";
// 		SDLNet_TCP_Send(client,msg,strlen(msg));
// 	}
// // cout<<SDLNet_CheckSockets(sockets,0)<<":::::"<<SDLNet_SocketReady(client)<<"::tree\n";
// if (SDLNet_CheckSockets(sockets,0)>0 && SDLNet_SocketReady(client)){
// int x=SDLNet_TCP_Recv(client,temp,strlen(temp));
// 						if (x!=0){
// 						cout<<"PAcket Recieved:"<<temp<<" "<<x<<"\n";
// 						}
						

// }
						

// 						if (temp[0]=='0'){
// 								cout<<"New player joined:"<<temp[1]-'0'<<"\n";


						// }

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
				// }
			// }

		// }
// else if (connected){
// 	if (!tempr){
// 		tempr=true;
// 		const char* msg="This is test message from client to server\n";
// 		SDLNet_TCP_Send(server,msg,strlen(msg));
// 	}



// if (SDLNet_CheckSockets(sockets,0)>0 && SDLNet_SocketReady(server)){
// int x=SDLNet_TCP_Recv(server,temp,strlen(temp));
// 						if (x!=0){
// 						cout<<"PAcket Recieved:"<<temp<<" "<<x<<"\n";
// 						}
						
	
// }

// }
// cout<<"Working\n";
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

// cout<<5;
		game->process();
		// cout<<6;
		game->render();
		// cout<<7;





		}
	

game->close();
// if (tempr){cout<<"successful\n";}
// else{cout<<"Failed\n";}

// // for (int i=0;i<socket_vector.size();i++){
// 	SDLNet_TCP_Close(socket_vector[i].socket);
// // }
// SDLNet_FreeSocketSet(sockets);

// 	SDLNet_TCP_Close(server);
// 	SDLNet_Quit();
	SDL_Quit(); 
	return 0;
}
