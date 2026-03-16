#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "vecext.h"

ENGINE_API pv3 pgmNormalizeVec3(pv3 v)
{
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	if (length == 0.0f)
		return (pv3){
		    .x = 0,
		    .y = 0,
		    .z = 0};

	return (pv3){
	    .x = v.x / length,
	    .y = v.y / length,
	    .z = v.z / length};
}

ENGINE_API pv3 pgmScaleVec3(pv3 v, float s)
{
	return (pv3){
	    .x = v.x * s,
	    .y = v.y * s,
	    .z = v.z * s};
}

ENGINE_API pv3 pgmSubVec3(pv3 a, pv3 b)
{
	return (pv3){
	    .x = a.x - b.x,
	    .y = a.y - b.y,
	    .z = a.z - b.z};
}

ENGINE_API pv3 pgmAddVec3(pv3 a, pv3 b)
{
	return (pv3){
	    .x = a.x + b.x,
	    .y = a.y + b.y,
	    .z = a.z + b.z};
}

ENGINE_API pv3 pgmCrossVec3(pv3 a, pv3 b)
{
	return (pv3){
	    .x = a.y * b.z - a.z * b.y,
	    .y = a.z * b.x - a.x * b.z,
	    .z = a.x * b.y - a.y * b.x};
}

ENGINE_API float pgmDotVec3(pv3 a, pv3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}