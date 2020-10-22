#include "OpenGLAPI.h"

BF::OpenGLAPI* BF::OpenGLAPI::_instance = nullptr;

BF::OpenGLAPI::OpenGLAPI()
{
    _instance = this;
}

BF::OpenGLAPI* BF::OpenGLAPI::Instance()
{
    return _instance == nullptr ? new OpenGLAPI() : _instance;
}

void BF::OpenGLAPI::Initialize(Player* player)
{
    MainWindow = new Window(player);
    Render = new BF::RenderSystem(player);    
}

void BF::OpenGLAPI::Update()
{
    MainWindow->Update();
    Render->RenderScene();
}

bool BF::OpenGLAPI::ShouldExit()
{
    return MainWindow->ShouldExit();
}