#include "server.h"

Server data;

Server Servers[MAX_SERVERS];

TCPsocket sd;
TCPsocket csd;
IPaddress ip;
IPaddress* remoteIP;
char buffer[512];
char* hostname;


void server_init(Server* server)
{
	malloc(sizeof(Server));
	server->hostname = "Eddy-PC";
	server->ip.host = 3232235784;
	server->ip.port = 2000;
}
Server* get_server(int server)
{
	if (server >= MAX_SERVERS) return NULL;
	return &Servers[server];
}
void server_setup()
{
	if (SDLNet_Init() < 0)
	{
		printf("SDL Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_ResolveHost(&ip, NULL, 2000) < 0)
	{
		printf("SDL Resolve Host: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		printf("SDL TCP Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	printf("Initialization Complete\n");
}
lbool server_connect()
{
	printf("Connecting ....\n");
	if (csd = SDLNet_TCP_Accept(sd))
	{
		printf("Getting Peer Address....\n");
		if (remoteIP = SDLNet_TCP_GetPeerAddress(csd))
		{
			printf("Host connected: %x, %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
			return true;
		}
		else
			printf("SDL TCP Get Peer Address: %s\n", SDLNet_GetError());
		//server_update();
	}
	return false;
}
entity* server_update(entity* e)
{
	if (SDLNet_TCP_Recv(csd, (void*)e, 1024) > 0)
	{
		//printf("Client Data: %f,%f,%f,%i\n", e->position.x, e->position.y, e->position.z, e->health);
		return e;
	}
}
entity* server_send(entity* e)
{
	//printf("Write something:\n>");
	//scanf("%s", data.buffer);

	//int len = strlen(data.buffer) + 1;
	if (SDLNet_TCP_Send(csd, (void*)e, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	return e;
}
void server_close_client()
{
	SDLNet_TCP_Close(csd);
}
void server_close()
{
	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
	exit(EXIT_SUCCESS);
}