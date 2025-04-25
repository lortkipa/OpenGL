#version 330 core

out vec4 finalColor;

in vec2 textureCoord;
uniform sampler2D textureData;

void main()
{
    finalColor = texture(textureData, textureCoord);
}
