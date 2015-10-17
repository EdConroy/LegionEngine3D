#include "entity.h"

typedef struct Trace_T
{
	Cube a;
	lbool allsolid;	// if true, plane is not valid
	lbool startsolid;	// if true, the initial point was in a solid area
	float fraction;	
	Vec3D endpos;		
	entity* hitinfo;
	int	contents;
}Trace;

