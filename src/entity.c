#include "entity.h"
#include "game.h"

extern Game game;

int entities_used = 0;

entity Entities[MAX_ENTITIES];

/* Initializes the fighter list that holds both of the player characters */
void InitEntityList()
{
	int i;
	for (i = 0; i<MAX_ENTITIES; ++i)
	{
		memset(&Entities[i], 0, sizeof(entity));
	}
}

entity* CreateEntity()
{
	int i;
	for (i = entities_used; i < MAX_ENTITIES; ++i)
	{
		if (getEntity(i))
		{
			entities_used = i + 1;
			return getEntity(i);
		}
		else
			printf("Cannot Create Entity, Max Entities Reached");
	}
	return NULL;
}

/* Gets the location of the fighter from the fighter list and returns the location */
entity * getEntity(int player)
{
	if (player >= MAX_ENTITIES) return NULL;
	return &Entities[player];
}
/* Sets the first player's data */
void InitEntity(entity* e, char* mod_file, char* spr_file, int spr_x, int spr_y)
{
	e->health = 100;

	vec3d_set(e->position, 0, 0, 0);
	vec3d_set(e->velocity, 0, 0, 0);
	vec3d_set(e->rotation, 0, 0, 0);
	
	e->hb.x = e->position.x;
	e->hb.y = e->position.y;
	e->hb.z = e->position.z;
	e->hb.d = 1;
	e->hb.w = 1;
	e->hb.h = 1;

	Vec3d_set(e->hb.bounding.vmax, 1, 1, 1);
	Vec3d_set(e->hb.bounding.vmin, -1, -1, -1);
	e->gravity = 5;
	e->obj = obj_load(mod_file);
	e->texture = LoadSprite(spr_file, spr_x, spr_y);
	SpaceAddBody(game.space, &e->body);
	e->body.owner = e;
}
/* Frees the memory that is held by the fighter */
void FreeEntity(entity* e)
{
	free(e->obj);
	FreeSprite(e->texture);
	memset(e,0,sizeof(entity));
	free(e);
}

void FreeEntityList()
{
	int i;
	for (i = 0; i < MAX_ENTITIES; ++i)
	{
		FreeEntity(&Entities[i]);
	}
}
void FreeEntityFromList(entity* e)
{
	if (&Entities[e->index] == NULL)
		printf("No such entity exists");
	FreeEntity(&Entities[e->index]);
}

/* Loads the fighter from a text file into the game */
void LoadEntity(entity* e, long character)
{

}
/* Allows the user to edit the data of any fighter */
int EditEntity()
{
	return 0;
}
