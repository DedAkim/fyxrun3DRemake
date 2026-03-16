/*
    SORRY
    I'M SO LAZY

    obj_loader - старая реализация на Си
*/

#pragma once
#include "../../defext.h"
#include "vecext.h"

#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	pv3 position;
	pv3 normal;
	pv2 texcoord;
} obj_vertex;

typedef struct
{
	int vertex;
	int texcoord;
	int normal;
} obj_index;

typedef struct
{
	GLuint VAO, VBO, EBO;
	int index_count;
} obj_mesh;

typedef struct
{
	obj_vertex *vertices;
	GLuint *indices;

	int vertex_count;
	int index_count;

	pv3 *temp_positions;
	pv3 *temp_normals;
	pv2 *temp_texcoords;
	obj_index *temp_indices;

	int temp_position_count;
	int temp_normal_count;
	int temp_texcoord_count;
	int temp_index_count;
} obj_model;

ENGINE_API int objPrepareModel(obj_model *model);

ENGINE_API void objFree(obj_model *model);

ENGINE_API int objParseVertexIndex(const char *token);

ENGINE_API void objParseFaceVertex(const char *vertex_str, obj_index *index);

ENGINE_API int objAddTempPosition(obj_model *model, float x, float y, float z);

ENGINE_API int objAddTempTexcoord(obj_model *model, float u, float v);

ENGINE_API int objAddTempNormal(obj_model *model, float x, float y, float z);

ENGINE_API int objAddTempIndex(obj_model *model, obj_index index);

ENGINE_API void objCalculateNormals(obj_model *model);

ENGINE_API int objBuildModel(obj_model *model);

ENGINE_API int objLoad(obj_model *model, const char *filename);

ENGINE_API obj_mesh objCreateMesh(obj_model *model);

ENGINE_API void objMeshFree(obj_mesh *mesh);

ENGINE_API int objGetNativeTIC(obj_model* model);