#include "SDL2/SDL_net.h"
#include <bits/stdc++.h>
using namespace std;
class network{


public:

	bool isServer=false;
	network(bool isserver);
	void send(std::string s);
	std::string recieve(int num);
	TCPsocket server,client;
	char temp[30];
	bool connected=false;
	SDLNet_SocketSet sockets;
	bool check_new_players();
	string getResponse(string res,int num);

};