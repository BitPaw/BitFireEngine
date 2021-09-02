#include "CleavedGameSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../ResourceSystem/Source/Time/StopWatch.h"
#include "../../ResourceSystem/Source/Shader/ShaderProgram.h"
#include "../../ResourceSystem/Source/Game/SkyBox.h"
#include "../../BitFireEngine/Source/UI/UIText.h"
#include "../../ResourceSystem/Source/Model/Model.h"
#include "../../ResourceSystem/Source/Math/Math.h"

BF::UIText* text;
//BF::Model* sphere;

BF::SkyBox* skybox;
BF::Model cube;

BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

Cleaved::CleavedGameSystem::CleavedGameSystem()
{
    GameSystem.SetCallBack(this);
}

float _deltaTime = 0;

void Cleaved::CleavedGameSystem::OnStartUp()
{
    BF::StopWatch stopwatch;

    stopwatch.Start();

    GameSystem.Resource.Load(worldShader, "Shader/WS.vert", "Shader/WS.frag");
    GameSystem.Resource.Load(hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");

    GameSystem.Resource.Load("Level/MainMenu.lev");
    GameSystem.Resource.Load(cube, "Model/Cube.obj");

    cube.ModelMatrix.Scale(10.0f);
    cube.EnablePhysics = true;
    GameSystem.Resource.Add(cube);

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
    GameSystem.Resource.Add(*text);

    printf("[i][Info] Loading took %.2fs\n", stopwatch.Stop());

    GameSystem.Resource.PrintContent(true);
}

void Cleaved::CleavedGameSystem::OnShutDown()
{

}

void Cleaved::CleavedGameSystem::OnUpdateGameLogic(float deltaTime)
{
    if (cube.ModelMatrix.CurrentPosition().Y <= 0)
    {
        //cube.ModelMatrix.Move(0, tcap, 0);
        cube.Velocity.Set(0, 90, 0);
    }

    _deltaTime = deltaTime;
}

void Cleaved::CleavedGameSystem::OnUpdateUI()
{
    sprintf_s(text->TextContent, "FPS: %4i", (BF::Math::Ceiling(1 / _deltaTime)));
    text->SetText(text->TextContent);
}
