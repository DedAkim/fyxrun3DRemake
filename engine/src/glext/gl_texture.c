#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "gl_texture.h"

ENGINE_API GL_IMAGE GLEXT_LOAD_IMAGE(const char *path)
{
	GLuint texture_id;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	int width, height, channels;
	unsigned char *data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);

	if (!data)
	{
		return (GL_IMAGE){
		    .id = 0};
	}

	glTexImage2D(
	    	GL_TEXTURE_2D,
	    	0,
	    	GL_RGBA,
	    	width, height,
	    	0,
	    	GL_RGBA,
	    	GL_UNSIGNED_BYTE,
	    	data
	);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return (GL_IMAGE)
	{
		.id = texture_id
	};
}