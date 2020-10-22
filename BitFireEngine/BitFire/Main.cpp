 //-----------------------------------------------------------------------------
#include "IO/Message/MessageSystem.h"
#include "OpenGL/OpenGLAPI.h"
#include "Player/Player.h"

#include "Mathematic/Geometry/Vector/Vector3.h"

#include "Resources/Model/ModelLoader.h"
#include "Resources/Image/ImageLoader.h"
//-----------------------------------------------------------------------------
int main()
{
    BF::MessageSystem::PushMessage(BF::MessageType::Notfication, "BitFire Engine: Starting");

    // Paths for Shader & Object, Change this here...
    std::string vertexShader = "VertexShader.vert";
    std::string fragmentShader = "FragmentShader.frag";
    std::string objectFilePath = "Dust II.obj";

    BF::ShaderFile shaderfile(vertexShader, fragmentShader);
    BF::OpenGLAPI* openGL = BF::OpenGLAPI::Instance();
    BF::Player player;

    openGL->Initialize(&player);
    openGL->Render->AddShader(shaderfile);
    
    try
    {   
        // Loads a texture
        BF::IImage* image = BF::ImageLoader::LoadFromFile("B.bmp");

        // Load a object
        BF::IModel* country = BF::ModelLoader::LoadFromFile(objectFilePath);
        country->Scale(BF::Vector3(0.02, 0.02, 0.02));
        country->MoveBy(BF::Vector3(-10, -2, 0));
        
        openGL->MainWindow->SetCursorTexture((BF::Image*)image);
        openGL->MainWindow->SetIcon((BF::Image*)image);

        while (!openGL->ShouldExit())
        {           
            openGL->Update();
        }
    }
    catch (const std::exception& e)
    {
        const char* message = e.what();

        BF::MessageSystem::PushMessage(BF::MessageType::Error, message);

        e.~exception();

        return 1;
    }

    BF::MessageSystem::PushMessage(BF::MessageType::Notfication, "BitFire Engine : Closing");
     
    return 0;
}
//-----------------------------------------------------------------------------