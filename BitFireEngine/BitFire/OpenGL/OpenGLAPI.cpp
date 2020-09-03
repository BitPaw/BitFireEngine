#include "OpenGLAPI.h"

OpenGLAPI::OpenGLAPI()
{
    IsRunning = true;

    _window = new Window(700, 500, "BitFireEngine");
   
    _shaderFile = ShaderFile("BitFire/OpenGL/Shader/Files/VertexShader.vert", "BitFire/OpenGL/Shader/Files/FragmentShader.frag");

    _window->SetShader(_shaderFile);
}

void OpenGLAPI::Update()
{
    _window->Update();

    if (_window->Exit)
    {
        IsRunning = false;
    }
}