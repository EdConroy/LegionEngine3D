#ifndef _COLLISION_
#define _COLLISION_

#include "graphics3d.h"
#include "SDL.h"
#include "entity.h"
#include "vector.h"

typedef struct Ray_T
{
	Vec3 start;
	Vec3 dir;
	float t;
}Ray;

int AABB(SDL_Rect attacker, SDL_Rect defender); /* Axis Aligned Bounding Box collision system */
int Rect3D_Overlap(Cube EntityA, Cube EntityB);
int Sphere3D_Overlap(Sphere a, Sphere b);
int Sphere_Cube_Overlap(Sphere a, Cube b);
int Ray_Cube_Overlap(Vec3D point, Vec3D box, Vec3D size);
lbool ClipLine(int d, Vec3DCompare aabb, Vec3 v0, Vec3 v1);
lbool LineBoxOverlap(Vec3DCompare aabb, Vec3 v0, Vec3 v1);

#endif
