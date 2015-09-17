#include "collision.h"
#include "vector.h"

#define SQUARE(a) ((a) * (a))

int AABB(SDL_Rect attacker, SDL_Rect defender)
{
	/*
	Checks if the boxes intersect by comparing the boxes (x and widths) and (y and heights)
	*/
	if ((attacker.x + attacker.w) > defender.x && (defender.x + defender.w) > attacker.x
		&& (attacker.y + attacker.w) > defender.y && (defender.y + defender.h) > attacker.y)
	{
		/* ReturnBox(attacker,defender,1,screen); */
		return 1;
	}
	return 0;
}
int Rect3D_Overlap(Cube EntityA, Cube EntityB)
{
	if (EntityA.x > (EntityB.x + EntityB.w) && EntityA.y > (EntityB.y + EntityB.h) &&
		EntityB.x > (EntityA.x + EntityA.w) && EntityB.y > (EntityA.y + EntityB.h) &&
		EntityB.z > (EntityA.z + EntityA.d) && EntityA.z > (EntityB.z + EntityB.d))
	{
		return 1;
	}
	return 0;
}
int Sphere3D_Overlap(Sphere a, Sphere b)
{
	if (SQUARE(a.r) + SQUARE(b.r) < (SQUARE(a.x - b.x) + SQUARE(a.y - b.y) + SQUARE(a.z - b.z)))
	{
		return 1;
	}
	return 0;
}

int Sphere_Cube_Overlap(Sphere a, Cube b)
{
	float cornerDistanceSQ;
	float circleDistanceX = abs(a.x - b.x);
	float circleDistanceY = abs(a.y - b.y);
	float circleDistanceZ = abs(a.z - b.z);

	if ((circleDistanceX > ((b.w / 2) + a.r)) || (circleDistanceY > ((b.h / 2) + a.r)) || (circleDistanceZ > ((b.d / 2) + a.r)))
		return 0;

	if ((circleDistanceX <= (b.w / 2)) || (circleDistanceY <= (b.h / 2)) || (circleDistanceZ <= (b.d / 2)))
		return 1;

	cornerDistanceSQ = (SQUARE(circleDistanceX - (b.w / 2)) + SQUARE(circleDistanceY - b.h / 2) + SQUARE(circleDistanceZ - b.d / 2));
	return (cornerDistanceSQ <= (SQUARE(a.r)));
}

