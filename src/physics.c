#include "physics.h"
#include <glib.h>
#include "collision.h"
#include "mgl_callback.h"

struct Space_T
{
	GList *bodylist;
	int steps;
	int stepstaken;
	float stepFactor;
};

space* NewSpace()
{
	space* sp;
	sp = (space*)calloc(1, sizeof(struct Space_T));
	return sp;
}

void SpaceSetSteps(space* sp, int steps)
{
	if (!sp) return;
	sp->steps = steps;
}

void SpaceDoStep(space* sp, int steps)
{
	if (!sp) return;
	if (!steps)
	{
		printf("cannot support zero steps!");
		return;
	}
	sp->steps = steps;
	sp->stepFactor = 1.0 / steps;
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
	sp->bodylist = g_list_append(sp->bodylist, body);
}

void SpaceRemoveBody(space* sp, Body* body)
{
	if (!sp) return;
	if (!body) return;
	sp->bodylist = g_list_remove(sp->bodylist, body);
}
void Add_Gravity(entity e)
{
	e.velocity.z -= e.gravity + 15 * .01;
	vec3d_add(e.position, e.position, e.velocity);
}

static void space_body_update(space *space, Body *body)
{
	GList *it;
	Cube a, b;
	Body *other;
	Vec3D stepVector;
	Vec3D stepOffVector;

	if ((!body) || (body->_done))return;

	vec3d_scale(stepVector, body->velocity, space->stepFactor);
	vec3d_negate(stepOffVector, stepVector);

	vec3d_add(body->position, body->position, stepVector);

	a.x = body->position.x + body->bounds.x;
	a.y = body->position.y + body->bounds.y;
	a.z = body->position.z + body->bounds.z;
	a.w = body->bounds.w;
	a.h = body->bounds.h;
	a.d = body->bounds.d;

	for (it = space->bodylist; it != NULL; it = g_list_next(it))
	{
		if (!it->data)continue;
		if (it->data == body)continue;
		/*check for collision*/
		other = (Body *)it->data;
		vec3d_cpy(b, other->position);
		b.w = other->bounds.w;
		b.h = other->bounds.h;
		b.d = other->bounds.d;
		vec3d_add(b, b, other->bounds);
		if (Rect3D_Overlap(a,b))
		{
			/*call touch functions*/
			/*back the fuck off*/
			vec3d_cpy(body->_stepOffVector, stepOffVector);
			body->_done = 1;
			body->_needsBackoff = 1;
			if (body->touch.function)
			{
				body->touch.function(body->touch.data, other);
			}
		}
	}
}

static void space_update(space *space)
{
	GList *it;
	for (it = space->bodylist; it != NULL; it = g_list_next(it))
	{
		if (!it->data)continue;
		space_body_update(space, (Body*)it->data);
	}
	for (it = space->bodylist; it != NULL; it = g_list_next(it))
	{
		if (!it->data)continue;
		body_process((Body *)it->data);
	}
}

void space_do_step(space *space)
{
	if (!space)return;
	if (space->stepstaken == space->steps)
	{
		space->stepstaken = 0;
		GList *it;
		for (it = space->bodylist; it != NULL; it = g_list_next(it))
		{
			if (!it->data)continue;
			body_reset((Body *)it->data);
		}
	}
	/*run one iteration of space update*/
	space_update(space);
	/*for each body, update it a little*/
	space->stepstaken++;
}

void body_reset(Body *body)
{
	if (!body)return;
	body->_needsBackoff = 0;
	body->_done = 0;
}

void body_process(Body *body)
{
	if (!body)return;
	if (body->_needsBackoff)
	{
		vec3d_add(body->position, body->position, body->_stepOffVector);
	}
}