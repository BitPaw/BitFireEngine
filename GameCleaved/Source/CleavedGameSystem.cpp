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
#include "../../SystemResource/Source/Math/Physic/GravityCube.h"
#include "../../BitFireEngine/Source/Entity/Sign.h"
#include "../../BitFireEngine/Source/UI/DialogBox/UIDialogBox.h"

using namespace BF;

float _deltaTime = 0;

BF::FNT fnt;
BF::Font font;

BF::SkyBox skybox;
BF::ShaderProgram worldShader;
BF::ShaderProgram hudShaderID;

BF::GravityCube _gravityField;

BF::Camera* _camera = nullptr;
BF::Sprite _playerCharacterLuna;
BF::Sprite _backGround;
BF::Sprite _playerCharacterNyte;
BF::Sprite _lamp;
BF::Sprite _fireplace;
BF::Sign _sign;
BF::Sprite _floor;

BF::UIDialogBox _dialogBox;

bool moveCamera = false;

Cleaved::CleavedGameSystem::CleavedGameSystem()
{
    GameSystem.SetCallBack(this);
}

void Cleaved::CleavedGameSystem::OnStartUp()
{
    _camera = &GameSystem.Resource.MainCamera;

    GameSystem.Resource.Load(worldShader, L"Shader/WS.vert", L"Shader/WS.frag");
    GameSystem.Resource.Load(hudShaderID, L"Shader/HUD.vert", L"Shader/HUD.frag");
    
    GameSystem.Resource.Load(GameSystem.Resource.ShaderHitBox, L"Shader/HitBox.vert", L"Shader/HitBox.frag");

    GameSystem.Resource.Load
    (
        skybox,
        L"Shader/SkyBox.vert",
        L"Shader/SkyBox.frag",
        L"Texture/SkyBox_Side.png",
        L"Texture/SkyBox_Side.png",
        L"Texture/SkyBox_Top.png",
        L"Texture/SkyBox_Bottom.png",
        L"Texture/SkyBox_Side.png",
        L"Texture/SkyBox_Side.png"
    ); 





    // Gravity
    _gravityField.PullForce = -GravityForceEarth * 0.001;
    _gravityField.PullDirection.Set(0, -1, 0);
    _gravityField.BoundingBox.Set(170, 0, 30, 70);
    GameSystem.Resource.Add(&_gravityField);

    _backGround.Set(13.5, -0.2, -5, "Sprite_backGround", "Texture/BackGround.png");
    _backGround.MatrixModel.Scale(12);
    GameSystem.Resource.Add(_backGround);



#if 1
   // _fireplace.Set(20, 0, 0.2, "Sprite_FirePlace", "Texture/Fireplace.png");
   // GameSystem.Resource.Add(_fireplace);

    _lamp.Set(26, 0.008, 0.3, "Sprite_Lamp", "Texture/LampA.png");
    GameSystem.Resource.Add(_lamp); 

    _sign.Set(24, 0, 0.1, "Sprite_Sign", "Texture/Sign.png");
    _sign.Type = ColliderType::EffectBox;
    GameSystem.Resource.Add(_sign);

    _floor.Set(10, -2, 0.0, "Floor", "Texture/Brick.bmp");
    _floor.MaterialList[0].Texture->ImageWrapSet(ImageWrap::Repeat);
    _floor.MatrixModel.Scale(200, 20, 1);   
   // _floor.MatrixModel.Move(100, -83, 0);
    GameSystem.Resource.Add(_floor);        
#endif 

    _playerCharacterNyte.Set(10, 0, 0.4, "Sprite_Nyte", "Texture/Nyte.png");
    _playerCharacterNyte.MatrixModel.Scale(0.5);
    GameSystem.Resource.Add(_playerCharacterNyte);

    _playerCharacterLuna.Set(23, 0, 0.5, "Sprite_Luna", "Texture/Theia.png");
    _playerCharacterLuna.MatrixModel.Scale(0.5);
    _playerCharacterLuna.EnablePhysics = true;
    GameSystem.Resource.Add(_playerCharacterLuna);
    //GameSystem.Resource.Add(_playerCharacterLuna);


#if 1
    BF::Cube cube;

    GameSystem.Resource.CubeHitBoxViewModel.ConvertFrom(cube.VertexList, cube.VertexListSize, cube.IndexList, cube.IndexListSize, RenderMode::Square);
    GameSystem.Resource.CubeHitBoxViewModel.NameChange("Cube-HitBoxView");

    GameSystem.Resource.PushToGPU(GameSystem.Resource.CubeHitBoxViewModel);
#endif // 1

 






    

    //---<DialogBox>-----------------------------------------------------------


    _dialogBox.BackGroundTexture.Set(-0.07f, -0.05f, 0, "DialogBoxBorder", "Texture/DialogBoxBorder.png");
    GameSystem.Resource.Add(_dialogBox.BackGroundTexture);
    _dialogBox.BackGroundTexture.MeshList[0].RenderInfo.ShaderProgramID = hudShaderID.ID;


    GameSystem.Resource.Load(font, L"Font/harrington.fnt");
    _dialogBox.Content.SetFont(font);
    _dialogBox.Content.SetText("Soon...");
    _dialogBox.Content.MatrixModel.Scale(1);
    _dialogBox.Content.MatrixModel.MoveTo(-0.3, 0.0025, -1);
    _dialogBox.Content.UpdateText();
    GameSystem.Resource.Add(_dialogBox.Content);
    GameSystem.Resource.PushToGPU(_dialogBox.Content);
    _dialogBox.Content.MeshList[0].RenderInfo.ShaderProgramID = hudShaderID.ID;

    //-------------------------------------------------------------------------



    GameSystem.Resource.PrintContent(true);
    //text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    //text->RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    //GameSystem.Resource.Add(*text);

    _camera->Rotate(0,0);
    _camera->MatrixModel.Move(240,15,60);
    _camera->CurrentRotation.Set(-90, 0, 0);
    _camera->Move(Vector3<float>(0, 0, -60));
    _camera->Rotate(0, 0);
    //_camera->MatrixModel.Rotate(90, 0, 0);


    _camera->Target = &_playerCharacterLuna.MatrixModel;
    _camera->Offset.Set(0, 20, 60);
    _camera->FollowSpeed = 1;
}

void Cleaved::CleavedGameSystem::OnShutDown()
{

}

void Cleaved::CleavedGameSystem::OnUpdateGameLogic(float deltaTime)
{
    _deltaTime = deltaTime;

    _camera->Follow(deltaTime);
}

void Cleaved::CleavedGameSystem::OnUpdateInput(BF::InputContainer& input)
{
#if 1
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

    if (keyboard.F.IsShortPressed())
    {
        keyboard.F.Value = 0xFF;

        if (_sign.Interactable)
        {
            printf("[Event] Clicked Sign\n");
        }
    }

    _playerCharacterLuna.MatrixModel.Move(movement);

    //camera.Move(movement);

    camera.Rotate(mouse.InputAxis[0], mouse.InputAxis[1]);

    camera.Update(_deltaTime);
    keyboard.IncrementButtonTick();
    mouse.ResetAxis();
#else
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

    //_camera->MatrixModel.Move(movementCharacter);
    _playerCharacterLuna.MatrixModel.Move(movementCharacter);
    //_camera->MatrixModel.Move(movementCamera);
#endif // 1


    

 
}

void Cleaved::CleavedGameSystem::OnUpdateUI()
{
    wsprintfW(_dialogBox.Content.TextContent, L"FPS: %4i", (BF::Math::Ceiling(1 / _deltaTime)));

    //text.UpdateText();

 // wsprintf_s(text.TextContent, "FPS: %4i", );

  // printf("FPS: %4i", (BF::Math::Ceiling(1 / _deltaTime));

   // Vector4<float> position = _camera->MatrixModel.CurrentPosition();

   //printf("CamPos: <%f|%f|%f>\n", position.X, position.Y, position.Z);

   //text->SetText(text->TextContent);
}