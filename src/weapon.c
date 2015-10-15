#include "weapon.h"
#include "collision.h"

static void fire_weapon(entity* self, Vec3D start, Vec3D aim_dir, int damage, int kick, int hspread, int vspread, int mod)
{
	Vec3D dir;
	Vec3D forward, right, up;
	Vec3D end;

	VectorMA(start, 8192, forward, end);
}