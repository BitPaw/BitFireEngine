#include "BitFireEngine.h"

#include <future>
#include "../../../ResourceSystem/Source/Model/Model.h"
#include "../../../RenderSystem/Source/OpenGLAPI.h"
#include "../../../RenderSystem/Source/Device/InputContainer.h"
#include "../../../ResourceSystem/Source/Time/StopWatch.h"
#include "../UI/UIText.h"
#include "../../../ResourceSystem/Source/File/File.h"
#include "../../../ResourceSystem/Source/Image/BMP/BMP.h"

BF::BitFireEngine::BitFireEngine()
{
    _callbackListener = nullptr;
    IsRunning = false;
}

void BF::BitFireEngine::SetCallBack(IBitFireEngineListener* callbackListener)
{
    _callbackListener = callbackListener;
}

void BF::BitFireEngine::Start()
{    
    printf
    (
        "+------------------------------------------------------+\n"
        "| __________ .__   __  ___________.__                  |\n"
        "| \\______   \\|__|_/  |_\\_   _____/|__|_______   ____   |\n"
        "|  |    |  _/|  |\\   __\\|   __)   |  |\\_  __ \\_/ __ \\  |\n"
        "|  |    |   \\|  | |  |  |   |     |  | |  | \\/\\  ___/  |\n"
        "|  |________/|__| |__|  \\___|     |__| |__|    \\_____> |\n"
        "+------------------------------------------------------+\n"
    );

    _mainWindow.Create(1000, 1000, "[BFE] <BitFireEngine>");

    printf
    (
        "+------------------------------------------------------+\n"
        "| Graphics Card - Information                          |\n"
        "+------------------------------------------------------+\n"
        "| Vendor           : %-33s |\n"
        "| Model            : %-33s |\n"
        "| OpenGL Version   : %-33s |\n"
        "| Texture Slots    : %-33u |\n"
        "| Maximal Textures : %-33u |\n"
        "+------------------------------------------------------+\n",
        OpenGLAPI::GPUVendorName(),
        OpenGLAPI::GPUModel(),
        OpenGLAPI::VersionName(),
        OpenGLAPI::TextureMaxSlots(),
        OpenGLAPI::TextureMaxLoaded()
    );


    _callbackListener->OnStartUp();

    Resource.PrintContent(true);
   
    IsRunning = true;
}

float _lastUIUpdate = 0;

void BF::BitFireEngine::Update()
{
    //---[Variable Reset]--------------------------------------------------
    float deltaTime = _stopWatch.Reset();

    _gameTickData.ActiveTime = _mainWindow.ActiveTime;
    _gameTickData.CalcualteFramesPerSecounds(deltaTime);

    _lastUIUpdate += deltaTime;

    if (_lastUIUpdate >= .20f)
    {
        _lastUIUpdate = 0;
        _callbackListener->OnUpdateUI();
    }

    float smoothedDelteTime = _gameTickData.GetSmoothDeltaTime();

    //---[User-Input]------------------------------------------------------
    UpdateInput(_mainWindow.GetInput());

    //---[Game-Logic]------------------------------------------------------
    Resource.ModelsPhysicsApply(smoothedDelteTime);

    _callbackListener->OnUpdateGameLogic(smoothedDelteTime);

    //---[Render World]----------------------------------------------------
    Resource.ModelsRender(smoothedDelteTime);

    IsRunning = !_mainWindow.ShouldCloseWindow;
}

void BF::BitFireEngine::UpdateInput(InputContainer* input)
{
    KeyBoard& keyboard = input->KeyBoardInput;
    Mouse& mouse = input->MouseInput;    
    Camera& camera = Resource.MainCamera;
    Vector3<float> movement;

    _mainWindow.Update(); // Pull inputs from window

    if (keyboard.ShitftLeft.IsPressed()) { movement.Add(0, -1, 0); }
    if (keyboard.W.IsPressed()) { movement.Add(0, 0, 1); }
    if (keyboard.A.IsPressed()) { movement.Add(-1, 0, 0); }
    if (keyboard.S.IsPressed()) { movement.Add(0, 0, -1); }
    if (keyboard.D.IsPressed()) { movement.Add(1, 0, 0); }
    if (keyboard.SpaceBar.IsPressed()) 
    {
        camera.Velocity.Set(0.0f, 6.0f, .0f);

        movement.Add(0, 1, 0);
    }
   

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
        Image image;
        BMP bitmap;

        _mainWindow.TakeScreenShot(image);

        bitmap.ConvertFrom(image);
        bitmap.Save("ScreenShot.bmp");
    }

    if (keyboard.F.IsLongPressed())
    {
        switch (camera.Perspective)
        {
            case CameraPerspective::Orthographic:
                camera.PerspectiveChange(CameraPerspective::Perspective);
                break;

            case CameraPerspective::Perspective:
                camera.PerspectiveChange(CameraPerspective::Orthographic);
                break;
        }
    }

    camera.Move(movement);

    camera.Rotate(mouse.InputAxis[0], mouse.InputAxis[1]);

    camera.Update(_gameTickData.GetSmoothDeltaTime());
    keyboard.IncrementButtonTick();
    mouse.ResetAxis();
}

void BF::BitFireEngine::Stop()
{
    IsRunning = false;
}