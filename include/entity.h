#ifndef _FIGHTER_
#define _FIGHTER_

#include "graphics3d.h"
#include "time.h"
#include "sprite.h"
#include "vector.h"
#include "obj.h"

#define IS_SET(a,b)				(a & b)
#define SET_FLAG(a,b)			(a |= b)
#define REMOVE_FLAG(a,b)		(a &= ~b)

#define MAX_ENTITIES				2

/* Indicates which fighter is currently being played by each player */
#define FIGHT_STRIDER				0

#define ENTITYFLAG_WALKL			0
#define ENTITYFLAG_WALKR			1
#define ENTITYFLAG_JUMP				2
#define ENTITYFLAG_IDLE				3
#define ENTITYFLAG_CROUCH			4
#define ENTITYFLAG_HITSTUN			5
/*
Indicates the current state of the player in the air
*/
#define JUMPFLAG_MOVEL				0
#define JUMPFLAG_MOVER				1
/*
States used for drawing the player character
*/
#define ANIMFLAG_WALKL				0
#define ANIMFLAG_WALKR				1
#define ANIMFLAG_JUMP				2
#define ANIMFLAG_IDLE				3
#define ANIMFLAG_CROUCH				4
#define ANIMFLAG_HITSTUN			5

typedef struct Cube_T
{
	float x;
	float y;
	float z;
	float w;
	float h;
	float d;
	Vec3DCompare bounding;
}Cube;

typedef struct Sphere_T
{
	float x;
	float y;
	float z;
	float w;
	float h;
	float d;
	float r;
}Sphere;

typedef struct Entity_T
{ 
	Obj* obj; 
	Cube hb;

	float walk_speed;
	float walk_acc;
	float run_speed;
	float run_acc;
	float fall_acc;
	float jump_speed;
	float jump_height;
	float current_speed;
	float current_acc;

	int x; /* Goin' give it to ya */
	int y;
	int z;
	int health;
	int weight;
	int facing; /* So the fighter knows which direction he is facing*/
	long id;

	float gravity;

	Vec3D position;
	Vec3D velocity;
	Vec3D rotation;
	Vec3D move_dir;

	clock_t t;
}entity;

typedef enum { false, true } lbool;

void InitEntity(entity* e, long character);
void InitEntityList(); /* Initializes the fighter list and populates it */
entity* CreateEntity();

entity* getEntity(int player);

void FreeEntity(entity* e);/* Frees all of the current memory held by the fighter and sets it to null*/
void FreeEntityList();
void CloseEntity();/* Frees all the fighters in the fighter list*/

void LoadEntity(entity* e, long character); /* Loads Fighter data from a .txt file*/
int EditEntity(); /* Edits the current data of the Fighter, only a temporary edit*/

#endif
