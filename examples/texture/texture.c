#include "../../backend/backend.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

int main(void)
{
    window_create(400, 400, "OpenGL Textures");

    float openglPoints[] = 
    {
             // vertices              // texture coordinates
        -1.0f,   1.0f,    0.0f,  1.0f, // left top - 0
        -0.6f,   1.0f,    1.0f,  1.0f, // right top - 1
        -1.0f,   0.8f,   0.0f, 0.0f, // left bottom - 2
       -0.6f,  0.8f,   1.0f, 0.0f  // right bottom - 3
    };

    float wallPoints[] = 
    {
             // vertices              // texture coordinates
        -0.5f,   0.5f,    0.0f,  1.0f, // left top - 0
        0.5f,    0.5f,    1.0f,  1.0f, // right top - 1
        -0.5f,  -0.5f,   0.0f, 0.0f, // left bottom - 2
        0.5f, -0.5f,   1.0f, 0.0f  // right bottom - 3
    };

    unsigned quadParts[] = 
    {
        0, 2, 3, // left triangle
        0, 1, 3 // right triangle
    };

    stbi_set_flip_vertically_on_load(true);

    int openglTexW, openglTexY, openglTexC;
    unsigned char* openglTexData = stbi_load(
            "../examples/texture/opengl.jpg", 
            &openglTexW, 
            &openglTexY, 
            &openglTexC, 0);
    if (openglTexData == NULL)
    {
        printf("can't find texture\n");
        abort();
    }
    unsigned openglTexture;
    glGenTextures(1, &openglTexture);
    glBindTexture(GL_TEXTURE_2D, openglTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, openglTexW, openglTexY, 0, GL_RGB, GL_UNSIGNED_BYTE, openglTexData);
    glGenerateMipmap(GL_TEXTURE_2D);

    int wallTexW, wallTexY, wallTexC;
    unsigned char* wallTexData = stbi_load(
            "../examples/texture/brick.jpg", 
            &wallTexW, 
            &wallTexY, 
            &wallTexC, 0);
    if (wallTexData == NULL)
    {
        printf("can't find texture\n");
        abort();
    }
    unsigned wallTexture;
    glGenTextures(1, &wallTexture);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallTexW, wallTexY, 0, GL_RGB, GL_UNSIGNED_BYTE, wallTexData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(wallTexData);

    unsigned openglShader = createShaderProgram(
            "../examples/texture/opengl.vert",
            "../examples/texture/opengl.frag"
            );

    unsigned wallShader = createShaderProgram(
            "../examples/texture/wall.vert",
            "../examples/texture/wall.frag"
            );
    float wallUniformLoc = glGetUniformLocation(wallShader, "scale");

    unsigned openglVAO = createVAO();
    createBuffer(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(openglPoints), openglPoints, GL_STATIC_DRAW);
    createBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadParts), quadParts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned wallVAO = createVAO();
    createBuffer(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallPoints), wallPoints, GL_DYNAMIC_DRAW);
    createBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadParts), quadParts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    float scale = 0.5f;
    float scaleOffset = 0.075f;
    while(window_isOpen())
    {
        window_updateState();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        if (window_keyPressed(GLFW_KEY_W))
        {
            if (scale >= 0.02f)
                scale -= scaleOffset;
        }
        if (window_keyPressed(GLFW_KEY_S))
        {
            if (scale <= 2.0f)
                scale += scaleOffset;
        }

        glBindVertexArray(wallVAO);
        glUseProgram(wallShader);
        glUniform1f(wallUniformLoc, scale);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(openglVAO);
        glUseProgram(openglShader);
        glBindTexture(GL_TEXTURE_2D, openglTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    window_destroy();
}
