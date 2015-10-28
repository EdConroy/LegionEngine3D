#include "physics.h"
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
	if (SDLNet_TCP_Recv(csd, (void*) e, 1024) > 0)
	{
		printf("Client Data: %f,%f,%f\n", e->position.x, e->position.y, e->position.z);
	}
	if (SDLNet_TCP_Recv(csd, (void*) e->obj, 1024) > 0)
	{
		printf("Sent Model Data");
	}
	if (SDLNet_TCP_Recv(csd, (void*)e->texture, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)e->health, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)&e->hb, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)&e->acceleration, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)&e->position, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)&e->velocity, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)&e->body, 1024) > 0)
	{
		if (SDLNet_TCP_Recv(csd, (void*)&e->body.bounds, 1024) > 0)
		{
			;
		}
		if (SDLNet_TCP_Recv(csd, (void*)e->body.owner, 1024) > 0)
		{
			;
		}
		if (SDLNet_TCP_Recv(csd, (void*)&e->body.position, 1024) > 0)
		{
			;
		}
		if (SDLNet_TCP_Recv(csd, (void*)&e->body.velocity, 1024) > 0)
		{
			;
		}
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)e->id, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)e->weapon_flag, 1024) > 0)
	{
		;
	}
	if (SDLNet_TCP_Recv(csd, (void*)e->index, 1024) > 0)
	{
		;
	}
	return e;
}
space* server_update_space(space* s)
{
	if (SDLNet_TCP_Recv(csd, (void*)s, 1024) > 0)
	{
		printf("Sent Server Space Data \n");
		//exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Recv(csd, (void*)&s->bodylist, 1024) > 0)
	{
		if (SDLNet_TCP_Recv(csd, (void*)&s->bodylist->data, 1024) > 0)
		{
			printf("Sent Server Space Data \n");
			//exit(EXIT_FAILURE);
		}
		/*
		if (&s->bodylist->next != NULL)
		{
			if (SDLNet_TCP_Recv(csd, (void*)&s->bodylist->next, 1024) > 0)
			{
				printf("Sent Server Space Data \n");
				//exit(EXIT_FAILURE);
			}
		}
		if (&s->bodylist->next != NULL)
		{
			if (SDLNet_TCP_Recv(csd, (void*)&s->bodylist->prev, 1024) > 0)
			{
				printf("Sent Server Space Data \n");
				//exit(EXIT_FAILURE);
			}
		}
		*/
		printf("Sent Server Space Data \n");
		//exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Recv(csd, (void*)&s->stepVector, 1024) > 0)
	{
		printf("Sent Server Space Data \n");
		//exit(EXIT_FAILURE);
	}
	return s;
}
entity* server_send(entity* e)
{
	Vec3 temp = { 0, 0, 0 };
	//printf("Write something:\n>");
	//scanf("%s", data.buffer);

	//int len = strlen(data.buffer) + 1;
	if (SDLNet_TCP_Send(csd, (void*)e, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)e->obj, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)e->texture, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)e->health, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)&e->hb, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)&e->acceleration, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)&e->position, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)&e->velocity, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)&e->body, 1024) < 0)
	{
		if (SDLNet_TCP_Send(csd, (void*)&e->body.bounds, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDLNet_TCP_Send(csd, (void*)e->body.owner, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDLNet_TCP_Send(csd, (void*)&e->body.position, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		if (SDLNet_TCP_Send(csd, (void*)&e->body.velocity, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)e->id, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)e->weapon_flag, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)e->index, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	return e;
}
space* server_send_space(space* s)
{
	if (SDLNet_TCP_Send(csd, (void*)s, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)&s->bodylist, 1024) < 0)
	{
		if (SDLNet_TCP_Send(csd, (void*)&s->bodylist->data, 1024) < 0)
		{
			printf("Failed to send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
		/*
		if (SDLNet_TCP_Send(csd, (void*)&s->bodylist->next, 1024) < 0)
		{
				printf("Failed to send: %s\n", SDLNet_GetError());
				exit(EXIT_FAILURE);
		}
		if (SDLNet_TCP_Send(csd, (void*)&s->bodylist->prev, 1024) < 0)
		{
				printf("Failed to send: %s\n", SDLNet_GetError());
				exit(EXIT_FAILURE);
		}
		*/
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_TCP_Send(csd, (void*)&s->stepVector, 1024) < 0)
	{
		printf("Failed to send: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	return s;
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
