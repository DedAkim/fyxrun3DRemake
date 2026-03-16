#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "camera.hpp"

ENGINE_API void Camera3D::setShader(OpenGLShader *s)
{
	shader = s;
}

ENGINE_API void Camera3D::setFov(const float f)
{
	fov = f;
}

ENGINE_API void Camera3D::setPosition(const vec3 physPosition)
{
	position.x = physPosition.x;
	position.y = physPosition.y;
	position.z = physPosition.z;
}

ENGINE_API void Camera3D::setPoint(const vec3 lookPosition)
{
	point.x = lookPosition.x;
	point.y = lookPosition.y;
	point.z = lookPosition.z;
}

ENGINE_API void Camera3D::setWindowResolution(const vec2 wr)
{
	windowResolution.x = wr.x;
	windowResolution.y = wr.y;
}

ENGINE_API void Camera3D::setNear(const float newNear)
{
	nearPlane = newNear;
}

ENGINE_API void Camera3D::setFar(const float newFar)
{
	farPlane = newFar;
}

ENGINE_API void Camera3D::setViewUniform(const std::string uniform)
{
	viewUniformName = uniform;
}

ENGINE_API void Camera3D::setProjectionUniform(const std::string uniform)
{
	projectionUniformName = uniform;
}


ENGINE_API void Camera3D::calculateMatrix()
{
	viewMatrix = Math::lookAt(
		position,
		point,
		{0.0f, 1.0f, 0.0f}
	);

	projectionMatrix = Math::perspective(
		fov,
		windowResolution.x / windowResolution.y,
		nearPlane,
		farPlane
	);
}

ENGINE_API void Camera3D::flush()
{
	shader->setMat4(viewUniformName.c_str(), viewMatrix);
	shader->setMat4(projectionUniformName.c_str(), projectionMatrix);
	shader->setVec3("view_position", position);
}
