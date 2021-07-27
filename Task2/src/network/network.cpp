#include "network.h"
using namespace std;

//Constructor for network manager
network::network(bool isserver,char* ip_addr,int portNo){
	
	SDLNet_Init();
	IPaddress ip;	
	isServer=isserver;
	sockets=SDLNet_AllocSocketSet(1); //2-player game
	
	if (isServer){

		//Assigning a new IP address if this a server
		SDLNet_ResolveHost(&ip,NULL,portNo);
		server = SDLNet_TCP_Open(&ip);

	}else{

		//Assigning the IP of the server if the current instance of the game
		//is a client
		SDLNet_ResolveHost(&ip,ip_addr,portNo);
		server=SDLNet_TCP_Open(&ip);
		if(server==NULL){
			cout<<"Unable to connect to server\n";
		}
		connected=true;
		SDLNet_TCP_AddSocket(sockets,server);

	}
}

//This function is called by a server to check for potential clients. Once 
//found, such clients are added to the socket set of the server
bool network::check_new_players(){
	if (isServer && !connected){
		TCPsocket temp_soc=SDLNet_TCP_Accept(server);
		if (temp_soc){
			client=temp_soc;
			connected=true;
			SDLNet_TCP_AddSocket(sockets,client);
			cout<<"New player joined:"<<"\n";
		}
	}else if(connected){ 
		cout<<"Entry denied:More players tried to connect\n";
		const char* msg="123456789";
		SDLNet_TCP_Send(client,msg,strlen(msg));
	}
	return connected;
}

//This method is used by the server or the clients to send some request or
//data, in the form of a string to the server or other clients
void network::send(string s,int* state,int* prevstate){

	//For disconnecting a client/server if it's connection times out 
	if (SDL_GetTicks()-timeout>5000){
		*prevstate=-1;
	}

	const char* tmp=&s[0];
	int size=0;
	int len=strlen(tmp);
	if (isServer){
		if (client==NULL){return;}
		while (size<len){
			if (SDL_GetTicks()-timeout>5000){
				*prevstate=-1;
		
			}
			size+=SDLNet_TCP_Send(client,tmp+size,len-size);
		}
	}else{
		if (server==NULL){cout<<"No server\n";exit(1);return;}
		while (size<len){
			if (SDL_GetTicks()-timeout>5000){
				*prevstate=-1;
				// *state=101;
			}
			size+=SDLNet_TCP_Send(server,tmp+size,len-size);
		}
	}
}

//This method is used to receive data or request from the server or clients
//essentially the opposite of send function 
string network::receive(int num,int* state,int* prevstate){

	//For disconnecting a client/server if it's connection times out 
	if (SDL_GetTicks()-timeout>5000){
		*prevstate=-1;
	}

	if (isServer && connected){
		if (SDLNet_CheckSockets(sockets,0)>0 && SDLNet_SocketReady(client)){
			timeout=SDL_GetTicks();
			int offset=0;
			char temp[num];
			string result;
			int offset_prv=-1;
			int test=0;
			while (offset<num && test<100){
				test++;
				offset_prv=offset;
				offset+=SDLNet_TCP_Recv(client,temp,num-result.size());	
				if (offset<=0){
					return "";
				}
				result+=string(temp).substr(0,min(num,(int)strlen(temp)));
			}
			return result;
		}
	}else if (connected){
		if (SDLNet_CheckSockets(sockets,0)>0 && SDLNet_SocketReady(server)){
			timeout=SDL_GetTicks();
			int offset=0;
			char temp[num];
			string result;
			int offset_prv=-1;
			int test=0;
			while (offset<num && test<100){
				test++;
				offset_prv=offset;
				offset+=SDLNet_TCP_Recv(server,temp,num-result.size());
				
				if (offset<=0){
					return "";
				}
				result+=string(temp).substr(0,min(num,(int)strlen(temp)));
			}
			return result;
		}
	}
	string x="";
	return x;
}
