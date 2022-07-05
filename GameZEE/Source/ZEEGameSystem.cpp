#include "ZEEGameSystem.h"

#include <stdio.h>
#include <stdlib.h>

#include <Math/Math.h>
#include <Math/Geometry/Matrix.hpp>
#include <Media/Sound/WAV/WAV.h>
#include <Media/Sound/MID/MID.h>
#include <Media/Image/PNG/PNG.h>
#include <Media/Image/JPEG/JPEG.h>
#include <Media/Font/TTF/TTF.h>
#include <Time/StopWatch.h>

#include <UI/UIText.h>
#include <Shader/ShaderProgram.h>
#include <Graphic/OpenGL/SkyBox.h>
#include <Physic/GravityCube.h>
#include <Model/Model.h>

using namespace BF;

BF::UIText* text;
//BF::Model* sphere;
BF::Texture _blockTexture;

BF::Level _level;

BF::SkyBox skybox;
BF::Renderable _cubeModel;

BF::ShaderProgram _worldShader;
BF::ShaderProgram _hudShaderID;

BF::AudioSource _audioSource;
BF::GravityCube _worldGravity;
float _deltaTime = 0;
BF::Model* model;
BF::Model textureBix;
//BF::Level _level;
BF::AudioClip _audioClip;

#define EnableMusic 1

ZEE::ZEEGameSystem::ZEEGameSystem()
{
    GameSystem.SetCallBack(this);
}

void ZEE::ZEEGameSystem::OnStartUp()
{       
    GameSystem.Load(_worldShader, L"Shader/WS.vert", L"Shader/WS.frag");
    GameSystem.Load(_hudShaderID, L"Shader/HUD.vert", L"Shader/HUD.frag");

    GameSystem.Load
    (
        skybox,
        L"Shader/SkyBox.vert",
        L"Shader/SkyBox.frag",
        L"Texture/SkyBox/Right.png",
        L"Texture/SkyBox/Left.png",
        L"Texture/SkyBox/Top.png",
        L"Texture/SkyBox/Bottom.png",
        L"Texture/SkyBox/Back.png",
        L"Texture/SkyBox/Front.png"
    );    

    //GameSystem.Load(textureBix, "Model/Dialog/DialogBox.obj");

    GameSystem.Load(_blockTexture, L"Texture/Block.bmp",false);
    //GameSystem.Resource.Load("Model/Triangle.obj");
    
   // _worldGravity.IgnoreAxis.Set(true, true, true);
   // _worldGravity.PullForce = GravityForceEarth;
   // _worldGravity.PullDirection.Set(0, -1, 0);
   // GameSystem.Resource.Add(&_worldGravity);

    GameSystem.Load(_level, L"Level/MainMenu.lev");

    //GameSystem.Resource.Load(L"B:/Daten/Textures/PR/Countrry/Neo/FI/Country.obj");

    GameSystem.Load(_cubeModel, L"Model/Cube.obj", false);
   // _cubeModel.Move(0,50,0);
   // _cubeModel.Scale(100.0f);
    _cubeModel.ShaderUse(_worldShader.ID);
    _cubeModel.TextureUse(_blockTexture.ID);
    _cubeModel.Scale(100);
    _cubeModel.Move(250, 0, 0);
        
        //cube.EnablePhysics = true;
    //cube.Mass = 1000;
 
   // cube.MaterialListSize++;
   // cube.MaterialList = new Material();

    //GameSystem.Resource.Add(cube.MaterialList[0].Texture, "C:/Users/BitPaw/Videos/TEST_PNG3.png", false);
    //cube.MeshList[0].RenderInfo.MaterialID = 0;
    

    

   // textureBix.MatrixModel.Scale(10, 2, 1);

 


        

    //text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    //text->MeshList[0].RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    //text->SetText(text->TextContent);
    //GameSystem.Resource.Add(*text);
    

#if EnableMusic // Sound Enable
//BF::MID midi;
//midi.Load("Sound/CaveStory.mid");
//midi.Save("Sound/CaveStory_NEW.mid");

//sound.Load("Sound/Our.mp3");
//sound.Load("Sound/CaveStory.mid");

    GameSystem.Register(_audioSource);
    GameSystem.Load(_audioClip, L"Sound/CatFeet.wav", false);
    GameSystem.Use(_audioSource, _audioClip);

    // GameSystem.LoopPart(audioSource, 100, 100);
    // GameSystem.Play(audioSource, sound);

#endif // Sound Enable
    GameSystem.MainCamera.Update(0);
    GameSystem.MainCamera.Move(0, 0, -100);

    //GameSystem.PrintContent(true);
}

void ZEE::ZEEGameSystem::OnShutDown()
{

}

BF::Vector3<float> rot(0.0349066,0,0);

void ZEE::ZEEGameSystem::OnUpdateGameLogic(float deltaTime)
{    
    /*
    if (cube.MatrixModel.CurrentPosition().Y <= 0)
    {
       // cube.MatrixModel.Move(0, 200, 0);
        cube.Force.Add(0, 50, 0);
    }*/

    _deltaTime = deltaTime;
}

void ZEE::ZEEGameSystem::OnUpdateInput(BF::InputContainer& input)
{
#if EnableMusic
    bool changed = false;
    float value = 0.01f;

    if (input.KeyBoardInput.O.IsPressed())
    {
        _audioSource.PitchIncrease(value);

        changed = true;
    }

    if (input.KeyBoardInput.L.IsPressed())
    {
        _audioSource.PitchReduce(value);

        changed = true;
    }

    if (changed)
    {
        GameSystem.Update(_audioSource);
    }
#endif

    KeyBoard& keyboard = input.KeyBoardInput;
    Mouse& mouse = input.MouseInput;
    Camera& camera = GameSystem.MainCamera;
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

   // auto x = GameSystem.MainCamera.MatrixModel.PositionXYZ();
   // printf("Camera Pos : %5.2f %5.2f %5.2f\n", x.X, x.Y, x.Z);
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