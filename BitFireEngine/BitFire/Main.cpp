//-----------------------------------------------------------------------------
#include "IO/Message/MessagerSystem.h"
#include "OpenGL/OpenGLAPI.h"
//-----------------------------------------------------------------------------
int main()
{
    MessagerSystem::PushMessage(Message(MessagePriorityType::Notfication, "BitFire Engine: Starting"));

    OpenGLAPI openGL;
  
    try
    {
        while (openGL.IsRunning)
        {
            openGL.Update();
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