#ifndef _PHYSICS_
#define _PHYSICS_

#include "collision.h"
#include "mgl_callback.h"

typedef struct Body_T
{
	Vec3D position;
	Vec3D velocity;
	Cube bounds;
	MglCallback touch;
	int  _needsBackoff;
	int  _done;
	Vec3D _stepOffVector;
	struct Entity_T* owner;
}Body;


typedef struct Space_T space;

space* NewSpace();
void SpaceSetSteps(space* sp, int steps);
void SpaceDoStep(space* sp, int steps);
void space_free(space* sp);
void SpaceAddBody(space* sp, Body* body);
void SpaceRemoveBody(space* sp, Body* body);
static void space_body_update(space *space, Body *body);
static void space_update(space *space);
void space_do_step(space *space);

void body_reset(Body *body);
void body_process(Body *body);

void Add_Gravity(Body* body);
#endif