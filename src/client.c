#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

Client data;
Server sData;

Client Clients[MAX_CLIENTS];

IPaddress ip;
TCPsocket sd, test;
IPaddress* remoteIP;
int quit, len;
char buffer[512];

void client_init(Client* client)
{
	malloc(sizeof(Client));
	client->ip.host = 2130706433;
	client->ip.port = 2000;
}
Client* get_client(int client)
{
	if (client >= MAX_SERVERS) return NULL;
	return &Clients[client];
}
void client_connect(Server* s_data)
{
	if (SDLNet_Init() < 0)
	{
		printf("SDL Init (client): %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_ResolveHost(&data.ip, s_data->hostname, 2000) < 0)
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
lbool client_commit()
{
	printf("Connecting ....\n");
	if (test = SDLNet_TCP_Accept(data.sd))
	{
		printf("Getting Peer Address....\n");
		if (remoteIP = SDLNet_TCP_GetPeerAddress(test))
		{
			printf("Host connected: %x, %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
			return true;
		}
		else
			printf("SDL TCP Get Peer Address: %s\n", SDLNet_GetError());
	}
	return false;
}
entity* client_update(entity* e)
{
	Vec3 temp = { 0, 0, 0 };
	//printf("Write something:\n>");
	//scanf("%s", data.buffer);

	//int len = strlen(data.buffer) + 1;
	if (SDLNet_TCP_Send(data.sd, (void*)e, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)e->obj, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)e->texture, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)e->health, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)&e->hb, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)&e->acceleration, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)&e->position, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)&e->velocity, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)&e->body, 1024) < 0)
	{
		if (SDLNet_TCP_Send(data.sd, (void*)&e->body.bounds, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDLNet_TCP_Send(data.sd, (void*)e->body.owner, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDLNet_TCP_Send(data.sd, (void*)&e->body.position, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDLNet_TCP_Send(data.sd, (void*)&e->body.velocity, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)e->id, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)e->weapon_flag, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(data.sd, (void*)e->index, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	return e;
}
entity* client_recieve(entity* e)
{
	if (SDLNet_TCP_Recv(data.sd, (void*)e, 1024) > 0)
	{
		printf("Client Data: %f,%f,%f\n", e->position.x, e->position.y, e->position.z);
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)e->obj, 1024) > 0)
	{
		printf("Sent Model Data");
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)e->texture, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)e->health, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)&e->hb, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)&e->acceleration, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)&e->position, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)&e->velocity, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)&e->body, 1024) > 0)
	{
		if (SDLNet_TCP_Recv(data.sd, (void*)&e->body.bounds, 1024) > 0)
		{
			;
		}
		if (SDLNet_TCP_Recv(data.sd, (void*)e->body.owner, 1024) > 0)
		{
			;
		}
		if (SDLNet_TCP_Recv(data.sd, (void*)&e->body.position, 1024) > 0)
		{
			;
		}
		if (SDLNet_TCP_Recv(data.sd, (void*)&e->body.velocity, 1024) > 0)
		{
			;
		}
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)e->id, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)e->weapon_flag, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(data.sd, (void*)e->index, 1024) > 0)
	{
		;
	}
}
void client_close()
{
	SDLNet_TCP_Close(data.sd);
	SDLNet_Quit();
	exit(EXIT_SUCCESS);
}
