#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>

#define swap(c, a, b) (c = b, a = b, b = c)
#define max(a,b) ((a < b)? b : a)
#define min(a,b) ((a > b)? b : a)
#define SQUARE(a) ((a) * (a))

typedef struct
{
	float x, y;
}Vec2D;

typedef struct
{
	float x, y, z;
}Vec3D;

typedef struct
{
	float x, y, z, w;
}Vec4D;

typedef float Vec;
typedef Vec Vec2[2];
typedef Vec Vec3[3];
typedef Vec Vec4[4];

typedef struct
{
	Vec3 vmax, vmin;

}Vec3DCompare;

Vec2D vec2d(float x, float y);
Vec3D vec3d(float x, float y, float z);
Vec4D vec4d(float x, float y, float z, float w);

Vec2D vec2d(float x, float y);
Vec3D vec3d(float x, float y, float z);
Vec4D vec4d(float x, float y, float z, float w);

void AngleVectors(Vec3D angles, Vec3D* forward, Vec3D* right, Vec3D* up);


#define pi 3.14159265358979323846
#define vec2d_set(v, a, b)      (v.x=(a), v.y=(b))
#define vec3d_set(v, a, b, c)   (v.x=(a), v.y=(b), v.z=(c))
#define vec4d_set(v, a, b, c,d) (v.x=(a), v.y=(b), v.z=(c), v.w=(d))
#define Vec2d_set(v, a, b)      (v[0]=(a), v.[1]=(b))
#define Vec3d_set(v, a, b, c)   (v[0]=(a), v[1]=(b), v[2]=(c))
#define Vec4d_set(v, a, b, c,d) (v[0]=(a), v[1]=(b), v[2]=(c), v[3]=(d))

#define vec2d_negate(dst,src)      (dst.x = -src.x,dst.y = -src.y)
#define vec3d_negate(dst,src)      (dst.x = -src.x,dst.y = -src.y,dst.z = -src.z)
#define vec4d_negate(dst,src)      (dst.x = -src.x,dst.y = -src.y,dst.z = -src.z,dst.w = -src.w)
#define Vec2d_negate(dst,src)      (dst[0] = -src[0], dst[1] = -src[1])
#define Vec3d_negate(dst,src)      (dst[0] = -src[0], dst[1] = -src[1], dst[2] = -src[2])
#define Vec4d_negate(dst,src)      (dst[0] = -src[0], dst[1] = -src[1], dst[2] = -src[2], dst[3] = -src[3])

#define vec2d_cpy(dst,src)   (dst.x = src.x,dst.y = src.y)
#define vec3d_cpy(dst,src)   (dst.x = src.x,dst.y = src.y,dst.z = src.z)
#define vec4d_cpy(dst,src)   (dst.x = src.x,dst.y = src.y,dst.z = src.z,dst.w = src.w)
#define Vec2d_cpy(dst,src)   (dst[0] = src[0], dst[1] = src[1])
#define Vec3d_cpy(dst,src)   (dst[0] = src[0], dst[1] = src[1], dst[2] = src[2])
#define Vec4d_cpy(dst,src)   (dst[0] = src[0], dst[1] = src[1], dst[2] = src[2], dst[3] = src[3])

#define vec2d_add(dst,a,b)   (dst.x = a.x+b.x,dst.y = a.y+b.y)
#define vec3d_add(dst,a,b)   (dst.x = a.x+b.x,dst.y = a.y+b.y,dst.z = a.z+b.z)
#define vec4d_add(dst,a,b)   (dst.x = a.x+b.x,dst.y = a.y+b.y,dst.z = a.z+b.z,dst.w = a.w+b.w)
#define Vec2d_add(dst,a,b)   (dst[0] = a[0] + b[0], dst[1] = a[1] + b[1])
#define Vec3d_add(dst,a,b)   (dst[0] = a[0] + b[0], dst[1] = a[1] + b[1], dst[2] = a[2] + b[2])
#define Vec4d_add(dst,a,b)   (dst[0] = a[0] + b[0], dst[1] = a[1] + b[1], dst[2] = a[2] + b[2], dst[3] = a[3] + b[3])

#define vec2d_sub(dst,a,b)   (dst.x = a.x - b.x, dst.y = a.y - b.y)
#define vec3d_sub(dst,a,b)   (dst.x = a.x - b.x, dst.y = a.y - b.y, dst.z = a.z - b.z)
#define vec4d_sub(dst,a,b)   (dst.x = a.x - b.x, dst.y = a.y - b.y, dst.z = a.z - b.z, dst.w = a.w - b.w)

#define Vec2d_sub(dst,a,b)   (dst[0] = a[0] - b[0], dst[1] = a[1] - b[1])
#define Vec3d_sub(dst,a,b)   (dst[0] = a[0] - b[0], dst[1] = a[1] - b[1], dst[2] = a[2] - b[2])
#define Vec4d_sub(dst,a,b)   (dst[0] = a[0] - b[0], dst[1] = a[1] - b[1], dst[2] = a[2] - b[2], dst[3] = a[3] - b[3])

#define vec3d_scale(dst,src,scale) (dst.x = src.x * scale, dst.y = src.y * scale, dst.z = src.z * scale)
#define Vec3d_scale(dst,src,scale) (dst[0] = src[0] * scale, dst[1] = src[1] * scale, dst[2] = src[2] * scale)

#define vectorMA(a, scale, b, result) (result.x = a.x + scale * b.x, result.y = a.y + scale * b.y, result.z = a.z + scale * b.z)
#define VectorMA(a, scale, b, result) (result[0] = a[0] + scale * b[0], result[1] = a[1] + scale * b[1], result[2] = a[2] + scale * b[2])

#define vec_convert_Vec3D (dst, a) (dst.x = a[0], dst.y = a[1], dst.z = a[2])
#define vec_convert_Vec3 (dst, a) (dst[0] = a.x, dst[1] = a.y, dst[2] = a.z)

#define Vec3d_length(dst, a) (dst = sqrt(SQUARE(a[0]) + SQUARE(a[1]) + SQUARE(a[2])))
#define vec3d_length(dst, a) (dst = sqrt(SQUARE(a.x) + SQUARE(a.y) + SQUARE(a.z)))

#endif
