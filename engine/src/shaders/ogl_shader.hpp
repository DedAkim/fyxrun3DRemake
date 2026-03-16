#pragma once
#include "../defext.h"

#include <GL/glew.h>

#include <fstream>
#include <string>
#include <iostream>

#include "../transform/transform.hpp"

/*
	GLSL shader build and run class :3

	Works with OpenGL, use OpenGL, and prints logs into console (std::cout).
*/
class OpenGLShader
{
	GLuint program;
	std::string vertex_path;
	std::string fragment_path;

	std::string _getSourceFromFile(const std::string file);
public:
	// Creating and build shaders from files.
	ENGINE_API OpenGLShader(std::string v_path, std::string f_path);
	ENGINE_API ~OpenGLShader();

	// Bind your shaders
	ENGINE_API void bind();

	// Send your int value to uniform in shader (uniform int some_value, for example)
	ENGINE_API void setInt(const char* uniform, GLint value);
	// Send your float value to uniform in shader (uniform float some_value, for example)
	ENGINE_API void setFloat(const char* uniform, GLfloat value);

	/* TODO Math pls :D (it doesnt exists rn) */

	ENGINE_API void setVec3(const char* uniform, vec3 value);
	ENGINE_API void setVec4(const char* uniform, vec4 value);
	ENGINE_API void setMat4(const char* uniform, mat4 value);

	// Returns GLuint program
	ENGINE_API GLuint getProgram();
};