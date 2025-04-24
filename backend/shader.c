#include "shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>


unsigned compileShader(const char* path, const int type)
{
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        printf("file not found: %s\n", path);
        abort();
    }

    fseek(file, 0, SEEK_END);
    int fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* shaderCode = malloc(fileLength + 1);
    int i = 0;
    while ((shaderCode[i] = fgetc(file)) != EOF){i++;}

    unsigned shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char**)&shaderCode, NULL);
    glCompileShader(shader);

    int compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        printf("shader not compiled: %s\n", path);
        abort();
    }

    free(shaderCode);
    fclose(file);

    return shader;
}

unsigned linkProgram(const unsigned shader1, const unsigned shader2)
{
    unsigned program = glCreateProgram();

    glAttachShader(program, shader1);
    glAttachShader(program, shader2);
    glLinkProgram(program);

    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        printf("program not linked\n");
        abort();
    }

    return program;
}

unsigned createShaderProgram(const char* vertPath, const char* fragPath)
{
    unsigned vertexShader = compileShader(vertPath, GL_VERTEX_SHADER);
    unsigned fragmentShader = compileShader(fragPath, GL_FRAGMENT_SHADER);

    unsigned program = linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
