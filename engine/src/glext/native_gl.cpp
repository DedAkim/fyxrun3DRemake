#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "native_gl.hpp"

ENGINE_API GLTexture::GLTexture()
{
	// Nothing...
}

ENGINE_API GLTexture::GLTexture(const char *path)
{
	loadFromFile(path);
}

ENGINE_API void GLTexture::loadFromFile(const char *path)
{
	image = GLEXT_LOAD_IMAGE(path);
}

ENGINE_API void GLTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D, image.id);
}

ENGINE_API void GLImmediateRender::drawElements(GLBuffers buffers, GLint indexCount)
{
	glBindVertexArray(buffers.VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

ENGINE_API void GLImmediateRender::drawArrays(GLBuffers buffers, GLenum mode, GLint first, GLint indexCount)
{
	glBindVertexArray(buffers.VAO);
	glDrawArrays(mode, first, indexCount);
}

ENGINE_API void GLManualBuffers::generateVAO()
{
	glGenVertexArrays(1, &buffers.VAO);
	glBindVertexArray(buffers.VAO);
}

ENGINE_API void GLManualBuffers::generateVBO(GLfloat *vertices, GLint size, GLint v_in_array)
{
	glGenBuffers(1, &buffers.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, buffers.VBO);

	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, v_in_array * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
}

ENGINE_API void GLManualBuffers::generateEBO(GLint *indices, GLint size)
{
	glGenBuffers(1, &buffers.EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

ENGINE_API void GLManualBuffers::generateTextureAttribs(GLint v_in_array)
{
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, v_in_array * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

ENGINE_API GLBuffers GLManualBuffers::getNativeBuffers()
{
	return buffers;
}
