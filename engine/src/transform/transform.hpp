#pragma once
#include "../defext.h"

#include "vector.hpp"
#include "matrix.hpp"
#include "trygonometry.hpp"
#include "operations.hpp"

/*
	Really stupid thing.
	I just tired to see mat4 everywhere :(
*/
class Transform
{
	vec3 position = {0, 0, 0};
	float angle = 0.0f;
	vec3 axis = {0, 1, 0};
	vec3 scaleFactor = {1, 1, 1};

public:
	// Set position
	ENGINE_API void translateTo(const vec3 pos);
	
	// Set rotation
	ENGINE_API void rotateTo(const float deg, const vec3 rotAxis);

	// Set scale
	ENGINE_API void scaleTo(const vec3 scale);

	// Return mat4 model (default usage: setMat4 uModel in your shader uniform)
	ENGINE_API mat4 getModel();
};