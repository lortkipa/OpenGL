#include "../../backend/backend.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    window_create(600, 400, "OpenGL Quad");

    float quadPoints[] = 
    {
        // coordinates        // colors
        -0.8f,  0.8f, 1.0f, 0.0f, 0.0f, // left top - 0
        0.8f,  0.8f,  0.0f, 1.0f, 0.0f, // right top - 1
        -0.8f, -0.8f,0.0f, 0.0f, 1.0f, // left bottom - 2
        0.8f, -0.8f, 1.0f, 234.0f/255, 0.0f // right bottom - 3
    };

    unsigned quadParts[] =
    {
        0, 2, 3, // left triangle
        0, 1, 3, // right triangle
    };

    float colors[] = 
    {
        1.0f, 0.0f, 0.0f,           // red
        0.0f, 1.0f, 0.0f,           // green
        0.0f, 0.0f, 1.0f,           // blue
        1.0f, 234.0f/255, 0.0f    // yellow
    };

    unsigned program = createShaderProgram(
            "../examples/quad/quad.vert",
            "../examples/quad/quad.frag"
            );

    unsigned VAO = createVAO();

    createBuffer(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadPoints), quadPoints, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    createBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadParts), quadParts, GL_DYNAMIC_DRAW);

    int uniformLoc = glGetUniformLocation(program, "scale");

    float scale = 0.5f;
    while (window_isOpen())
    {
        window_updateState();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        if (window_keyPressed(GLFW_KEY_W))
        {
            if (scale <= 0.99f)
            {
                scale += 0.025f;
            }
        }

        if (window_keyPressed(GLFW_KEY_S))
        {
            if (scale >= 0.05f)
            {
                scale -= 0.025f;
            }
        }

        glUseProgram(program);
        glUniform1f(uniformLoc, scale);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    window_close();
}
