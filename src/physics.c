#include "physics.h"
//#include <glib.h>

struct Space_T
{
	//GList *bodylist;
	int steps;
	int stepstaken;
};

space* NewSpace()
{
	space *sp;
	sp = (space*)calloc(1 , sizeof(struct Space_T));
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
	//sp->bodylist = g_list_append(sp->bodylist, body);
}
void SpaceRemoveBody(space* sp, Body* body)
{
	if (!sp) return;
	if (!body) return;
	//sp->bodylist = g_list_remove(sp->bodylist, body);
}
