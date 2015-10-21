#include <stdio.h>
#include <stdlib.h>
#include "server.h"

Server data;

void server_setup()
{
	if (SDLNet_Init() < 0)
	{
		printf("SDL Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_ResolveHost(&data.ip, NULL, 2000) < 0)
	{
		printf("SDL Resolve Host: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (!(data.sd = SDLNet_TCP_Open(&data.ip)))
	{
		printf("SDL TCP Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}
void server_connect()
{
	if (data.csd = SDL_TCP_Accept(data.sd))
	{
		if (data.remoteIP = SDLNet_TCP_GetPeerAddress(data.csd))
		{
			printf("Host connected: %x, %d\n", SDLNet_Read32(&data.remoteIP->host), SDLNet_Read16(&data.remoteIP->port));
		}
		else
			printf("SDL TCP Get Peer Address: %s\n", SDLNet_GetError());
	}
}
void server_update()
{
	while (1)
	{
		if (SDLNet_TCP_Recv(data.csd, data.buffer, 512) > 0)
		{
			printf("Client Data: %s\n", data.buffer);
		}
	}
	server_close_client();
}
void server_close_client()
{
	SDLNet_TCP_Close(data.csd);
}
void server_close()
{
	SDLNet_TCP_Close(data.sd);
	SDLNet_Quit();
	exit(EXIT_SUCCESS);
}