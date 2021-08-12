#include "SDL2/SDL_net.h"
#include <bits/stdc++.h>
using namespace std;
class network{


public:

	bool isServer=false;
	network(bool isserver,char* ip_addr,int portNo);
	void send(std::string s,int* state,int* prevstate);
	std::string receive(int num,int* state,int* prevstate);
	TCPsocket server,client;
	char temp[30];
	bool connected=false;
	bool isPlaying=false;
	SDLNet_SocketSet sockets;
	bool check_new_players();
	long long int timeout;

};