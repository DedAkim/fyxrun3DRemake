/*
	legacy bridge, compatibility layer, transitional wrapper, idk

	временная мера (или нет)
*/

#pragma once
#include "../defext.h"
#include "../transform/transform.hpp"

#include <GL/glew.h>
#include <iostream>
#include <vector>

/* Это прям реально мера временная, я скоро перепишу */
extern "C"
{
	#include "legacy/vecext.h"
	#include "legacy/obj_loader.h"
}

/* ДА БЛЯТЬ Я ПЕРЕПИШУ ЧЕСТНО */
class ObjModel
{
	obj_model objmodel;
	obj_mesh mesh;

	GLBuffers buffer;
public:
	ENGINE_API ObjModel(const std::string path);

	ENGINE_API GLBuffers getBuffers();

	ENGINE_API int getNativeIndexCount();
	ENGINE_API int getNativeTempIndexCount();
	ENGINE_API vec3 getNativeTempPosition(int index);
	ENGINE_API obj_mesh getNativeMesh();

};