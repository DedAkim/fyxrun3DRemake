#pragma once

extern "C"
{
	#include "../defext.h"
	#include "glext.h"
	#include "gl_texture.h"
}

class GLTexture
{
	GL_IMAGE image;

public:
	ENGINE_API GLTexture();
	ENGINE_API GLTexture(const char* path);

	ENGINE_API void loadFromFile(const char* path);

	ENGINE_API void bind();
};

class GLManualBuffers
{
	GLBuffers buffers;

public:
	ENGINE_API void generateVAO();
	ENGINE_API void generateVBO(GLfloat *vertices, GLint size, GLint v_in_array);
	ENGINE_API void generateEBO(GLint *indices, GLint size);
	
	ENGINE_API void generateTextureAttribs(GLint v_in_array);

	ENGINE_API GLBuffers getNativeBuffers();
};

namespace GLImmediateRender
{
	ENGINE_API void drawElements(GLBuffers buffers, GLint indexCount);
	ENGINE_API void drawArrays(GLBuffers buffers, GLenum mode, GLint first, GLint indexCount);
};