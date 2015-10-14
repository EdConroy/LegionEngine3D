#include "physics.h"
#include "legion_lib.h"

struct Space_T
{
	node *bodylist;
	int steps;
	int stepstaken;
};

space* NewSpace()
{
	space *sp;
	sp = (space*)calloc(1 , sizeof(struct Space_T));
	sp->bodylist = malloc(sizeof(node));
}

void SpaceSetSteps(space* sp, int steps)
{
	if (!sp) return;
	sp->steps = steps;
}
void SpaceDoStep(space* sp)
{
	if (!sp) return;
	if (sp->stepstaken == sp->steps)
		sp->stepstaken = 0;
	sp->stepstaken++;
}
void space_free(space* sp)
{
	if (!sp) return;
	memset(sp, 0, sizeof(space));
}
void SpaceAddBody(space* sp, Body* body)
{
	if (!sp) return;
	if (!body) return;
	legion_push_to_front(sp->bodylist->head, body);
}
void SpaceRemoveBody(space* sp, Body* body)
{
	if (!sp) return;
	if (!body) return;
	legion_remove_by_value(sp->bodylist, body);
}
void Add_Gravity(entity e)
{
	e.velocity.z -= e.gravity + 15 * .01;
	vec3d_add(e.position, e.position, e.velocity);
}
