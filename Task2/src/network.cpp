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
		connected=true;
		SDLNet_TCP_AddSocket(sockets,server);	
	}
}

bool network::check_new_players(){
	if (isServer && !connected){
		TCPsocket temp_soc=SDLNet_TCP_Accept(server);
		if (temp_soc){
			client=temp_soc;
			if (!connected){
				connected=true;
				SDLNet_TCP_AddSocket(sockets,client);
				cout<<"New player joined:"<<"\n";
			}else{ 
				cout<<"Entry denied:More players tried to connect\n";
				const char* msg="123456789";
				SDLNet_TCP_Send(client,msg,strlen(msg));
			}	
		}
    }
	return connected;
}

void network::send(string s){
	cout<<"send\n";
	const char* tmp=&s[0];
	int size=0;
	int len=strlen(tmp);
	if (isServer){
		if (client==NULL){return;}
		while (size<len){
			size+=SDLNet_TCP_Send(client,tmp+size,len-size);
		}
	}else{
		if (server==NULL){return;}
		while (size<len){
			size+=SDLNet_TCP_Send(server,tmp+size,len-size);
		}
	}
}

string network::receive(int num){
	cout<<"receive\n";
	if (isServer && connected){
		if (SDLNet_CheckSockets(sockets,0)>0 && SDLNet_SocketReady(client)){
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
