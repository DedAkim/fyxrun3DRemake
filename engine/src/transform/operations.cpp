#ifdef _WIN32
#define ENGINE_API_EXPORTS
#endif

#include "operations.hpp"
#include <cstring>

ENGINE_API vec3 Math::normalize(const vec3 &v)
{
	float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	if (len > 0.0001f)
		return {v.x / len, v.y / len, v.z / len};

	return {0.0f, 0.0f, 1.0f};
}

ENGINE_API vec3 Math::cross(const vec3 &a, const vec3 &b)
{
	return {
	    a.y * b.z - a.z * b.y,
	    a.z * b.x - a.x * b.z,
	    a.x * b.y - a.y * b.x};
}

ENGINE_API float Math::dot(const vec3 &a, const vec3 &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

ENGINE_API float Math::lenght(const vec3 &v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

ENGINE_API mat4 Math::identity()
{
	mat4 result;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result.m[i][j] = (i == j) ? 1.0f : 0.0f;

	return result;
}

ENGINE_API mat4 Math::perspective(float fov, float aspect, float near, float far)
{
	mat4 result = {0};
	float tanHalfFov = tanf(fov / 2.0f);

	result.m[0][0] = 1.0f / (aspect * tanHalfFov);
	result.m[1][1] = 1.0f / tanHalfFov;
	result.m[2][2] = (far + near) / (near - far);
	result.m[2][3] = (2.0f * far * near) / (near - far);
	result.m[3][2] = -1.0f;

	return result;
}

ENGINE_API mat4 Math::translate(const mat4 m, float x, float y, float z)
{
	mat4 result = m;

	result.m[0][3] += x;
	result.m[1][3] += y;
	result.m[2][3] += z;

	return result;
}

ENGINE_API mat4 Math::translate(const mat4 m, vec3 position)
{
	return Math::translate(m, position.x, position.y, position.z);
}

ENGINE_API mat4 Math::rotate(const mat4 matrix, float angle, const vec3 axis)
{
	vec3 norm_axis = normalize(axis);

	float cos_angle = cosf(angle);
	float sin_angle = sinf(angle);
	float t = 1.0f - cos_angle;

	mat4 rotation = {{{t * norm_axis.x * norm_axis.x + cos_angle, t * norm_axis.x * norm_axis.y - sin_angle * norm_axis.z, t * norm_axis.x * norm_axis.z + sin_angle * norm_axis.y, 0.0f},
			  {t * norm_axis.x * norm_axis.y + sin_angle * norm_axis.z, t * norm_axis.y * norm_axis.y + cos_angle, t * norm_axis.y * norm_axis.z - sin_angle * norm_axis.x, 0.0f},
			  {t * norm_axis.x * norm_axis.z - sin_angle * norm_axis.y, t * norm_axis.y * norm_axis.z + sin_angle * norm_axis.x, t * norm_axis.z * norm_axis.z + cos_angle, 0.0f},
			  {0.0f, 0.0f, 0.0f, 1.0f}}};

	mat4 result = {0};

	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			for (int i = 0; i < 4; i++)
				result.m[row][col] += matrix.m[row][i] * rotation.m[i][col];

	return result;
}

ENGINE_API mat4 Math::scale(const mat4 m, const vec3 &scaleFactors)
{
	mat4 scaleMatrix = identity();

	scaleMatrix.m[0][0] = scaleFactors.x;
	scaleMatrix.m[1][1] = scaleFactors.y;
	scaleMatrix.m[2][2] = scaleFactors.z;

	mat4 result = {0};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += m.m[i][k] * scaleMatrix.m[k][j];
			}
		}
	}

	return result;
}

ENGINE_API mat4 Math::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	vec3 forward = normalize(center - eye);
	vec3 right = normalize(cross(forward, up));
	vec3 top = cross(right, forward);

	mat4 result = identity();

	result.m[0][0] = right.x;
	result.m[0][1] = right.y;
	result.m[0][2] = right.z;

	result.m[1][0] = top.x;
	result.m[1][1] = top.y;
	result.m[1][2] = top.z;

	result.m[2][0] = -forward.x;
	result.m[2][1] = -forward.y;
	result.m[2][2] = -forward.z;

	result.m[0][3] = -dot(right, eye);
	result.m[1][3] = -dot(top, eye);
	result.m[2][3] = dot(forward, eye);

	return result;
}

ENGINE_API mat4 Math::ortho(float left, float right, float bottom, float top, float near, float far)
{
	mat4 result = {0};

	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = -2.0f / (far - near);

	result.m[0][3] = -(right + left) / (right - left);
	result.m[1][3] = -(top + bottom) / (top - bottom);
	result.m[2][3] = -(far + near) / (far - near);
	result.m[3][3] = 1.0f;

	return result;
}
