#include "OpenGLAPI.h"

OpenGLAPI* OpenGLAPI::_instance = nullptr;

OpenGLAPI::OpenGLAPI()
{
    _instance = this;
}

OpenGLAPI* OpenGLAPI::Instance()
{
    return _instance == nullptr ? new OpenGLAPI() : _instance;
}

void OpenGLAPI::Initialize(Player* player)
{
    MainWindow = new Window(player);
    Render = new BF::RenderSystem(player);

    Render->AddShader(ShaderFile("BitFire/OpenGL/Shader/Files/VertexShader.vert", "BitFire/OpenGL/Shader/Files/FragmentShader.frag"));
}

void OpenGLAPI::Update()
{
    MainWindow->Update();
    Render->RenderScene();
}

bool OpenGLAPI::ShouldExit()
{
    return MainWindow->ShouldExit();
}
