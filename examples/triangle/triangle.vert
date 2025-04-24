#version 330 core

layout (location = 0) in vec2 in_points;
layout (location = 1) in vec3 in_colors;

out vec3 vertice_colors;

void main()
{
    vertice_colors = in_colors;
    gl_Position = vec4(in_points, 1.0f, 1.0f);
}
