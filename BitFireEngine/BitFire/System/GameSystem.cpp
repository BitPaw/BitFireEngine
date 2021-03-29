#include "GameSystem.h"

#include "../Mathematic/Geometry/Form/Cube.h"
#include "../Mathematic/Geometry/Shape/Triangle.h"
#include "../Mathematic/Geometry/Shape/Square.h"
#include "../Mathematic/Geometry/Shape/Rectangle.h"
#include "../UI/Text.h"

#include <future>

BF::GameSystem* BF::GameSystem::_instance = nullptr;

void BF::GameSystem::Start()
{
   // AsciiString levelFilePath = "A:/_WorkSpace/BitFireEngine/Level/MainMenu.lev";
   // LevelLoader::LoadFromFile(level, levelFilePath); // ?? alloc
   // LevelLoader::PrintLevelInfo(level, false);

    AsciiString vertexShaderFilePath("A:/_WorkSpace/BitFireEngine/Shader/WorldSpace.vert");
    AsciiString fragmentShaderFilePath("A:/_WorkSpace/BitFireEngine/Shader/WorldSpace.frag");

    StopWatch stopwatch;

    stopwatch.Start();

    Resource.AddShaderProgram(vertexShaderFilePath, fragmentShaderFilePath);

    Resource.Load("A:/_WorkSpace/BitFireEngine/Model/Dust_II.obj");
    Resource.Load("A:/_WorkSpace/BitFireEngine/Model/Cube.obj");

    Resource.Load("A:/_WorkSpace/BitFireEngine/Texture/MissingTexture.bmp");
    Resource.Load("A:/_WorkSpace/BitFireEngine/Texture/Block.bmp");
    Resource.Load("A:/_WorkSpace/BitFireEngine/Texture/W.png");

    Resource.Load("A:/E.tga");
    Resource.Load("A:/earth.tga");
    Resource.Load("A:/_WorkSpace/BitFireEngine/Font/segoe.fnt");
    
    
    printf(">>> Loading took %lfs\n",stopwatch.Stop());

    Resource.PrintContent(true);
    
    _state = SystemState::Running;

    glLineWidth(10);
    glPointSize(5);
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
        _gameTickData.DeltaTime = _stopWatch.Reset();

        //---[User-Input]------------------------------------------------------
        UpdateInput(_mainWindow.GetInput());

        //---[Game-Logic]------------------------------------------------------
        OnGameTick.Trigger(_gameTickData);
      
        //---[Render World]----------------------------------------------------
        RenderScene();
    }
}

void BF::GameSystem::RenderScene()
{
    int lastProgrammID = -1;
    int lastTextureID = -1;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1);

    Resource.RenderModels(_gameTickData);
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

    camera.Rotate(mouse.InputAxis.X, mouse.InputAxis.Y);

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

    _gameTickData.DeltaTime = _stopWatch.Reset();

    _state = SystemState::Ready;
}