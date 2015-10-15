#include "vector.h"
#include "entity.h"

static void fire_weapon(entity* self, Vec3D start, Vec3D aim_dir, int damage, int kick, int hspread, int vspread, int mod);