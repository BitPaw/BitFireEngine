//-----------------------------------------------------------------------------
#include "IO/Message/MessagerSystem.h"
#include "OpenGL/OpenGLAPI.h"
#include "Player/Player.h"

#include "Graphics/Model/CubeModel.h"
//-----------------------------------------------------------------------------
int main()
{
    MessagerSystem::PushMessage(Message(MessagePriorityType::Notfication, "BitFire Engine: Starting"));

    OpenGLAPI* openGL = OpenGLAPI::Instance();
    Player player;

    openGL->Initialize(&player);

    try
    {

        RenderModel triangle = TriangleModel();
        triangle.MoveWholeObject(Position(1.5f, 0, 0));

        RenderModel rec = RectangleModel();
        rec.MoveWholeObject(Position(-1.5f,0,0));

        RenderModel cube;
        WaveFront cubeObject = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/old/Data/Q.obj");
        cube.LoadFromWaveFront(cubeObject);
        cube.MoveWholeObject(Position(-1.5f, -2, 0));

        RenderModel sphere;
        WaveFront sphereObject = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/old/Data/S.obj");
        sphere.LoadFromWaveFront(sphereObject);
        sphere.MoveWholeObject(Position(1.5f, -2, 0));

        RenderModel panzer;
        WaveFront panzereObject = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/old/Data/T.obj");
        panzer.LoadFromWaveFront(panzereObject);
        panzer.MoveWholeObject(Position(5, 0, 0));

      //  RenderModel world;
      //  WaveFront worldObject = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/D.obj");
       // world.LoadFromWaveFront(worldObject);
      //  world.MoveWholeObject(Position(0,0,0));

        while (!openGL->ShouldExit())
        {
            openGL->Update();
        }
    }
    catch (const std::exception& e)
    {
        const char* message = e.what();

        MessagerSystem::PushMessage(Message(MessagePriorityType::Error, message));

        return 1;
    }
    
    MessagerSystem::PushMessage(Message(MessagePriorityType::Notfication, "BitFire Engine : Closing"));

    return 0;
}
//-----------------------------------------------------------------------------