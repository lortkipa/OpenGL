#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec2 in_textureCoord;

uniform float scale;

out vec2 textureCoord;

void main()
{
    textureCoord = in_textureCoord;
    gl_Position = vec4(point * scale, 0.0f, 1.0f);
}
