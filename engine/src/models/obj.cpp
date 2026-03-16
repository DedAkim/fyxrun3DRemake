#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "obj.hpp"

ENGINE_API ObjModel::ObjModel(const std::string path)
{
	if(!objPrepareModel(&objmodel))
	{
		std::cerr << "Cant prepare " << path << std::endl;
	}

	if(!objLoad(&objmodel, path.c_str()))
	{
		std::cerr << "Cant load " << path << std::endl;
	}

	mesh = objCreateMesh(&objmodel);

	//objFree(&objmodel);

	buffer.VAO = mesh.VAO;
	buffer.VBO = mesh.VBO;
	buffer.EBO = mesh.EBO;
	buffer.indexCount = mesh.index_count;
}

ENGINE_API GLBuffers ObjModel::getBuffers()
{
	return buffer;
}

ENGINE_API int ObjModel::getNativeIndexCount()
{
	return mesh.index_count;
}

ENGINE_API int ObjModel::getNativeTempIndexCount()
{
	return objmodel.temp_position_count;
}

ENGINE_API vec3 ObjModel::getNativeTempPosition(int index)
{
	vec3 fv3;
	
	fv3.x = objmodel.temp_positions[index].x;
	fv3.y = objmodel.temp_positions[index].y;
	fv3.z = objmodel.temp_positions[index].z;

	return fv3;
}

ENGINE_API obj_mesh ObjModel::getNativeMesh()
{
	return mesh;
}
