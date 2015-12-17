#include "collision.h"

#define EPSILON .00000001
#define CROSS(dest, v1, v2) (dest[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]), dest[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]), dest[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]))
#define DOT(v1, v2) ((v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]))
#define SUB(dest, v1, v2) (dest[0] = v1[0] - v2[0], dest[1] = v1[1] - v2[1], dest[2] = v1[2] - v2[2])

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
	if (EntityA.x < (EntityB.x + EntityB.w) && EntityA.y < (EntityB.y + EntityB.h) &&
		EntityB.x < (EntityA.x + EntityA.w) && EntityB.y < (EntityA.y + EntityB.h) &&
		EntityB.z < (EntityA.z + EntityA.d) && EntityA.z < (EntityB.z + EntityB.d))
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

int Cube_Cube_Overlap(Cube a, Cube b)
{
	if (a.x > b.x + b.w || b.x > a.x + a.w ||
		a.y > b.y + b.h || b.y > a.y + a.h ||
		a.z > b.z + b.z || b.z > a.z + a.d)
	{
		return 0;
	}
	return 1;
}
int Point_Cube_Overlap(Vec3D point, Vec3D box, Vec3D size)
{
	if ((point.x < box.x) ||
		(point.y < box.y) ||
		(point.z < box.z) ||
		(point.x > box.x + size.x) ||
		(point.y > box.y + size.y) ||
		(point.z > box.z + size.z))
	{
		return 0;
	}
	return 1;
}
lbool ClipLine(int d, Vec3 planes, Vec3 v0, Vec3 v1)
{
	/* v0 is the start point of the ray while v1 is the end point*/
	int temp;
	float f_dim_low, f_dim_high;

	printf("calling Clip Line \n");
	f_dim_low = min(v0[d], v1[d]);
	f_dim_high = max(v0[d], v1[d]);

	if (planes[d] >= f_dim_low && planes[d] <= f_dim_high)
		return true;
	return false;
}
lbool LineBoxOverlap(Vec3DCompare aabb, Vec3 v0, Vec3 v1)
{
	/* v0 is the start point of the ray while v1 is the end point*/
	float f_low = 0;
	float f_high = 1;

	Vec3 closest, temp;
	float closest_dist, temp_dist,
		slope, dist, height, width;

	closest_dist = 10000000000000;

	if (ClipLine(0, aabb.vmin, v0, v1))
	{
		temp_dist = v1[0] - v0[0];
		if (temp_dist == 0)
		{
			;
		}
		slope = (v1[1] - v0[1]) / temp_dist;
		dist = aabb.vmin[0] - v0[0];
		height = dist * slope + v0[1];
		slope = (v1[2] - v0[2]) / temp_dist;
		width = dist * slope + v0[2];
		printf("%f, %f\n", height, width);

		if (height >= aabb.vmin[1] && height <= aabb.vmax[1]
			&& width >= aabb.vmin[2] && width <= aabb.vmax[2])
		{
			Vec3d_set(closest, aabb.vmin[0], height, width);
			Vec3d_sub(temp, closest, v0);
			Vec3d_length(closest_dist, temp);
			printf("we made it yo\n");
			printf("%f,%f,%f,%f\n", closest_dist, closest[0], closest[1], closest[2]);
		}
	}
	if (ClipLine(0, aabb.vmax, v0, v1))
	{
		temp_dist = v1[0] - v0[0];
		if (temp_dist == 0)
		{
			;
		}
		slope = (v1[1] - v0[1]) / temp_dist;
		dist = aabb.vmax[0] - v0[0];
		height = dist * slope + v0[1];
		slope = (v1[2] - v0[2]) / temp_dist;
		width = dist * slope + v0[2];
		printf("%f, %f\n", height, width);

		if (height >= aabb.vmin[1] && height <= aabb.vmax[1]
			&& width >= aabb.vmin[2] && width <= aabb.vmax[2])
		{
			Vec3d_set(temp, aabb.vmax[0], height, width);
			Vec3d_sub(temp, temp, v0);
			Vec3d_length(temp_dist, temp);
			if (temp_dist < closest_dist || closest_dist == -1)
			{
				closest_dist = temp_dist;
				Vec3d_set(closest, aabb.vmax[0], height, width);
			}
			printf("we made it yo\n");
			printf("%f,%f,%f,%f\n", closest_dist, closest[0], closest[1], closest[2]);
		}
	}
	if (ClipLine(1, aabb.vmin, v0, v1))
	{
		temp_dist = v1[1] - v0[1];
		if (temp_dist == 0)
		{
			;
		}
		slope = (v1[0] - v0[0]) / temp_dist;
		dist = aabb.vmin[1] - v0[1];
		height = dist * slope + v0[0];
		slope = (v1[2] - v0[2]) / temp_dist;
		width = dist * slope + v0[2];
		printf("%f, %f\n", height, width);

		if (height >= aabb.vmin[0] && height <= aabb.vmax[0]
			&& width >= aabb.vmin[2] && width <= aabb.vmax[2])
		{
			Vec3d_set(temp, height, aabb.vmin[1], width);
			Vec3d_sub(temp, temp, v0);
			Vec3d_length(temp_dist, temp);
			if (temp_dist < closest_dist || closest_dist == -1)
			{
				closest_dist = temp_dist;
				Vec3d_set(closest, height, aabb.vmin[1], width);
			}
			printf("we made it yo\n");
			printf("%f,%f,%f,%f\n", closest_dist, closest[0], closest[1], closest[2]);
		}
	}
	if (ClipLine(1, aabb.vmax, v0, v1))
	{
		temp_dist = v1[1] - v0[1];
		if (temp_dist == 0)
		{
			;
		}
		slope = (v1[0] - v0[0]) / temp_dist;
		dist = aabb.vmax[1] - v0[1];
		height = dist * slope + v0[0];
		slope = (v1[2] - v0[2]) / temp_dist;
		width = dist * slope + v0[2];
		printf("%f, %f\n", height, width);

		if (height >= aabb.vmin[0] && height <= aabb.vmax[0]
			&& width >= aabb.vmin[2] && width <= aabb.vmax[2])
		{
			Vec3d_set(temp, height, aabb.vmax[1], width);
			Vec3d_sub(temp, temp, v0);
			Vec3d_length(temp_dist, temp);
			if (temp_dist < closest_dist || closest_dist == -1)
			{
				closest_dist = temp_dist;
				Vec3d_set(closest, height, aabb.vmax[1], width);
			}
			printf("we made it yo\n");
			printf("%f,%f,%f,%f\n", closest_dist, closest[0], closest[1], closest[2]);
		}
	}
	if (ClipLine(2, aabb.vmin, v0, v1))
	{
		temp_dist = v1[2] - v0[2];
		if (temp_dist == 0)
		{
			;
		}
		slope = (v1[0] - v0[0]) / temp_dist;
		dist = aabb.vmin[2] - v0[2];
		height = dist * slope + v0[0];
		slope = (v1[1] - v0[1]) / temp_dist;
		width = dist * slope + v0[1];
		printf("%f, %f\n", height, width);

		if (height >= aabb.vmin[0] && height <= aabb.vmax[0]
			&& width >= aabb.vmin[1] && width <= aabb.vmax[1])
		{
			Vec3d_set(temp, height, width, aabb.vmin[2]);
			Vec3d_sub(temp, temp, v0);
			Vec3d_length(temp_dist, temp);
			if (temp_dist < closest_dist || closest_dist == -1)
			{
				closest_dist = temp_dist;
				Vec3d_set(closest, height, width, aabb.vmin[2]);
			}
			printf("we made it yo\n");
			printf("%f,%f,%f,%f\n", closest_dist, closest[0], closest[1], closest[2]);
		}
	}
	if (ClipLine(2, aabb.vmax, v0, v1))
	{
		temp_dist = v1[2] - v0[2];
		if (temp_dist == 0)
		{
			;
		}
		slope = (v1[0] - v0[0]) / temp_dist;
		dist = aabb.vmax[2] - v0[2];
		height = dist * slope + v0[0];
		slope = (v1[1] - v0[1]) / temp_dist;
		width = dist * slope + v0[1];
		printf("%f, %f\n", height, width);

		if (height >= aabb.vmin[0] && height <= aabb.vmax[0]
			&& width >= aabb.vmin[1] && width <= aabb.vmax[1])
		{
			Vec3d_set(temp, height, width, aabb.vmax[2]);
			Vec3d_sub(temp, temp, v0);
			Vec3d_length(temp_dist, temp);
			if (temp_dist < closest_dist || closest_dist == -1)
			{
				closest_dist = temp_dist;
				Vec3d_set(closest, height, width, aabb.vmax[2]);
			}
			printf("we made it yo\n");
			printf("%f,%f,%f,%f\n", closest_dist, closest[0], closest[1], closest[2]);
		}
	}
	if (ClipLine(0, aabb.vmin, v0, v1) ||
		ClipLine(0, aabb.vmax, v0, v1) ||
		ClipLine(1, aabb.vmin, v0, v1) ||
		ClipLine(1, aabb.vmax, v0, v1) ||
		ClipLine(2, aabb.vmin, v0, v1) ||
		ClipLine(2, aabb.vmax, v0, v1))
		return true;

	return false;
}
lbool RayTriangleCollision(Vec3 origin, Vec3 dir, Vec3 vert0, Vec3 vert1, Vec3 vert2)
{
	Vec3 edge1, edge2, tvec, pvec, qvec;
	float det, inv_det;
	float t, u, v;

	/* find vectors for two edges sharing vert0*/
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);

	/* begin calculating determinant - also used to calculated U parameter */
	CROSS(pvec, dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle*/
	det = DOT(edge1, pvec);
#ifdef TEST_CULL /* Define TEST_CULL if culling */
	if (det < EPSILON)
		return false;

	/* calculate distance from vert0 to ray origin */
	SUB(tvec, origin, vert0);

	/* calculate U parameter and test bounds*/
	u = DOT(tvec, pvec);

	if (*u < 0.0 || *u > det)
		return false;

	CROSS(qvec, tvec, edge1);

	/* calculate V parameter and test bounds*/
	v = DOT(dir, qvec);

	if (*v < 0.0 || *u + *v > det)
		return false;

	/* calculate t, scale parameters, ray intersects triangle*/
	t = DOT(edge2, qvec);
	inv_det = 1.0 / det;
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;
#else /* Non-culling branch*/
	if (det > -EPSILON && det < EPSILON)
		return false;

	inv_det = 1.0 / det;

	/* calculate distance from vert0 to ray origin */
	SUB(tvec, origin, vert0);

	/* calculate U parameter and test bounds */
	u = DOT(tvec, pvec) * inv_det;

	if (u < 0.0 || u > 1.0)
		return false;

	CROSS(qvec, tvec, edge1);

	/* calculate V parameter and test bounds */
	v = DOT(dir, qvec) * inv_det;

	if (v < 0.0 || u + v > 1.0)
		return false;

	/* calculate t, ray intersects triangle */
	t = DOT(edge2, qvec) * inv_det;
#endif
	return true;
}