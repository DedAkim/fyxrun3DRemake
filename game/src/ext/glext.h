/*
	Use it ONLY if you want use OpenGL manually, without engine functions
	There is no guarantee that there will be no conflicts.
	Use at your own risk.

	Please, use #define GL_EXT before usage
*/

#ifdef GL_EXT

	#ifdef _WIN32
		#include <windows.h>
	#endif	

	#include <GL/glew.h>
	#include <stdio.h>

	// Init glew manually. Make OGL addrs great again  
	void glextInitGLEW();

#endif