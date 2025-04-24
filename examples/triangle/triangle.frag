#version 330 core

out vec4 out_color;

in vec3 vertice_colors;

void main()
{
    out_color = vec4(vertice_colors, 1.0f);
}
