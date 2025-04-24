#include "buffer.h"
#include <GL/glew.h>

unsigned createVAO(void)
{
    unsigned VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    return VAO;
}

unsigned createBuffer(int type)
{
    unsigned BUFFER;

    glGenBuffers(1, &BUFFER);
    glBindBuffer(type, BUFFER);

    return BUFFER;
}
