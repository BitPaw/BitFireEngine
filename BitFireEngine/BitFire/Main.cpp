//-----------------------------------------------------------------------------
#include "IO/Message/MessagerSystem.h"
#include "OpenGL/OpenGLAPI.h"
#include "Player/Player.h"

#include "Graphics/Model/CubeModel.h"
#include "Mathematic/Geometry/Vector/Vector3.h"
//-----------------------------------------------------------------------------
int main()
{
    MessagerSystem::PushMessage(MessagePriorityType::Notfication, "BitFire Engine: Starting");

    std::string vertexShader = "Shader/VertexShader.vert";
    std::string fragmentShader = "Shader/FragmentShader.frag";
    std::string objectFilePath = "Objects/Dust II.obj";

    ShaderFile shaderfile(vertexShader, fragmentShader);
    OpenGLAPI* openGL = OpenGLAPI::Instance();
    Player player;  

    openGL->Initialize(&player);
    openGL->Render->AddShader(shaderfile);

    try
    {
        BF::RenderModel triangle = BF::TriangleModel();
        triangle.Move(BF::Vector3(1.5f, 5, -2));

        BF::RenderModel rectangle = BF::RectangleModel();
        rectangle.Move(BF::Vector3(-1.5f, 5, 0));

        BF::RenderModel cube = BF::CubeModel();
        cube.Move(BF::Vector3(1.5f, 5, 5));

        BF::RenderModel dust;
        BF::WaveFront dustObject = BF::WaveFrontLoader::LoadFromFile(objectFilePath);
        dust.LoadFromWaveFront(dustObject);
        dust.ReSize(BF::Vector3(0.005f, 0.005f, 0.005f));
        dust.Move(BF::Vector3(0, -1, 2));    
        
        while (!openGL->ShouldExit())
        {           
            triangle.Rotate(BF::Vector3(0, 0.01f,0));

            openGL->Update();
        }
    }
    catch (const std::exception& e)
    {
        const char* message = e.what();

        MessagerSystem::PushMessage(MessagePriorityType::Error, message);

        e.~exception();

        return 1;
    }

    MessagerSystem::PushMessage(MessagePriorityType::Notfication, "BitFire Engine : Closing");
     
    return 0;
}
//-----------------------------------------------------------------------------