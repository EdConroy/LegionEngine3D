#include "server.h"

#define MAX_CLIENTS			2

typedef struct ClientData
{
	IPaddress ip;
	TCPsocket sd;
	int quit, len;
	char buffer[512];
}Client;

void client_init(Client* client);
Client* get_client(int client);

void client_connect(Server* s_data);
entity* client_update(entity* e);
entity* client_recieve(entity* e);
void client_close();