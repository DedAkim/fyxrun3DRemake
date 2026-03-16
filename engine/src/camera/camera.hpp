#pragma once
#include "../defext.h"

#include "../transform/matrix.hpp"
#include "../transform/operations.hpp"

#include "../shaders/ogl_shader.hpp"

#include <string>

class Camera3D
{
	mat4 viewMatrix;
	mat4 projectionMatrix;

	float fov = 90.0f;
	vec3 position = {0.f, 0.f, 0.f};
	vec3 point = {0.f, 0.f, 0.f};

	vec2 windowResolution = {1280.0f, 720.0f};

	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	std::string viewUniformName = "uView";
	std::string projectionUniformName = "uProjection";

	OpenGLShader *shader;

public:
	ENGINE_API void setShader(OpenGLShader* s);

	ENGINE_API void setFov(const float f);
	ENGINE_API void setPosition(const vec3 physPosition);
	ENGINE_API void setPoint(const vec3 lookPosition);

	ENGINE_API void setWindowResolution(const vec2 wr);

	ENGINE_API void setNear(const float newNear);
	ENGINE_API void setFar(const float newFar);

	ENGINE_API void setViewUniform(const std::string uniform);
	ENGINE_API void setProjectionUniform(const std::string uniform);

	ENGINE_API void calculateMatrix();
	ENGINE_API void flush();
};