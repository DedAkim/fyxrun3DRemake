#pragma once
#include "../defext.h"

#include "vector.hpp"
#include "matrix.hpp"
#include "trygonometry.hpp"

#include <math.h>

namespace Math
{
	/* Vector */
	ENGINE_API vec3 normalize(const vec3& v);
	ENGINE_API vec3 cross(const vec3& a, const vec3& b);

	ENGINE_API float dot(const vec3 &a, const vec3 &b);
	ENGINE_API float lenght(const vec3 &v);

	/* Matrix */

	ENGINE_API mat4 identity();

	ENGINE_API mat4 perspective(float fov, float aspect, float near, float far);

	ENGINE_API mat4 translate(const mat4 m, float x, float y, float z);
	ENGINE_API mat4 translate(const mat4 m, vec3 position);
	ENGINE_API mat4 rotate(const mat4 matrix, float angle, const vec3 axis);
	ENGINE_API mat4 scale(const mat4 m, const vec3 &scaleFactors);

	ENGINE_API mat4 lookAt(const vec3 &eye, const vec3 &center, const vec3 &up);
	ENGINE_API mat4 ortho(float left, float right, float bottom, float top, float near, float far);
};