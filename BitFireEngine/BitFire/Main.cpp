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

        RenderModel rec = CubeModel();
        rec.MoveWholeObject(Position(-1.5f, 0, 0));

        RenderModel cube;
        WaveFront cubeObject = WaveFrontLoader::LoadFromFile("Cube.obj");
        cube.LoadFromWaveFront(cubeObject);
        cube.MoveWholeObject(Position(-1.5f, -2, 0));

        RenderModel sphere;
        WaveFront sphereObject = WaveFrontLoader::LoadFromFile("Sphere.obj");
        sphere.LoadFromWaveFront(sphereObject);
        sphere.MoveWholeObject(Position(1.5f, -2, 0));

        RenderModel panzer;
        WaveFront panzereObject = WaveFrontLoader::LoadFromFile("Tiger.obj");
        panzer.LoadFromWaveFront(panzereObject);
        panzer.MoveWholeObject(Position(5, 0, 0));

        // RenderModel world;
        // WaveFront worldObject = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/old/D.obj");
        // world.LoadFromWaveFront(worldObject);
        // world.MoveWholeObject(Position(0, -3, 5));

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