#pragma once
#include "../defext.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>

typedef struct 
{
	GLuint id;
} GL_IMAGE;

ENGINE_API GL_IMAGE GLEXT_LOAD_IMAGE(const char* path);