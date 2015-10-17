#include "weapon.h"
#include "collision.h"

static void fire_weapon(entity* self, entity* enemy, Vec3 start, Vec3 aim_dir, int damage, int kick, int hspread, int vspread, int mod)
{
	Ray shot;
	float speed;

	Vec3d_cpy(shot.start, start);
	Vec3d_cpy(shot.dir, aim_dir);
	shot.t = speed;

	if(LineBoxOverlap(enemy->hb.bounding, start, aim_dir, NULL, 0))
	{
		enemy->health -= damage;
	}
}

static void fire_rocket(entity* self, entity* enemy, Vec3D start, Vec3D aim_dir, int damage, int sp_damage, int mod)
{
	entity* rocket;
	float length;

	vec3d_length(length, aim_dir);
	vec3d_scale(rocket->velocity, aim_dir, 100 / length);
	vectorMA(rocket->position, .01, rocket->velocity, rocket->position);

	if (Rect3D_Overlap(rocket->hb, enemy->hb))
	{
		;
	}
}