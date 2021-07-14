#include "GameSystem.h"

#include <future>
#include "../../../ResourceSystem/Source/Model/Model.h"
#include "../../../RenderSystem/Source/OpenGLAPI.h"
#include "../../../RenderSystem/Source/Device/InputContainer.h"
#include "../Time/StopWatch.h"
#include "../UI/UIText.h"
#include "../../../ResourceSystem/Source/File/File.h"

BF::GameSystem* BF::GameSystem::_instance = nullptr;

BF::UIText* text;
//BF::Model* sphere;

void BF::GameSystem::Start()
{    
    _mainWindow.Create();

    printf
    (
        "+------------------------------------------------------+\n"
        "| __________ .__   __  ___________.__                  |\n"
        "| \\______   \\|__|_/  |_\\_   _____/|__|_______   ____   |\n"
        "|  |    |  _/|  |\\   __\\|   __)   |  |\\_  __ \\_/ __ \\  |\n"
        "|  |    |   \\|  | |  |  |    |    |  | |  | \\/\\  ___/  |\n"
        "|  |________/|__| |__|  \\____|    |__| |__|    \\_____> |\n"
        "+------------------------------------------------------+\n"
        "| OpenGL Version   : %s\n"
        "| Texture Slots    : %u\n"
        "| Maximal Textures : %u\n"
        "+------------------------------------------------------+\n",
        OpenGLAPI::VersionName(),
        OpenGLAPI::TextureMaxSlots(),
        OpenGLAPI::TextureMaxLoaded()
    );

    BF::StopWatch stopwatch;

    stopwatch.Start();



    const char* vertexShaderWorld = "Shader/WS.vert";
    const char* fragmentShaderWorld = "Shader/WS.frag";
    const char* vertexShaderHUD = "Shader/HUD.vert";
    const char* fragmentShaderHUD = "Shader/HUD.frag";

    Resource.AddShaderProgram(vertexShaderWorld, fragmentShaderWorld);
    unsigned int hudShaderID = Resource.AddShaderProgram(vertexShaderHUD, fragmentShaderHUD);
   
   // sphere = (Model*)Resource.Load("N:/Schule/Studium/Semester/Semester 4/[CGA] Computergrafik und Animation/Praktikum/S21/Projekt/CGA/Praktikum/A_Geometry/assets/models/sphere.obj");
    //sphere->UseTexturePointAsColor();
   // sphere->Move(6.5, 1.5, 0);
   // sphere->Scale(4, 4, 4);
  //  Resource.PushToGPU(*sphere);
    
   

    Resource.Load("Texture/White.bmp");
   // Resource.Load("A:/_WorkSpace/BitFireEngine/Texture/Sign.png");
    Resource.Load("Level/MainMenu.lev");
    
    //Resource.Load("Model/Bike/HQ_Movie cycle.obj");


    text = new UIText("SampleText", *Resource.DefaultFont, -1, -0.8);
    text->RenderInformation.ShaderProgramID = hudShaderID;
    Resource.Add(*text);

    _state = SystemState::Running;

    Resource.PrintContent(true);

    printf("[Info] Loading took %.2fs\n", stopwatch.Stop());


}

void BF::GameSystem::Update()
{
    if (_mainWindow.ShouldCloseWindow)
    {
        _state = SystemState::Stopping;
    }
    else
    {
        //---[Variable Reset]--------------------------------------------------
        _gameTickData.ActiveTime = _mainWindow.ActiveTime;
        _gameTickData.CalcualteFramesPerSecounds(_stopWatch.Reset());

        if(_gameTickData.FramesRendered == 0)
        {
            //sprintf(text->TextContent, "FPS: %4i", (Math::Ceiling(1/ _gameTickData.GetSmoothDeltaTime())));
            //text->SetText(text->TextContent);
           // Resource.Add(*text);
        }    
   
        //---[User-Input]------------------------------------------------------
        UpdateInput(_mainWindow.GetInput());

        //---[Game-Logic]------------------------------------------------------
        OnGameTick.Trigger(_gameTickData);    

        //---[Render World]----------------------------------------------------
        Resource.RenderModels(_gameTickData);

        //sphere->Orbit(BF::Position<float>(10.0f,0.0f,0.0f));
    }
}

void BF::GameSystem::UpdateInput(InputContainer* input)
{
    KeyBoard& keyboard = input->KeyBoardInput;
    Mouse& mouse = input->MouseInput;    
    FirstPersonCamera& camera = Resource.MainCamera;

    _mainWindow.Update(); // Pull inputs from window

    if (keyboard.W.IsPressed()) { camera.Move(Direcion::Forward); }
    if (keyboard.A.IsPressed()) { camera.Move(Direcion::Left); }
    if (keyboard.S.IsPressed()) { camera.Move(Direcion::Backward); }
    if (keyboard.D.IsPressed()) { camera.Move(Direcion::Right); }
    if (keyboard.SpaceBar.IsPressed()) { camera.Move(Direcion::Up); }
    if (keyboard.ShitftLeft.IsPressed()) { camera.Move(Direcion::Down); }

    if (keyboard.R.IsShortPressed())    
    {
        bool axisEnabled = mouse.ShoudRegisterInput();

        if (axisEnabled)
        {
            _mainWindow.SetCursorMode(CursorMode::Ignore);
        }
        else
        {
            _mainWindow.SetCursorMode(CursorMode::Locked);
        }
        keyboard.R.Value = 0xFF;
    }

    if (keyboard.K.IsShortPressed())
    {
        // PixelArray px = TakeScreenShot();
       //  PixelArrayLoader::SaveToFile("C:/_WorkSpace/C++/image.hex",px);
    }

    /*
    if (window->KeyBoardInput->Letter.F)
    {
        camera->Settings->Mode = camera->Settings->Mode == CameraMode::Perspectdive ? CameraMode::Orthographic : CameraMode::Perspectdive;
    }*/

    camera.Rotate(mouse.InputAxis[0], mouse.InputAxis[1]);

    camera.Update(_gameTickData);
    keyboard.IncrementButtonTick();
    mouse.ResetAxis();
}

void BF::GameSystem::Stop()
{
    _state = SystemState::Stopped;
}

BF::GameSystem::GameSystem()
{
    _instance = this;
    _state = SystemState::UnInitialized;   

    _state = SystemState::Ready;
}