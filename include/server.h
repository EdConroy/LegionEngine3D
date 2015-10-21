#include "SDL_net.h"

#define BLOCK_SIZE 1024
#define PORT 2345

typedef struct ServerData
{
	TCPsocket sd, csd;
	IPaddress ip, *remoteIP;
	int quit, quit2;
	char buffer[512];
	char* hostname;
}Server;

void server_setup();
void server_setup();
void server_connect();
void server_update();
void server_close_client();
void server_close();