#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


static GLFWwindow* window = NULL;

static void resizeDrawWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void window_create(const int width, const int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwMakeContextCurrent(window);

    glewInit();

    glfwSetFramebufferSizeCallback(window, resizeDrawWindow);
}

void window_updateState(void)
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

bool window_isOpen(void)
{
    return !glfwWindowShouldClose(window);
}

bool window_keyPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void window_close(void)
{
    glfwSetWindowShouldClose(window, true);
}

void window_destroy(void)
{
    glfwTerminate();
}
