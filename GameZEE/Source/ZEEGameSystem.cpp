#include "ZEEGameSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../BitFireEngine/Source/UI/UIText.h"
#include "../../SystemResource/Source/Time/StopWatch.h"
#include "../../SystemResource/Source/Shader/ShaderProgram.h"
#include "../../SystemResource/Source/Game/SkyBox.h"
#include "../../SystemResource/Source/Model/Model.h"
#include "../../SystemResource/Source/Math/Math.h"

BF::UIText* text;
//BF::Model* sphere;

BF::SkyBox* skybox;
BF::Model cube;

BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

ZEE::ZEEGameSystem::ZEEGameSystem()
{
    GameSystem.SetCallBack(this);
}

float _deltaTime = 0;
BF::Model* model;

void ZEE::ZEEGameSystem::OnStartUp()
{
    BF::StopWatch stopwatch;

    stopwatch.Start();

    GameSystem.Resource.Load(worldShader, "Shader/WS.vert", "Shader/WS.frag");
    GameSystem.Resource.Load(hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");

    GameSystem.Resource.Load("Texture/Block.bmp");
    GameSystem.Resource.Load("Level/MainMenu.lev");
    GameSystem.Resource.Load(cube, "Model/Cube.obj");

    cube.ModelMatrix.Scale(10.0f);
    cube.EnablePhysics = true;
   // GameSystem.Resource.Add(cube);

    

    skybox = new BF::SkyBox();
    GameSystem.Resource.Load(skybox->Faces[0], "Texture/SkyBox/Right.bmp"); // Right
    GameSystem.Resource.Load(skybox->Faces[1], "Texture/SkyBox/Left.bmp"); // Left
    GameSystem.Resource.Load(skybox->Faces[2], "Texture/SkyBox/Top.bmp"); // Top
    GameSystem.Resource.Load(skybox->Faces[3], "Texture/SkyBox/Bottom.bmp"); // Bottom
    GameSystem.Resource.Load(skybox->Faces[4], "Texture/SkyBox/Back.bmp"); // Back
    GameSystem.Resource.Load(skybox->Faces[5], "Texture/SkyBox/Front.bmp"); // Front       

    GameSystem.Resource.Load(skybox->Shader, "Shader/SkyBox.vert", "Shader/SkyBox.frag");
    
    
    GameSystem.Resource.Add(*skybox);
    




    text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    text->RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    text->SetText(text->TextContent);
    GameSystem.Resource.Add(*text);
    

    printf("[i][Info] Loading took %.2fs\n", stopwatch.Stop());

    GameSystem.Resource.PrintContent(true);
}

void ZEE::ZEEGameSystem::OnShutDown()
{

}

BF::Vector3<float> rot(0.0349066,0,0);

void ZEE::ZEEGameSystem::OnUpdateGameLogic(float deltaTime)
{
    
    if (cube.ModelMatrix.CurrentPosition().Y <= 0)
    {
        //cube.ModelMatrix.Move(0, tcap, 0);
        cube.Velocity.Set(0, 90, 0);
    }

    _deltaTime = deltaTime;
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
