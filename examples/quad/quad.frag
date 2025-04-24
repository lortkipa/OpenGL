#version 330 core

out vec4 finalColor;

in vec3 pointColor;

void main(void)
{
    finalColor = vec4(pointColor, 1.0f);
}
