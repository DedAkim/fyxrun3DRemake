#include "glext.h"

#ifdef GL_EXT

	void glextInitGLEW()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			#ifdef _WIN32

				MessageBox(NULL, L"GLEW init failed", L"Fatal error", MB_ICONERROR | MB_OK);
			#else
				printf("Glew init from GL_EXT failed.\n");
			#endif

			return;
		}
		else
		{
			printf("Using GL_EXT now.\n");
		}
	}
	
#endif