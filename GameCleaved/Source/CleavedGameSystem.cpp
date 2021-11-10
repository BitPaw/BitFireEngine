#include "CleavedGameSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../SystemResource/Source/Time/StopWatch.h"
#include "../../SystemResource/Source/Shader/ShaderProgram.h"
#include "../../SystemResource/Source/Game/SkyBox.h"
#include "../../SystemResource/Source/Model/Model.h"
#include "../../SystemResource/Source/Math/Math.h"
#include "../../SystemResource/Source/Math/Geometry/Shape/Rectangle.h"
#include "../../BitFireEngine/Source/UI/UIText.h"
#include "../../SystemResource/Source/Math/Geometry/Form/Cube.h"
#include "../../SystemResource/Source/Game/Sprite.h"
#include "../../SystemResource/Source/File/FileTemporary.h"



using namespace BF;

float _deltaTime = 0;

BF::UIText* text;

BF::SkyBox skybox;
BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

BF::Camera* _camera = nullptr;
BF::Sprite _playerCharacterLuna;
BF::Sprite _playerCharacterNyte;
BF::Sprite _lamp;
BF::Sprite _fireplace;
BF::Sprite _sign;
BF::Sprite _floor;

BF::Rectangle _rectangle;
BF::Cube _cube;

BF::Model _rectangleModel;
BF::Model _cubeBotlane;

bool moveCamera = false;

Cleaved::CleavedGameSystem::CleavedGameSystem()
{
    GameSystem.SetCallBack(this);
}

void Cleaved::CleavedGameSystem::OnStartUp()
{
    _camera = &GameSystem.Resource.MainCamera;

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

    _cubeBotlane.ConvertFrom(_cube.VertexList, _cube.VertexListSize, _cube.IndexList, _cube.IndexListSize, RenderMode::Square);
    _rectangleModel.ConvertFrom(_rectangle.VertexList, _rectangle.VertexListSize, _rectangle.IndexList, _rectangle.IndexListSize, RenderMode::Square);

    GameSystem.Resource.Add(_rectangleModel);
    GameSystem.Resource.Add(_cubeBotlane);

    _rectangleModel.MatrixModel.Move(0,5,0);
    _cubeBotlane.MatrixModel.Move(0, 3, 0);

    _rectangleModel.NameChange("Rectangle");
    _cubeBotlane.NameChange("Cube");
  
    
    _playerCharacterNyte.Set(10, 0, 0.4, "Sprite_Nyte", "Texture/Nyte.bmp");
    GameSystem.Resource.Add(_playerCharacterNyte);

    _fireplace.Set(20, 0, 0.2, "Sprite_FirePlace", "Texture/FirePlace.bmp");
    GameSystem.Resource.Add(_fireplace);

    _playerCharacterLuna.Set(23, 0, 0.5, "Sprite_Luna", "Texture/Luna.bmp");
    GameSystem.Resource.Add(_playerCharacterLuna);
    _playerCharacterLuna.MatrixModel.Scale(0.5);
   // GameSystem.Resource.Add(_playerCharacterLuna);
    _playerCharacterLuna.EnablePhysics = true;

    _sign.Set(24, 0, 0.1, "Sprite_Sign", "Texture/Sign.bmp");
    GameSystem.Resource.Add(_sign);

    _lamp.Set(25, 0, 0.3, "Sprite_Lamp", "Texture/Lamp_A.bmp");
    GameSystem.Resource.Add(_lamp);


    _floor.Set(0, 0, 0.0, "Floor", "Texture/Brick.bmp");
    _floor.Texture.ImageWrapSet(ImageWrap::Repeat);

    _floor.MatrixModel.Scale(200, 50, 1);   

     GameSystem.Resource.Add(_floor);  

     _floor.MatrixModel.Move(100, -63, 0);
    


    GameSystem.Resource.PrintContent(true);
    //text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    //text->RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    //GameSystem.Resource.Add(*text);

    _camera->Rotate(0,0);
    _camera->MatrixModel.Move(240,15,-60);
    _camera->CurrentRotation.Set(90, 0, 0);
    _camera->Rotate(0, 0);
    //_camera->MatrixModel.Rotate(90, 0, 0);

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
    KeyBoard& keyboard = input.KeyBoardInput;
    Mouse& mouse = input.MouseInput;
    Camera& camera = *_camera;
    Vector3<float> movementCamera;
    Vector3<float> movementCharacter;

    if (keyboard.Eight.IsPressed()) { movementCamera.Add(0, 1, 0); }
    if (keyboard.Four.IsPressed()) { movementCamera.Add(-1, 0, 0); }
    if (keyboard.Two.IsPressed()) { movementCamera.Add(0, -1, 0); }
    if (keyboard.Six.IsPressed()) { movementCamera.Add(1, 0, 0); }


    if (keyboard.W.IsPressed()) { movementCharacter.Add(0, 1, 0); }
    if (keyboard.A.IsPressed()) { movementCharacter.Add(-1, 0, 0); }
    if (keyboard.S.IsPressed()) { movementCharacter.Add(0, -1, 0); }
    if (keyboard.D.IsPressed()) { movementCharacter.Add(1, 0, 0); }
    if (keyboard.SpaceBar.IsPressed())
    {
        _playerCharacterLuna.Velocity.Add(0.0f, 6.0f, .0f);

        movementCharacter.Add(0, 1, 0);
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

        keyboard.F.Value = 0;
    }

    movementCharacter.X *= -1;  // Flip X-Axis

    _playerCharacterLuna.MatrixModel.Move(movementCharacter);
    _camera->MatrixModel.Move(movementCamera);
}

void Cleaved::CleavedGameSystem::OnUpdateUI()
{
  // sprintf_s(text->TextContent, "FPS: %4i", (BF::Math::Ceiling(1 / _deltaTime)));

  // printf("FPS: %4i", (BF::Math::Ceiling(1 / _deltaTime));

   // Vector4<float> position = _camera->MatrixModel.CurrentPosition();

   //printf("CamPos: <%f|%f|%f>\n", position.X, position.Y, position.Z);

   //text->SetText(text->TextContent);
}
