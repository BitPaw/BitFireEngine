#include "GameSystem.h"

#include <future>
#include "../../../ResourceSystem/Source/Model/Model.h"
#include "../../../RenderSystem/Source/OpenGLAPI.h"
#include "../../../RenderSystem/Source/Device/InputContainer.h"
#include "../../../ResourceSystem/Source/Time/StopWatch.h"
#include "../UI/UIText.h"
#include "../../../ResourceSystem/Source/File/File.h"
#include "../../../ResourceSystem/Source/Image/BMP/BMP.h"

BF::GameSystem* BF::GameSystem::_instance = nullptr;

BF::UIText* text;
//BF::Model* sphere;

BF::SkyBox* skybox;
BF::Model cube;

BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

void BF::GameSystem::Start()
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


    //---<TEST>---

    StopWatch stopwatch;

    stopwatch.Start();

    Resource.Load(worldShader, "Shader/WS.vert", "Shader/WS.frag");
    Resource.Load(hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");
   
    Resource.Load("Level/MainMenu.lev");    
    Resource.Load(cube, "Model/Cube.obj");

    cube.ModelMatrix.Scale(10.0f);
    cube.EnablePhysics = true;
    Resource.Add(cube);

    skybox = new SkyBox();
    Resource.Load(skybox->Faces[0], "Texture/SkyBox/Right.bmp"); // Right
    Resource.Load(skybox->Faces[1], "Texture/SkyBox/Left.bmp"); // Left
    Resource.Load(skybox->Faces[2], "Texture/SkyBox/Top.bmp"); // Top
    Resource.Load(skybox->Faces[3], "Texture/SkyBox/Bottom.bmp"); // Bottom
    Resource.Load(skybox->Faces[4], "Texture/SkyBox/Back.bmp"); // Back
    Resource.Load(skybox->Faces[5], "Texture/SkyBox/Front.bmp"); // Front       

    Resource.Load(skybox->Shader, "Shader/SkyBox.vert", "Shader/SkyBox.frag");
    Resource.Add(*skybox);

    text = new UIText("SampleText", *Resource.DefaultFont, -1, -0.8);
    text->RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    Resource.Add(*text);


    //------------------------------------------------------------------------------------

    Resource.PrintContent(true);
    
    printf("[i][Info] Loading took %.2fs\n", stopwatch.Stop());

    IsRunning = true;

}

float _lastUIUpdate = 0;

void BF::GameSystem::Update()
{
    if (_mainWindow.ShouldCloseWindow)
    {
        IsRunning = false;
    }
    else
    {
        //---[Variable Reset]--------------------------------------------------
        float deltaTime = _stopWatch.Reset();

        _gameTickData.ActiveTime = _mainWindow.ActiveTime;
        _gameTickData.CalcualteFramesPerSecounds(deltaTime);

        _lastUIUpdate += deltaTime;

        if (_lastUIUpdate >= .20f)
        {
            _lastUIUpdate = 0;
            UpdateUI();
          
        }

        //---[User-Input]------------------------------------------------------
        UpdateInput(_mainWindow.GetInput());

        //---[Game-Logic]------------------------------------------------------
       // OnGameTick.Trigger(_gameTickData);    
        Resource.ModelsPhysicsApply(_gameTickData.GetSmoothDeltaTime());

        if (cube.ModelMatrix.CurrentPosition().Y <= 0)
        {
            //cube.ModelMatrix.Move(0, tcap, 0);
            cube.Velocity.Set(0, 90, 0);
        }

        //---[Render World]----------------------------------------------------
        Resource.ModelsRender(_gameTickData.GetSmoothDeltaTime());

        //sphere->Orbit(BF::Position<float>(10.0f,0.0f,0.0f));
    }
}

void BF::GameSystem::UpdateUI()
{
    sprintf(text->TextContent, "FPS: %4i", (Math::Ceiling(1 / _gameTickData.GetSmoothDeltaTime())));
    text->SetText(text->TextContent);
    Resource.Add(*text);
}

void BF::GameSystem::UpdateInput(InputContainer* input)
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

void BF::GameSystem::Stop()
{
    IsRunning = false;
}

BF::GameSystem::GameSystem()
{
    _instance = this;

    IsRunning = false;
}