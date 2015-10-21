#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "server.h"

Client data;
Server sData;

void client_connect()
{
	if (SDLNet_Init() < 0)
	{
		printf("SDL Init (client): %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_ResolveHost(&data.ip, sData.hostname, 2000) < 0)
	{
		printf("SDL Resolve Host (client): %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (!(data.sd = SDLNet_TCP_Open(&data.ip)))
	{
		printf("SDL TCP Open (client): %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}
void client_update()
{
	printf("Write something:\n>");
	scanf("%s", data.buffer);

	data.len = strlen(data.buffer) + 1;
	if (SDLNet_TCP_Send(data.sd, (void*)data.buffer, data.len) < data.len)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}
void client_close()
{
	SDLNet_TCP_Close(data.sd);
	SDLNet_Quit();
	exit(EXIT_SUCCESS);
}