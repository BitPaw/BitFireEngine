#include "Window.h"

KeyBoard* Window::KeyBoardInput;

Window::Window()
{
    Exit = false;

    KeyBoardInput = new KeyBoard();
}

Window::~Window()
{
    glfwTerminate();

    delete KeyBoardInput;
}

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    KeyBoard* keyBoard = Window::KeyBoardInput;

    //keyBoard->Reset();

    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_W)   keyBoard->W = true;
        if (key == GLFW_KEY_A)   keyBoard->A = true;
        if (key == GLFW_KEY_S)   keyBoard->S = true;
        if (key == GLFW_KEY_D)   keyBoard->D = true;
        if (key == GLFW_KEY_F)   keyBoard->F = true;
        if (key == GLFW_KEY_G)   keyBoard->G = true;

        if (key == GLFW_KEY_E)   keyBoard->E = true;
        if (key == GLFW_KEY_R)   keyBoard->R = true;
    }

    if (action == GLFW_RELEASE)
    {
        if (key == GLFW_KEY_W)   keyBoard->W = false;
        if (key == GLFW_KEY_A)   keyBoard->A = false;
        if (key == GLFW_KEY_S)   keyBoard->S = false;
        if (key == GLFW_KEY_D)   keyBoard->D = false;
        if (key == GLFW_KEY_F)   keyBoard->F = false;
        if (key == GLFW_KEY_G)   keyBoard->G = false;

        if (key == GLFW_KEY_E)   keyBoard->E = false;
        if (key == GLFW_KEY_R)   keyBoard->R = false;
    }
  


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

    glfwSetKeyCallback(_window, OnKeyPressed);

    glfwSwapInterval(1);
}




void Window::Update()
{
    Exit = glfwWindowShouldClose(_window);

    //Window::KeyBoardInput->Reset();

    /* Render here */
    //glClear(GL_COLOR_BUFFER_BIT);

    /*
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.0f,  0.5f);
    glVertex2f( 0.5f, -0.5f);
    glEnd();
    */

   // glDrawArrays(GL_TRIANGLES, 0, 3); // Draw all
    
    //glDrawElements(GL_TRIANGLES, 1, NULL); Draw Spacific 

   //glDrawElements(GL_TRIANGLES, 8631, GL_UNSIGNED_INT, nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(_window);

    /* Poll for and process events */
    glfwPollEvents();
}
