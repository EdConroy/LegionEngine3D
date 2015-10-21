#include "SDL_net.h"

typedef struct ClientData
{
	IPaddress ip;
	TCPsocket sd;
	int quit, len;
	char buffer[512];
}Client;

void client_connect();
void client_update();
void client_close();