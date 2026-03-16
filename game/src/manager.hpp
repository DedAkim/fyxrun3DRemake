#include <glext/native_gl.hpp>
#include <winmgr.hpp>
#include <shaders/ogl_shader.hpp>
#include <transform/transform.hpp>
#include <models/obj.hpp>
#include <camera/camera.hpp>
#include <physics/collider.hpp>
#include "controls.hpp"

#include <ctime>


class collision
{
    vec3 position;
    AabbCollision aabb;
    PhysObject phys;

public:

    collision(vec3 min, vec3 max);
    collision(ObjModel &model);
    void transform_collision();
};

class shader
{
public:
    void color(vec3 colors, vec3 ambient, int num_lights, OpenGLShader shader);
    void light(vec3 pos, vec3 rgb, const int index, OpenGLShader shader);
};

class camera
{
	Camera3D mainCamera;
public:
    camera(vec3 pos, OpenGLShader shader);
    void transform_camera(vec3 pos, vec3 point);
};

class transforms
{
    Transform transform;
public:
    transforms(vec3 phys_pos);
};