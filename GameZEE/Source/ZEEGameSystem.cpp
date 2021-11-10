#include "ZEEGameSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../BitFireEngine/Source/UI/UIText.h"
#include "../../SystemResource/Source/Time/StopWatch.h"
#include "../../SystemResource/Source/Shader/ShaderProgram.h"
#include "../../SystemResource/Source/Game/SkyBox.h"
#include "../../SystemResource/Source/Model/Model.h"
#include "../../SystemResource/Source/Math/Math.h"
#include "../../SystemResource/Source/Sound/WAV/WAV.h"
#include "../../SystemResource/Source/Sound/MID/MID.h"
#include "../../SystemResource/Source/Math/Geometry/Matrix.hpp"
#include "../../SystemResource/Source/Image/PNG/PNG.h"
#include "../../SystemResource/Source/Math/Physic/GravityCube.h"
#include "../../SystemResource/Source/Image/JPEG/JPEG.h"


using namespace BF;

BF::UIText* text;
//BF::Model* sphere;

BF::SkyBox skybox;
BF::Model cube;

BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

BF::AudioSource audioSource;
BF::Sound sound;
BF::GravityCube _worldGravity;
float _deltaTime = 0;
BF::Model* model;
BF::Model textureBix;

ZEE::ZEEGameSystem::ZEEGameSystem()
{
    GameSystem.SetCallBack(this);
}

void ZEE::ZEEGameSystem::OnStartUp()
{   
    /*
    BF::JPEG jpeg;
    jpeg.Load("B:/Daten/Bilder/_garbage/KN.jpg");


    BF::PNG png;

    png.Load("Wb.png");
    png.Save("Wb_EE.png");*/

    BF::StopWatch stopwatch;

    stopwatch.Start();

    GameSystem.Resource.Load(worldShader, "Shader/WS.vert", "Shader/WS.frag");
    GameSystem.Resource.Load(hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");

    GameSystem.Resource.Load(textureBix, "Model/Dialog/DialogBox.obj");

    GameSystem.Resource.Load("Texture/Block.bmp");   
    GameSystem.Resource.Load("Model/Triangle.obj");
    
    _worldGravity.IgnoreAxis.Set(true, true, true);
    _worldGravity.PullForce = GravityForceEarth;
    _worldGravity.PullDirection.Set(0, -1, 0);
    GameSystem.Resource.Add(&_worldGravity);

    GameSystem.Resource.Load(cube, "Model/Cube.obj");
    cube.MatrixModel.Scale(10.0f);
    cube.EnablePhysics = true;
    cube.Mass = 1000;

    
    GameSystem.Resource.Load("Level/MainMenu.lev");


    textureBix.MatrixModel.Scale(10, 2, 1);



    GameSystem.Resource.Load
    (
        skybox,
        "Shader/SkyBox.vert",
        "Shader/SkyBox.frag",
        "Texture/SkyBox/Right.bmp",
        "Texture/SkyBox/Left.bmp",
        "Texture/SkyBox/Top.bmp",
        "Texture/SkyBox/Bottom.bmp",
        "Texture/SkyBox/Back.bmp",
        "Texture/SkyBox/Front.bmp"
    );           

    //text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    //text->MeshList[0].RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    //text->SetText(text->TextContent);
    //GameSystem.Resource.Add(*text);
    

    printf("[i][Info] Loading took %.2fs\n", stopwatch.Stop());

    GameSystem.Resource.PrintContent(true);    

    

#if 0 // Sound Enable
    //BF::MID midi;
    //midi.Load("Sound/CaveStory.mid");
    //midi.Save("Sound/CaveStory_NEW.mid");

    //sound.Load("Sound/Our.mp3");
    sound.Load("Sound/CatFeet.wav");
    //sound.Load("Sound/CaveStory.mid");

    GameSystem.SoundPlayer.Register(audioSource);
    GameSystem.SoundPlayer.Register(sound);



    GameSystem.SoundPlayer.Play(audioSource, sound);

    GameSystem.SoundPlayer.LoopPart(audioSource, 100, 100);

    GameSystem.SoundPlayer.Play(audioSource, sound);

#endif // Sound Enable
}

void ZEE::ZEEGameSystem::OnShutDown()
{

}

BF::Vector3<float> rot(0.0349066,0,0);

void ZEE::ZEEGameSystem::OnUpdateGameLogic(float deltaTime)
{    
    if (cube.MatrixModel.CurrentPosition().Y <= 0)
    {
        //cube.ModelMatrix.Move(0, tcap, 0);
        //cube.Force.Add(0, 50, 0);
    }

    _deltaTime = deltaTime;
}

void ZEE::ZEEGameSystem::OnUpdateInput(BF::InputContainer& input)
{
#if 0
    bool changed = false;
    float value = 0.01f;

    if (input.KeyBoardInput.O.IsPressed())
    {
        audioSource.PitchIncrease(value);

        changed = true;
    }

    if (input.KeyBoardInput.L.IsPressed())
    {
        audioSource.PitchReduce(value);

        changed = true;
    }

    if (changed)
    {
        GameSystem.SoundPlayer.Update(audioSource);
    }
#endif

    KeyBoard& keyboard = input.KeyBoardInput;
    Mouse& mouse = input.MouseInput;
    Camera& camera = GameSystem.Resource.MainCamera;
    Vector3<float> movement;

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

    camera.Move(movement);

    camera.Rotate(mouse.InputAxis[0], mouse.InputAxis[1]);

    camera.Update(_deltaTime);
    keyboard.IncrementButtonTick();
    mouse.ResetAxis();
}

void ZEE::ZEEGameSystem::OnUpdateUI()
{
    //sprintf_s(text->TextContent, "FPS: %4i", (BF::Math::Ceiling(1 / _deltaTime)));
    //text->SetText(text->TextContent);

    if (model == nullptr)
    {
       // model = GameSystem.Resource.GetModel(0);
    }
    else
    {
       // model->ModelMatrix.Rotate(rot);
    }
}