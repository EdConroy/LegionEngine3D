#include "entity.h"

void fire_weapon(entity* self, entity* enemy, Vec3 start, Vec3 aim_dir, int damage, int mod);

void use_knife(entity* self, entity* enemy);

void rocket_fly(entity* self, Vec3D start, Vec3D aim_dir);
void rocket_touch(entity* self, entity* other);
void fire_rocket(entity* rocket, entity* enemy, Vec3D start, Vec3D aim_dir, int damage, int sp_damage, int mod);
entity* rocket_init(entity* player);
void rocket_kill(entity* rocket);
void weapon_spawn_collision(entity* player, entity* self);