#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "obj_loader.h"

// temp_position_count

ENGINE_API int objPrepareModel(obj_model *model)
{
	memset(model, 0, sizeof(obj_model));
	return 1;
}

ENGINE_API void objFree(obj_model *model)
{
	if (model->vertices)
		free(model->vertices);

	if (model->indices)
		free(model->indices);

	if (model->temp_positions)
		free(model->temp_positions);

	if (model->temp_normals)
		free(model->temp_normals);

	if (model->temp_texcoords)
		free(model->temp_texcoords);

	if (model->temp_indices)
		free(model->temp_indices);

	memset(model, 0, sizeof(obj_model));
}

ENGINE_API int objParseVertexIndex(const char *token)
{
	if (token == NULL)
		return -1;

	return atoi(token) - 1;
}

ENGINE_API void objParseFaceVertex(const char *vertex_str, obj_index *index)
{
	char buffer[256];

	strncpy(buffer, vertex_str, sizeof(buffer) - 1);
	buffer[sizeof(buffer) - 1] = '\0';

	index->vertex = -1;
	index->texcoord = -1;
	index->normal = -1;

	char *parts[3] = {NULL, NULL, NULL};
	int part_count = 0;

	char *token = strtok(buffer, "/");

	while (token != NULL && part_count < 3)
	{
		parts[part_count++] = token;
		token = strtok(NULL, "/");
	}

	if (part_count >= 1)
		index->vertex = objParseVertexIndex(parts[0]);

	if (part_count >= 2 && strlen(parts[1]) > 0)
		index->texcoord = objParseVertexIndex(parts[1]);

	if (part_count >= 3)
		index->normal = objParseVertexIndex(parts[2]);
}

ENGINE_API int objAddTempPosition(obj_model *model, float x, float y, float z)
{
	model->temp_positions = realloc(model->temp_positions, sizeof(pv3) * (model->temp_position_count + 1));
	model->temp_positions[model->temp_position_count] = (pv3){x, y, z};


	return model->temp_position_count++;
}

ENGINE_API int objAddTempTexcoord(obj_model *model, float u, float v)
{
	model->temp_texcoords = realloc(model->temp_texcoords, sizeof(pv2) * (model->temp_texcoord_count + 1));
	model->temp_texcoords[model->temp_texcoord_count] = (pv2){u, v};

	return model->temp_texcoord_count++;
}

ENGINE_API int objAddTempNormal(obj_model *model, float x, float y, float z)
{
	model->temp_normals = realloc(model->temp_normals, sizeof(pv3) * (model->temp_normal_count + 1));
	model->temp_normals[model->temp_normal_count] = (pv3){x, y, z};

	return model->temp_normal_count++;
}

ENGINE_API int objAddTempIndex(obj_model *model, obj_index index)
{
	model->temp_indices = realloc(model->temp_indices, sizeof(obj_index) * (model->temp_index_count + 1));
	model->temp_indices[model->temp_index_count] = index;

	return model->temp_index_count++;
}

ENGINE_API void objCalculateNormals(obj_model *model)
{
	for (int i = 0; i < model->vertex_count; i++)
	{
		model->vertices[i].normal = (pv3){0, 0, 0};
	}

	for (int i = 0; i < model->index_count; i += 3)
	{
		unsigned int i1 = model->indices[i];
		unsigned int i2 = model->indices[i + 1];
		unsigned int i3 = model->indices[i + 2];

		obj_vertex *v1 = &model->vertices[i1];
		obj_vertex *v2 = &model->vertices[i2];
		obj_vertex *v3 = &model->vertices[i3];

		pv3 edge1 = pgmSubVec3(v2->position, v1->position);
		pv3 edge2 = pgmSubVec3(v3->position, v1->position);
		pv3 normal = pgmCrossVec3(edge1, edge2);

		normal = pgmNormalizeVec3(normal);

		v1->normal.x += normal.x;
		v1->normal.y += normal.y;
		v1->normal.z += normal.z;

		v2->normal.x += normal.x;
		v2->normal.y += normal.y;
		v2->normal.z += normal.z;

		v3->normal.x += normal.x;
		v3->normal.y += normal.y;
		v3->normal.z += normal.z;
	}

	for (int i = 0; i < model->vertex_count; i++)
	{
		model->vertices[i].normal = pgmNormalizeVec3(model->vertices[i].normal);
	}
}

ENGINE_API int objBuildModel(obj_model *model)
{
	model->vertices = malloc(sizeof(obj_vertex) * model->temp_index_count);
	model->indices = malloc(sizeof(unsigned int) * model->temp_index_count);

	model->vertex_count = 0;
	model->index_count = model->temp_index_count;

	for (int i = 0; i < model->temp_index_count; i++)
	{
		obj_index obj_index = model->temp_indices[i];
		obj_vertex vertex;

		if (obj_index.vertex >= 0 && obj_index.vertex < model->temp_position_count)
		{
			vertex.position = model->temp_positions[obj_index.vertex];
		}
		else
		{
			vertex.position = (pv3){0, 0, 0};
		}

		if (obj_index.texcoord >= 0 && obj_index.texcoord < model->temp_texcoord_count)
		{
			vertex.texcoord = model->temp_texcoords[obj_index.texcoord];
		}
		else
		{
			vertex.texcoord = (pv2){0, 0};
		}

		if (obj_index.normal >= 0 && obj_index.normal < model->temp_normal_count)
		{
			vertex.normal = model->temp_normals[obj_index.normal];
		}
		else
		{
			vertex.normal = (pv3){0, 0, 0};
		}

		int existing_index = -1;
		for (int j = 0; j < model->vertex_count; j++)
		{
			if (memcmp(&model->vertices[j], &vertex, sizeof(obj_vertex)) == 0)
			{
				existing_index = j;
				break;
			}
		}

		if (existing_index >= 0)
		{
			model->indices[i] = existing_index;
		}
		else
		{
			model->vertices[model->vertex_count] = vertex;
			model->indices[i] = model->vertex_count;
			model->vertex_count++;
		}
	}

	model->vertices = realloc(model->vertices, sizeof(obj_vertex) * model->vertex_count);
	model->indices = realloc(model->indices, sizeof(unsigned int) * model->index_count);

	int has_normals = 0;

	for (int i = 0; i < model->vertex_count; i++)
	{
		if (fabs(model->vertices[i].normal.x) > 0.001f ||
		    fabs(model->vertices[i].normal.y) > 0.001f ||
		    fabs(model->vertices[i].normal.z) > 0.001f)
		{
			has_normals = 1;
			break;
		}
	}

	if (!has_normals)
	{
		objCalculateNormals(model);
	}

	// printf("Loaded model: %d vertices, %d indices\n", model->vertex_count, model->index_count);

	return 1;
}

ENGINE_API int objLoad(obj_model *model, const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		printf("Error:  %s\n", filename);
		return 0;
	}

	char line[1024];
	int line_number = 0;

	while (fgets(line, sizeof(line), file))
	{
		line_number++;

		if (line[0] == '#' || line[0] == '\n')
			continue;

		char command[32];
		if (sscanf(line, "%31s", command) != 1)
			continue;

		if (strcmp(command, "v") == 0)
		{
			float x, y, z;

			if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3)
			{
				objAddTempPosition(model, x, y, z);
			}
		}

		else if (strcmp(command, "vt") == 0)
		{
			float u, v;

			if (sscanf(line, "vt %f %f", &u, &v) == 2)
			{
				objAddTempTexcoord(model, u, v);
			}
		}

		else if (strcmp(command, "vn") == 0)
		{
			float x, y, z;
			if (sscanf(line, "vn %f %f %f", &x, &y, &z) == 3)
			{
				objAddTempNormal(model, x, y, z);
			}
		}

		else if (strcmp(command, "f") == 0)
		{
			char vertex1[64], vertex2[64], vertex3[64], vertex4[64];
			int vertex_count = sscanf(line, "f %63s %63s %63s %63s", vertex1, vertex2, vertex3, vertex4);

			if (vertex_count >= 3)
			{
				obj_index indices[4];

				objParseFaceVertex(vertex1, &indices[0]);
				objParseFaceVertex(vertex2, &indices[1]);
				objParseFaceVertex(vertex3, &indices[2]);

				objAddTempIndex(model, indices[0]);
				objAddTempIndex(model, indices[1]);
				objAddTempIndex(model, indices[2]);

				if (vertex_count == 4)
				{
					objParseFaceVertex(vertex4, &indices[3]);
					objAddTempIndex(model, indices[0]);
					objAddTempIndex(model, indices[2]);
					objAddTempIndex(model, indices[3]);
				}
			}
		}
	}

	fclose(file);

	return objBuildModel(model);
}

ENGINE_API obj_mesh objCreateMesh(obj_model *model)
{
	// Мне было пиздец лень использовать pgl

	obj_mesh mesh = {0};

	glGenVertexArrays(1, &mesh.VAO);
	glGenBuffers(1, &mesh.VBO);
	glGenBuffers(1, &mesh.EBO);

	glBindVertexArray(mesh.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, model->vertex_count * sizeof(obj_vertex), model->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->index_count * sizeof(unsigned int), model->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(obj_vertex), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(obj_vertex), (void *)offsetof(obj_vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(obj_vertex), (void *)offsetof(obj_vertex, texcoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	mesh.index_count = model->index_count;

	return mesh;
}

ENGINE_API void objMeshFree(obj_mesh *mesh)
{
	glDeleteVertexArrays(1, &mesh->VAO);
	glDeleteBuffers(1, &mesh->VBO);
	glDeleteBuffers(1, &mesh->EBO);

	memset(mesh, 0, sizeof(obj_mesh));
}

ENGINE_API int objGetNativeTIC(obj_model *model)
{
	return model->temp_index_count;
}
