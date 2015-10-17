#include "collision.h"
#include "entity.h"


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
	for (i = 0; i < MAX_ENTITIES; ++i)
	{
		if (getEntity(i))
		{
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
	if (player >= MAX_ENTITIES)return NULL;
	return &Entities[player];
}
/* Sets the first player's data */
void InitEntity(entity* e, char* mod_file, char* spr_file, int spr_x, int spr_y)
{
	vec3d_set(e->position, 0, 0, 0);
	vec3d_set(e->velocity, 0, 0, 0);
	vec3d_set(e->rotation, 0, 0, 0);
	e->hb.x = 0;
	e->hb.y = 0;
	e->hb.z = 0;
	Vec3d_set(e->hb.bounding.vmax, 1, 1, 1);
	Vec3d_set(e->hb.bounding.vmin, -1, -1, -1);
	e->gravity = 5;
	e->obj = obj_load(mod_file);
	e->texture = LoadSprite(spr_file, spr_x, spr_y);
}
/* Frees the memory that is held by the fighter */
void FreeEntity(entity* e)
{
	free(e);
	free(e->obj);
	FreeSprite(e->texture);
	memset(e,0,sizeof(entity));
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
