#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "glext.h"

ENGINE_API void defextDevTestDrawEBO(GLBuffers buffers)
{
	glBindVertexArray(buffers.VAO);
	glDrawElements(GL_TRIANGLES, buffers.indexCount, GL_UNSIGNED_INT, 0);
}
