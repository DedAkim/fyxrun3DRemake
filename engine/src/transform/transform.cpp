#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "transform.hpp"

ENGINE_API void Transform::translateTo(const vec3 pos)
{
	position = pos;
}

ENGINE_API void Transform::rotateTo(const float deg, const vec3 rotAxis)
{
	angle = deg;

	axis.x = rotAxis.x;
	axis.y = rotAxis.y;
	axis.z = rotAxis.z;
}

ENGINE_API void Transform::scaleTo(const vec3 scale)
{
	scaleFactor.x = scale.x;
	scaleFactor.y = scale.y;
	scaleFactor.z = scale.z;
}

ENGINE_API mat4 Transform::getModel()
{
	mat4 model = Math::identity();

	model = Math::translate(model, position);
	model = Math::rotate(model, angle, axis);
	model = Math::scale(model, scaleFactor);

	return model;
}