#include <stdio.h>
#include <stdlib.h>
#include "SDL_net.h"
#include "entity.h"

#define MAX_SERVERS			1

typedef struct ServerData_T
{

	TCPsocket sd;
	TCPsocket csd;
	IPaddress ip; 
	IPaddress* remoteIP;
	char buffer[512];
	char* hostname;

}Server;

void server_init(Server* server);
Server* get_server(int server);

void server_setup();
void server_setup();
void server_connect();
entity* server_update(entity* e);
void server_close_client();
void server_close();