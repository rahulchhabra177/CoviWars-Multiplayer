#include "network.h"
using namespace std;

network::network(bool isserver){
	SDLNet_Init();
	IPaddress ip;	
	isServer=isserver;
	sockets=SDLNet_AllocSocketSet(1); //2-player game
	if (isServer){
		SDLNet_ResolveHost(&ip,NULL,1504);
		server = SDLNet_TCP_Open(&ip);
	}else{
		SDLNet_ResolveHost(&ip,"127.0.0.1",1504);
		server=SDLNet_TCP_Open(&ip);
		if(server==NULL){
			cout<<"Unable to connect to server\n";
		}
		connected=true;
		SDLNet_TCP_AddSocket(sockets,server);	
	}
}

bool network::check_new_players(){
	if (isServer && !connected){
		TCPsocket temp_soc=SDLNet_TCP_Accept(server);
		if (temp_soc){
			client=temp_soc;
			connected=true;
			SDLNet_TCP_AddSocket(sockets,client);
			cout<<"New player joined:"<<"\n";
			
		}
    }
    else if (connected){

    			cout<<"Entry denied:More players tried to connect\n";
				const char* msg="Access Denied";
				SDLNet_TCP_Send(client,msg,strlen(msg));

    }
	return connected;
}

void network::send(string s,int * state,int* prevstate){
	cout<<"send\n";
	if (SDL_GetTicks()-timeout>5000){
		*prevstate=*state;
		*state=101;
	}
	const char* tmp=&s[0];
	int size=0;
	int len=strlen(tmp);
	if (isServer){
		if (client==NULL){return;}
		while (size<len){
			if (SDL_GetTicks()-timeout>5000){
				*prevstate=*state;
				*state=101;
			}
			cout<<"size::\n";
			size+=SDLNet_TCP_Send(client,tmp+size,len-size);
			cout<<"size:\n";
		}
	}else{
		if (server==NULL){cout<<"No server\n";exit(1);return;}
		while (size<len){
			if (SDL_GetTicks()-timeout>5000){
				*prevstate=*state;
				*state=101;
			}

			cout<<"size::\n";
			size+=SDLNet_TCP_Send(server,tmp+size,len-size);
			cout<<"size:\n";
		}
	}
}

string network::receive(int num,int * state , int* prevstate){
	cout<<"receive\n";
	if (SDL_GetTicks()-timeout>5000){
		*prevstate=*state;
		*state=101;
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
				cout<<offset<<":"<<num<<":"<<result.size()<<":"<<result<<": offset\n";
				offset_prv=offset;
				offset+=SDLNet_TCP_Recv(client,temp,num-result.size());	
				if (offset<=0){
					cout<<"NOTYET|\n";
					return "";
				}
				result+=string(temp).substr(0,min(num,(int)strlen(temp)));
			}
			cout<<"Packet Recieved:"<<result<<":"<<result.size()<<"\n";
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
				cout<<offset<<":"<<num<<":"<<result.size()<<":"<<result<<": offset\n";
				offset_prv=offset;
				offset+=SDLNet_TCP_Recv(server,temp,num-result.size());
				
				if (offset<=0){
					// cout<<"NOTYET\n";
					return "";
				}
				result+=string(temp).substr(0,min(num,(int)strlen(temp)));
			

			}
			// SDLNet_TCP_Recv(client,temp,20);
			cout<<"Packet Recieved:"<<result<<":"<<result.size()<<"\n";
			return result;
		}
	}
	string x="";
	return x;
}
