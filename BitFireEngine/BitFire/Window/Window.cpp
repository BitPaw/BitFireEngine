#include "Window.h"

Window::Window()
{
    Exit = false;
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::Create(const int width, const int height, const char* title)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return false;
    }

    /* Create a windowed mode window and its OpenGL context */
    {
        _window = glfwCreateWindow(width, height, title, NULL, NULL);
    }

    if (!_window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    if (glewInit() != GLEW_OK)
    {
        return false;
    }
}

void Window::Update()
{
    Exit = glfwWindowShouldClose(_window);

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.0f,  0.5f);
    glVertex2f( 0.5f, -0.5f);
    glEnd();
    */

    //glDrawArrays(GL_TRIANGLES, 0, 3); // Draw all
    
    //glDrawElements(GL_TRIANGLES, 1, NULL); Draw Spacific 

   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(_window);

    /* Poll for and process events */
    glfwPollEvents();
}
