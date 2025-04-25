#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec2 in_texCoords;

out vec2 texCoords;

void main()
{
    texCoords = in_texCoords;
    gl_Position = vec4(point, 0.0f, 1.0f);
}
