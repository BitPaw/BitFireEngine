//-----------------------------------------------------------------------------
#include "IO/Message/MessagerSystem.h"
#include "OpenGL/OpenGLAPI.h"
#include "Player/Player.h"

#include <GLM/glm.hpp>

#include "Graphics/Model/CubeModel.h"
#include "Mathematic/Geometry/Vector/Vector3.h"
//-----------------------------------------------------------------------------
int main()
{
    MessagerSystem::PushMessage(MessagePriorityType::Notfication, "BitFire Engine: Starting");

    OpenGLAPI* openGL = OpenGLAPI::Instance();
    Player player;

    openGL->Initialize(&player);


    try
    {
        //BF::RenderModel triangle = TriangleModel();
        // triangle.MoveWholeObject(Position(1.5f, 0, 0));

        //BF::RenderModel triangle = BF::TriangleModel();

        BF::RenderModel cube = BF::CubeModel();
        BF::RenderModel rectangle = BF::CubeModel();
        rectangle.MoveInDirection(BF::Vector3(1.5f, 2, 0));
        
        
       // BF::RenderModel sphere;
        //BF::WaveFront sphereObject = BF::WaveFrontLoader::LoadFromFile("A:/D.obj");
       // sphere.LoadFromWaveFront(sphereObject);
     

        float vv = 0;

        while (!openGL->ShouldExit())
        {
            /*
            vv += 0.1;

            float x = cosf(vv);
            float y = sinf(vv);


            rectangle.MoveInDirection(BF::Vector3(x*0.01, 0, y*0.01));
            */

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