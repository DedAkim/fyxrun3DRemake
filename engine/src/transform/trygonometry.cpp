#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "trygonometry.hpp"

ENGINE_API float Trygonometry::radians(float degrees)
{
	return degrees * (PI / 180.0f);
}

ENGINE_API float Trygonometry::degrees(float radians)
{
	return radians * (180.0f / PI);
}

ENGINE_API float Trygonometry::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}