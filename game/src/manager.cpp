#include "manager.hpp"

collision::collision(vec3 min, vec3 max)
{
    aabb.create(min, max);
    phys.position = max - min;
}

collision::collision(ObjModel &model)
{
    aabb.createFromObject(&model);
    phys.position = position;
    phys.old_position = position;
    phys.velocity = {0.0f, 0.0f, 0.0f};
    phys.collision = aabb;
}

void collision::transform_collision()
{
    phys.old_position = phys.position;
    phys.position = position;
    phys.collision = aabb;
    phys.collision.translate(position);
}

void shader::color(vec3 colors, vec3 ambient, int num_lights, OpenGLShader shader)
{
	shader.setVec3("color", colors);
	shader.setVec3("ambient_light", ambient);
	shader.setInt("num_lights", num_lights);
}

void shader::light(vec3 pos, vec3 rgb, const int index, OpenGLShader shader)
{
    //shader.setVec3("light_color[" + (char)(index) + (char)("]"), rgb);
	//shader.setVec3("light_position[" + (char)(index) + (char)("]"), pos);
}

camera::camera(vec3 pos, OpenGLShader shader)
{
	mainCamera.setPosition(pos);
	mainCamera.setShader(&shader);
}

void camera::transform_camera(vec3 pos, vec3 point)
{
    mainCamera.calculateMatrix();
	mainCamera.flush();
	mainCamera.setPosition(pos);
	mainCamera.setPoint(point);
}


