#ifndef _PARTICLE_
#define _PARTICLE_

#include "entity.h"

typedef struct particle_s
{
	Vec3D position;
	Vec3D scale;
	Vec3D velocity;
	Vec3D acceleration;
	Body* body;

}Particle;

#endif