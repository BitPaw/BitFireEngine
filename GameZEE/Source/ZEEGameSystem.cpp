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

BF::UIText* text;
//BF::Model* sphere;

BF::SkyBox skybox;
BF::Model cube;

BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

BF::AudioSource audioSource;
BF::Sound sound;
BF::GravityCube _worldGravity;

ZEE::ZEEGameSystem::ZEEGameSystem()
{
    GameSystem.SetCallBack(this);
}

float _deltaTime = 0;
BF::Model* model;

BF::Model textureBix;

void ZEE::ZEEGameSystem::OnStartUp()
{   
    BF::PNG png;

    png.Load("Wb.png");
    png.Save("Wb_EE.png");


    BF::StopWatch stopwatch;

    stopwatch.Start();

    GameSystem.Resource.Load(worldShader, "Shader/WS.vert", "Shader/WS.frag");
    GameSystem.Resource.Load(hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");

    GameSystem.Resource.Load(textureBix, "Model/Dialog/DialogBox.obj");

    GameSystem.Resource.Load("Texture/Block.bmp");
    GameSystem.Resource.Load("Model/Triangle.obj");

    _worldGravity.IgnoreAxis(true, true, true);
    _worldGravity.PullForce.Set(0, -GravityForceEarth, 0);
    GameSystem.Resource.Add(&_worldGravity);

    GameSystem.Resource.Load("Level/MainMenu.lev");
    GameSystem.Resource.Load(cube, "Model/Cube.obj");   

    textureBix.MatrixModel.Scale(10, 2, 1);

    cube.MatrixModel.Scale(10.0f);
    cube.EnablePhysics = true;       

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

    text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    text->RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    text->SetText(text->TextContent);
    GameSystem.Resource.Add(*text);
    

    printf("[i][Info] Loading took %.2fs\n", stopwatch.Stop());

    GameSystem.Resource.PrintContent(true);    



#if 1 // Sound Enable
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
        cube.Velocity.Set(0, _worldGravity.PullForce.Y * -50, 0);
    }

    _deltaTime = deltaTime;
}

void ZEE::ZEEGameSystem::OnUpdateInput(BF::InputContainer& input)
{
#if 1
    bool changed = false;

    if (input.KeyBoardInput.O.IsPressed())
    {
        audioSource.Pitch += 0.01;
        if (audioSource.Pitch > 2.8)

        {
            audioSource.Pitch = 2.8;
        }


      
        changed = true;
    }

    if (input.KeyBoardInput.L.IsPressed())
    {
        audioSource.Pitch -= 0.01;

        if (audioSource.Pitch < 0.3)
        {
            audioSource.Pitch = 0.3;
        }

        changed = true;
    }

    if (changed)
    {
        GameSystem.SoundPlayer.Update(audioSource);
    }
#endif
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