#include "BitFireEngine.h"

#include "../UI/UIText.h"
#include "../../../SystemResource/Source/Model/Model.h"
#include "../../../SystemResource/Source/Time/StopWatch.h"
#include "../../../SystemResource/Source/File/File.h"
#include "../../../SystemResource/Source/Image/BMP/BMP.h"
#include "../../../SystemRender/Source/OpenGLAPI.h"
#include "../../../SystemRender/Source/Device/InputContainer.h"

#include <stdlib.h>

BF::BitFireEngine::BitFireEngine()
{
    _callbackListener = nullptr;
    IsRunning = false;
    _deltaTime = 0;
}

void BF::BitFireEngine::SetCallBack(IBitFireEngineListener* callbackListener)
{
    _callbackListener = callbackListener;
}

void BF::BitFireEngine::Start()
{    
    unsigned int versionMajor = 0;
    unsigned int versionMinor = 0;
    unsigned int versionPatch = 1;

    printf
    (
        "+------------------------------------------------------+----------------------+\n"
        "| __________ .__   __  ___________.__                  | Version    v.%i.%i.%03i |\n"
        "| \\______   \\|__|_/  |_\\_   _____/|__|_______   ____   | Date     02 Sep 2021 |\n"
        "|  |    |  _/|  |\\   __\\|   __)   |  |\\_  __ \\_/ __ \\  |                      |\n"
        "|  |    |   \\|  | |  |  |   |     |  | |  | \\/\\  ___/  |                      |\n"
        "|  |________/|__| |__|  \\___|     |__| |__|    \\_____> |                      |\n"
        "+------------------------------------------------------+----------------------+\n"
    ,
        versionMajor,
        versionMinor,
        versionPatch
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
   
    IsRunning = true;
}

float _lastUIUpdate = 0;

void BF::BitFireEngine::Update()
{
    //---[Variable Reset]--------------------------------------------------
    float deltaTime = _stopWatch.Reset();
    _deltaTime = deltaTime;

    _lastUIUpdate += deltaTime;

    if (_lastUIUpdate >= .20f)
    {
        _lastUIUpdate = 0;

        Resource.CheckUncachedData();

        _callbackListener->OnUpdateUI();
    }

    //---[User-Input]------------------------------------------------------
    _mainWindow.Update(); // Pull inputs from window
    auto inputPool = _mainWindow.GetInput();
    auto& eeeeee = *inputPool;

    UpdateInput(eeeeee);

    _callbackListener->OnUpdateInput(eeeeee);

    //---[Game-Logic]------------------------------------------------------
    Resource.ModelsPhysicsApply(deltaTime);

    _callbackListener->OnUpdateGameLogic(deltaTime);

    //---[Render World]----------------------------------------------------
    Resource.ModelsRender(deltaTime);

    IsRunning = !_mainWindow.ShouldCloseWindow;
}

void BF::BitFireEngine::UpdateInput(InputContainer& input)
{
    KeyBoard& keyboard = input.KeyBoardInput;
    Mouse& mouse = input.MouseInput;    
    Camera& camera = Resource.MainCamera;

    _callbackListener->OnUpdateInput(input);
    
    if (keyboard.J.IsShortPressed())
    {
        Resource.PrintContent(true);        
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
        const char fileName[] = "ScreenShot.bmp";

        _mainWindow.TakeScreenShot(image);

        image.Save(fileName, ImageFileFormat::BitMap);
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

    camera.Update(_deltaTime);
    keyboard.IncrementButtonTick();
    mouse.ResetAxis();
}

void BF::BitFireEngine::Stop()
{
    IsRunning = false;
}