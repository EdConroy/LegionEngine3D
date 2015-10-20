#include "weapon.h"

void fire_weapon(entity* self, entity* enemy, Vec3 start, Vec3 aim_dir, int damage, int mod)
{
	Ray shot;
	float speed;

	Vec3d_cpy(shot.start, start);
	Vec3d_cpy(shot.dir, aim_dir);
	shot.t = speed;

	if (LineBoxOverlap(enemy->hb.bounding, start, aim_dir))
	{
		enemy->health -= damage;
	}
}
entity* rocket_init(entity* player)
{
	entity* rocket;

	rocket = CreateEntity();
	InitEntity(rocket, "models/cube.obj", "models/cube_text.png", 1024, 1024);
	vec3d_set(rocket->position, player->position.x, player->position.y + 1, player->position.z);
	vec3d_set(rocket->acceleration, 0, 4, 0);

	return rocket;
}
void rocket_fly(entity* self, Vec3D start, Vec3D aim_dir)
{
	self->hb.x = self->position.x;
	self->hb.y = self->position.y;
	self->hb.z = self->position.z;
	/*
	float length;

	vec3d_length(length, aim_dir);
	vec3d_scale(self->velocity, aim_dir, 100 / length);
	vectorMA(self->position, .01, self->velocity, self->position);
	*/
}
void rocket_touch(entity* self, entity* other)
{
	int damage = 50;
	int sp_damage = 50;
	Sphere sphere;

	sphere.x = self->position.x;
	sphere.y = self->position.y;
	sphere.z = self->position.z;
	sphere.r = 15;
	sphere.h = 8;

	other->health -= damage;

	if (Sphere_Cube_Overlap(sphere, other->hb))
	{
		other->health -= sp_damage;
		FreeEntityFromList(self);
		return;
	}
}
void fire_rocket(entity* rocket, entity* enemy, Vec3D start, Vec3D aim_dir, int damage, int sp_damage, int mod)
{
	rocket_fly(rocket, start, aim_dir);

	if (Rect3D_Overlap(rocket->hb, enemy->hb))
	{
		rocket_touch(rocket, enemy);
	}
}
void use_knife(entity* self, entity* enemy)
{
	Cube knife_box;

	knife_box.x = self->position.x;
	knife_box.y = self->position.y;
	knife_box.z = self->position.z;
	
	knife_box.w = self->hb.w + 2;
	knife_box.h = self->hb.h + 2;
	knife_box.d = self->hb.d + 2;

	if (Rect3D_Overlap(knife_box, enemy->hb))
	{
		enemy->health = 0;
		printf("Enemy Health: %i\n", enemy->health);
	}
}