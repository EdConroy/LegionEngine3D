#include "vector.h"

Vec2D vec2d(float x, float y)
{
	Vec2D v = { x, y };
	return v;
}

Vec3D vec3d(float x, float y, float z)
{
	Vec3D v = { x, y, z };
	return v;
}

Vec4D vec4d(float x, float y, float z, float w)
{
	Vec4D v = { x, y, z, w };
	return v;
}

void AngleVectors(Vec3D angles, Vec3D* forward, Vec3D* right, Vec3D* up)
{
	float		angle;
	static float		sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles.x * (pi * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.y * (pi * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * (pi * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}
	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}
	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

/*eol@eof*/
