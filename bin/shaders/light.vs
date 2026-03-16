#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture_coordinates;

out vec2 texture_coords;
out vec3 normals;
out vec3 frag_position;

uniform mat4 uProjection;
uniform mat4 uModel;
uniform mat4 uView;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(position.x, position.y, position.z, 1.0);

    texture_coords.x = texture_coordinates.x;
    texture_coords.y = 1.0 - texture_coordinates.y;

    frag_position = vec3(uModel * vec4(position, 1.0));

    mat3 normal_matrix = transpose(inverse(mat3(uModel)));
    normals = normalize(normal_matrix * normal);
}