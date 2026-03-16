#pragma once
#include "../defext.h"

#include "../transform/vector.hpp"
#include "../transform/operations.hpp"

#include "../models/obj.hpp"

#include <cfloat>

class AabbCollision
{
	vec3 min;
	vec3 max;
public:
	// A - min | B - max
	ENGINE_API void create(const vec3 a, const vec3 b);
	ENGINE_API void createFromCenter(const vec3 center, const vec3 size);
	ENGINE_API void createFromObject(ObjModel* model);

	ENGINE_API void translate(vec3 xyz);
	ENGINE_API void setScale(vec3 xyz);

	ENGINE_API vec3 getCenter();
	ENGINE_API vec3 getSize();
	ENGINE_API vec3 getMin();
	ENGINE_API vec3 getMax();

	// debug
	ENGINE_API bool isValid();
};

struct PhysObject
{
	vec3 position;
	vec3 old_position;

	AabbCollision collision;

	vec3 velocity;
};

namespace Collider
{
	ENGINE_API bool intersects(AabbCollision& a, AabbCollision& b);
	ENGINE_API vec3 resolveWithSliding(PhysObject& obj, AabbCollision& obstacle);
};