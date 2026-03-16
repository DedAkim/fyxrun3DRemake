#pragma once

/* DLL and SO defines */

#ifdef _WIN32
    #if defined(ENGINE_CORE_EXPORTS) || defined(ENGINE_API_EXPORTS)
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#else
    #define ENGINE_API __attribute__((visibility("default")))
#endif

/* Utils Defines and Structures */

#include <stdint.h>

typedef struct 
{
    uint8_t r; 
    uint8_t g;
    uint8_t b;
} RGB8;

/* OpenGL Buffers */

#define OGL_M_BUFFERS GLBuffers;

typedef struct 
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    int indexCount;
} OGL_M_BUFFERS;