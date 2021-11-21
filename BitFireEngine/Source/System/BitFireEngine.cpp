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
    printf
    (
        "+------------------------------------------------------+----------------------+\n"
        "| __________ .__   __  ___________.__                  |                      |\n"
        "| \\______   \\|__|_/  |_\\_   _____/|__|_______   ____   | Date %15s |\n"
        "|  |    |  _/|  |\\   __\\|   __)   |  |\\_  __ \\_/ __ \\  | Time %15s |\n"
        "|  |    |   \\|  | |  |  |   |     |  | |  | \\/\\  ___/  |                      |\n"
        "|  |________/|__| |__|  \\___|     |__| |__|    \\_____> |                      |\n"
        "+------------------------------------------------------+----------------------+\n",
        __DATE__,
        __TIME__
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

    _mainWindow.Callback = this;
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
    //---------------------------------------------------------------------

    //---[User-Input]------------------------------------------------------
    _mainWindow.Update(); // Pull inputs from window
    InputContainer& inputPool = _mainWindow.Input;

    UpdateInput(inputPool);

    _callbackListener->OnUpdateInput(inputPool);
    //---------------------------------------------------------------------

    //---[Game-Logic]------------------------------------------------------
    Resource.ModelsPhysicsApply(deltaTime);
    //Resource.Models

    _callbackListener->OnUpdateGameLogic(deltaTime);
    //---------------------------------------------------------------------

    //---[Render World]----------------------------------------------------
    Resource.ModelsRender(deltaTime);
    //---------------------------------------------------------------------

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
        const char* fileName = "ScreenShot.bmp";

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

void BF::BitFireEngine::OnKeyPressed(int key, int scancode, int action, int mods)
{

}

void BF::BitFireEngine::OnMouseButtonClick(int button, int action, int mods)
{

}

void BF::BitFireEngine::OnMousePositionChanged(double positionX, double positionY)
{

}

void BF::BitFireEngine::OnWindowSizeChanged(int width, int height)
{
    Resource.MainCamera.AspectRatioSet(width, height);
}