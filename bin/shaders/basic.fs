#version 330 core

out vec4 FragColor;
// in vec2 texture_coords;
// in vec3 fnormal;

uniform sampler2D t;

void main()
{
    FragColor = vec4(1, 1, 1, 1);
}