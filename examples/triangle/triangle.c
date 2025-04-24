#include "../../backend/window.h"
#include "../../backend/shader.h"
#include "../../backend/buffer.h"
#include <GL/glew.h>

int main(void)
{
    window_create(600, 400, "OpenGL Triangle");

    float points[] = 
    {
        0.0f,    0.75f,    // top middle
        -0.75f,   -0.75f,   // left bottom
        0.75f,    -0.75f,   // right bottom
    };

    float colors[] = 
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    unsigned program = createShaderProgram(
            "../examples/triangle/triangle.vert",
            "../examples/triangle/triangle.frag");

    unsigned VAO = createVAO();

    createBuffer(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    createBuffer(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    while (window_isOpen())
    {
        window_updateState();

        glClear(GL_COLOR_BUFFER_BIT);
        // glClearColor(114.0f/255, 114.0f/255, 144.0f/255, 1.0f);
        glClearColor(0.01, 0.01, 0.01, 1.0f);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    window_destroy();
}
