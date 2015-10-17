#include "vector.h"
#include "entity.h"

static void fire_weapon(entity* self, entity* enemy, Vec3 start, Vec3 aim_dir, int damage, int kick, int hspread, int vspread, int mod);