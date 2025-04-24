#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec3 color;
uniform float scale;

out vec3 pointColor;

void main()
{
    pointColor = color;
    gl_Position = vec4(point * scale, 1.0f, 1.0f);
}
