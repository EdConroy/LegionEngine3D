#ifndef _ENTITY_
#define _ENTITY_

#include <time.h>
#include "sprite.h"
#include "vector.h"
#include "obj.h"
#include "physics.h"

#define IS_SET(a,b)				(a & b)
#define SET_FLAG(a,b)			(a |= b)
#define REMOVE_FLAG(a,b)		(a &= ~b)

#define MAX_ENTITIES				1000000

/* Indicates which fighter is currently being played by each player */

#define ENTITYFLAG_JUMP				0
#define ENTITYFLAG_GROUNDED			1

#define EFLAG_PLAYER				0
#define EFLAG_PICKUP				1
#define EFLAG_PLATFORM				2

#define ENFLAG_DEAD					0
#define ENFLAG_ALIVE				1

#define WFLAG_RIFLE					0
#define WFLAG_KNIFE					1
#define WFLAG_ROCKET				2

typedef struct Entity_T
{
	Sprite* texture;
	Obj* obj;
	Cube hb;
	Body body;

	int health;
	int index;
	long id;
	long type;
	long flag;
	
	long weapon_flag;
	long jump_flag;

	float gravity;

	Vec3D position;
	Vec3D velocity;
	Vec3D acceleration;
	Vec3D rotation;
	Vec3D move_dir;

	clock_t t;

	void(*think) (struct Entity_T);
	void(*touch) (struct Entity_T, struct Entity_T);
	void(*update) (struct Entity_T);
}entity;



void InitEntity(entity* e, char* mod_file, char* spr_file, int spr_x, int spr_y);
void InitEntityList(); /* Initializes the fighter list and populates it */
entity* CreateEntity();

entity* getEntity(int player);

void FreeEntity(entity* e);/* Frees all of the current memory held by the fighter and sets it to null*/
void FreeEntityList();
void FreeEntityFromList(entity* e);
void CloseEntity();/* Frees all the fighters in the fighter list*/

void Player1Pull(SDL_Event events, entity* player, entity* enemy, lbool rocket_fired);
void Player2Pull(SDL_Event events, entity* player, entity* enemy, lbool rocket_fired);

void update_rocket(entity* rocket, entity* player, entity* enemy, double time, lbool fired);

void entity_load(entity* e);
int entity_edit();

#endif
