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

    OpenGLAPI* openGL = OpenGLAPI::Instance();
    Player player;

    openGL->Initialize(&player);

    try
    {
        BF::RenderModel triangle = BF::TriangleModel();
        triangle.Move(BF::Vector3(1.5f, 1, 0));

        BF::RenderModel rectangle = BF::RectangleModel();
        rectangle.Move(BF::Vector3(-1.5f, 0, 0));

        BF::RenderModel cube = BF::CubeModel();
        //cube.MoveInDirection(BF::Vector3(1.5f, 0, 0));

        /*
        BF::RenderModel sphere;
        BF::WaveFront sphereObject = BF::WaveFrontLoader::LoadFromFile("A:/QF.obj");// <- OBJ needed
        sphere.LoadFromWaveFront(sphereObject);
      
        sphere.Move(BF::Vector3(-1.5f, -1, 0));
        //        sphere.UseTexturePointAsColor();

        BF::RenderModel dust;
        BF::WaveFront dustObject = BF::WaveFrontLoader::LoadFromFile("A:/D.obj"); // <- OBJ needed
        dust.LoadFromWaveFront(dustObject);
        dust.ReSize(BF::Vector3(0.005f,0.005f,0.005f));
        dust.Move(BF::Vector3(0,0,2));
        */
        while (!openGL->ShouldExit())
        {           
            BF::Vector3 currpos = triangle.CurrentPosition();

            if (currpos.X >= 10.0f)
            {
                triangle.MoveTo(BF::Vector3(0, 0, 0));
            }
            else
            {
                triangle.Move(BF::Vector3(0.05f, 0, 0));
            }

            cube.Rotate(BF::Vector3(0, 0.01f,0));

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