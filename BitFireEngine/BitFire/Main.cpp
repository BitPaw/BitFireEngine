//-----------------------------------------------------------------------------
#include "IO/Message/MessagerSystem.h"
#include "OpenGL/OpenGLAPI.h"
#include "Player/Player.h"

#include "Graphics/Model/CubeModel.h"
//-----------------------------------------------------------------------------
int main()
{
    MessagerSystem::PushMessage(MessagePriorityType::Notfication, "BitFire Engine: Starting");

    OpenGLAPI* openGL = OpenGLAPI::Instance();
    Player player;

    openGL->Initialize(&player);

    try
    {
        // BF::RenderModel triangle = TriangleModel();
        // triangle.MoveWholeObject(Position(1.5f, 0, 0));

        // BF::RenderModel rectangle = BF::CubeModel();

        BF::RenderModel sphere;
        BF::WaveFront sphereObject = BF::WaveFrontLoader::LoadFromFile("Sphere.obj");
        sphere.LoadFromWaveFront(sphereObject);

        BF::RenderModel world;
        BF::WaveFront worldObject = BF::WaveFrontLoader::LoadFromFile("City.obj");
        world.LoadFromWaveFront(worldObject);
        //world.MoveWholeObject(Position(0, -3, 5));*/
        
        
        /*
        BF::RenderModel world;
        BF::WaveFront worldObject = BF::WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/D.obj");
        world.LoadFromWaveFront(worldObject);
        //world.MoveWholeObject(Position(0, -3, 5));               

        BF::RenderModel rectangle = BF::RectangleModel();
        rectangle.MoveWholeObject(Position(-1.5f, 0, 0));

        BF::RenderModel panzer;
        BF::WaveFront panzereObject = BF::WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/T.obj");
        panzer.LoadFromWaveFront(panzereObject);
        //  panzer.MoveWholeObject(Position(5, 0, 0));
        */        

        while (!openGL->ShouldExit())
        {
            openGL->Update();
        }
    }
    catch (const std::exception& e)
    {
        const char* message = e.what();

        MessagerSystem::PushMessage(MessagePriorityType::Error, message);

        return 1;
    }

    MessagerSystem::PushMessage(MessagePriorityType::Notfication, "BitFire Engine : Closing");

    return 0;
}
//-----------------------------------------------------------------------------