#include "CleavedGameSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../SystemResource/Source/Time/StopWatch.h"
#include "../../SystemResource/Source/Shader/ShaderProgram.h"
#include "../../SystemResource/Source/Game/SkyBox.h"
#include "../../SystemResource/Source/Model/Model.h"
#include "../../SystemResource/Source/Math/Math.h"
#include "../../BitFireEngine/Source/UI/UIText.h"

BF::UIText* text;

BF::SkyBox skybox;

BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

Cleaved::CleavedGameSystem::CleavedGameSystem()
{
    GameSystem.SetCallBack(this);
}

using namespace BF;

float _deltaTime = 0;
 
Image _playerCharacterLuna;
Image _playerCharacterNyte;
Image _lamp;
Image _fireplace;
Image _sign;

void Cleaved::CleavedGameSystem::OnStartUp()
{
    GameSystem.Resource.Load(worldShader, "Shader/WS.vert", "Shader/WS.frag");
    GameSystem.Resource.Load(hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");

    GameSystem.Resource.Load
    (
        skybox,
        "Shader/SkyBox.vert",
        "Shader/SkyBox.frag",
        "Texture/SkyBox_Right.bmp",
        "Texture/SkyBox_Left.bmp",
        "Texture/SkyBox_Top.bmp",
        "Texture/SkyBox_Bottom.bmp",
        "Texture/SkyBox_Back.bmp",
        "Texture/SkyBox_Front.bmp"
    );

    
    //GameSystem.Resource.Load(_playerCharacterLuna, "Texture/bmp");
    //GameSystem.Resource.Load(_playerCharacterNyte, "Texture/bmp");
    //GameSystem.Resource.Load(_lamp, "Texture/Lamp_B.bmp");
    GameSystem.Resource.Load(_fireplace, "Texture/FirePlaace.bmp");
    GameSystem.Resource.Load(_sign, "Texture/Sign.bmp");


    text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    text->RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    GameSystem.Resource.Add(*text);    
}

void Cleaved::CleavedGameSystem::OnShutDown()
{

}

void Cleaved::CleavedGameSystem::OnUpdateGameLogic(float deltaTime)
{
    _deltaTime = deltaTime;
}

void Cleaved::CleavedGameSystem::OnUpdateInput(BF::InputContainer& input)
{
}

void Cleaved::CleavedGameSystem::OnUpdateUI()
{
   //sprintf_s(text->TextContent, "FPS: %4i", (BF::Math::Ceiling(1 / _deltaTime)));
   //text->SetText(text->TextContent);
}
