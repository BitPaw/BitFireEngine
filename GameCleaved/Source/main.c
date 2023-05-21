#include "main.h"

#if !defined(_DEBUG) && defined(OSWindowsE)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif
{
    BFEngine bfEngine;
    BFEngineConstruct(&bfEngine);

    bfEngine.UpdateUICallBack = OnUpdateUI;
    bfEngine.StartUpCallBack = OnStartUp; // StartDoc
    bfEngine.ShutDownCallBack = OnShutDown;
    bfEngine.UpdateGameLogicCallBack = OnUpdateGameLogic;
    bfEngine.UpdateInputCallBack = OnUpdateInput;

    BFEngineStart(&bfEngine);

    while (BFEngineIsRunning(&bfEngine))
    {
        BFEngineUpdate(&bfEngine);
    }

    BFEngineStop(&bfEngine);

    return EXIT_SUCCESS;
}

void OnUpdateUI(const BFEngine* bitFireEngine)
{
    //wsprintfW(_dialogBox.Content.TextContent, L"FPS: %4i", (PXMathCeiling(1 / _deltaTime)));

  //text.UpdateText();

// wsprintf_s(text.TextContent, "FPS: %4i", );

 // printf("FPS: %4i", (PXMathCeiling(1 / _deltaTime));

  // Vector4<float> position = _camera->MatrixModel.CurrentPosition();

  //printf("CamPos: <%f|%f|%f>\n", position.X, position.Y, position.Z);

  //text->SetText(text->TextContent);
}
void OnStartUp(BFEngine* const bitFireEngine)
{
    PXCameraConstruct(&bitFireEngine->MainCamera);

    PXWindowCursorCaptureMode(&bitFireEngine->WindowMain, PXWindowCursorLockAndHide);

    //---<Setup>
    _simplex.ID = -1;
    _worldShader.ID = -1;
    _hudShaderID.ID = -1;



    //---<Load>
    {
        PXText vertexShader;
        PXTextMakeFixedNamedA(&vertexShader, vertexShaderBuffer, "Shader/WS.vert");

        PXText fragmentShader;
        PXTextMakeFixedNamedA(&fragmentShader, fragmentShaderBuffer, "Shader/WS.frag");

        PXGraphicShaderProgramLoadGLSL(&bitFireEngine->WindowMain.GraphicInstance, &_worldShader, &vertexShader, &fragmentShader);
    }


    {
        PXText vertexShader;
        PXTextMakeFixedNamedA(&vertexShader, vertexShaderBuffer, "Shader/HUD.vert");

        PXText fragmentShader;
        PXTextMakeFixedNamedA(&fragmentShader, fragmentShaderBuffer, "Shader/HUD.frag");

        PXGraphicShaderProgramLoadGLSL(&bitFireEngine->WindowMain.GraphicInstance, &_hudShaderID, &vertexShader, &fragmentShader);
    }

    {
        PXText vertexShader;
        PXTextMakeFixedNamedA(&vertexShader, vertexShaderBuffer, "Shader/Simplex.vert");

        PXText fragmentShader;
        PXTextMakeFixedNamedA(&fragmentShader, fragmentShaderBuffer, "Shader/Simplex.frag");

        PXGraphicShaderProgramLoadGLSL(&bitFireEngine->WindowMain.GraphicInstance, &_simplex, &vertexShader, &fragmentShader);
    }

    //  //GameSystem.Load(GameSystem.ShaderHitBox, L"Shader/HitBox.vert", L"Shader/HitBox.frag");




    {

        PXText shaderVertex;
        PXText shaderFragment;
        PXText textureRight;
        PXText textureLeft;
        PXText textureTop;
        PXText textureBottom;
        PXText textureBack;
        PXText textureFront;

        PXTextMakeFixedNamedA(&shaderVertex, shaderVertexBuffer, "Shader/SkyBox.vert");
        PXTextMakeFixedNamedA(&shaderFragment, shaderFragmentBuffer, "Shader/SkyBox.frag");

        PXTextMakeFixedNamedA(&textureRight, textureRightBuffer, "Texture/SkyBox_Side.png");
        PXTextMakeFixedNamedA(&textureLeft, textureLeftBuffer, "Texture/SkyBox_Side.png");
        PXTextMakeFixedNamedA(&textureTop, textureTopBuffer, "Texture/SkyBox_Top.png");
        PXTextMakeFixedNamedA(&textureBottom, textureBottomBuffer, "Texture/SkyBox_Bottom.png");
        PXTextMakeFixedNamedA(&textureBack, textureBackBuffer, "Texture/SkyBox_Side.png");
        PXTextMakeFixedNamedA(&textureFront, textureFrontBuffer, "Texture/SkyBox_Side.png");

        PXGraphicSkyboxRegisterD
        (
            &bitFireEngine->WindowMain.GraphicInstance,
            &_skybox,
            &shaderVertex,
            &shaderFragment,
            &textureRight,
            &textureLeft,
            &textureTop,
            &textureBottom,
            &textureBack,
            &textureFront
        );

    }





#if 0

  

    bitFireEngine->Load
    (
        _skybox,
        L"Shader/SkyBox.vert",
        L"Shader/SkyBox.frag",
        L"Texture/SkyBox_Side.png",
        L"Texture/SkyBox_Side.png",
        L"Texture/SkyBox_Top.png",
        L"Texture/SkyBox_Bottom.png",
        L"Texture/SkyBox_Side.png",
        L"Texture/SkyBox_Side.png"
    );

    bitFireEngine->Load(testTextue, L"Texture/SkyBox.bmp", false);

    // PXCube cube;

     //GameSystem.Resource.Add(_cubeRenderable, cube.VertexList, cube.VertexListSize, cube.IndexList, cube.IndexListSize);

     // Test-Cube
    {
        bitFireEngine->MakeRectangle(_rectangleMesh);

        _rectangleMesh.ShaderUse(_simplex);
        _rectangleMesh.TextureUse(testTextue.ID);
        //_cubeRenderable.ChunkList[0].SegmentList[0].TextureType = ImageType::Texture2D;
    }

    _backGround.Scale(12);
    _backGround.MoveTo(13.5, -0.2, -5);
    _backGround.ShaderUse(_simplex);
    _backGround.MeshShare(_rectangleMesh);
    bitFireEngine->Load(_backGround, L"Texture/BackGround.png");

    _lamp.MoveTo(120, 12, 0.3);
    _lamp.ShaderUse(_simplex);
    _lamp.MeshShare(_rectangleMesh);
    bitFireEngine->Load(_lamp, L"Texture/LampA.png");

    _sign.MoveTo(110, 12, 0.1);
    _sign.ShaderUse(_simplex);
    _sign.MeshShare(_rectangleMesh);
    bitFireEngine->Load(_sign, L"Texture/Sign.png");
    //_sign.Type = ColliderType::EffectBox;

    _floor.MoveTo(10, -7, 0);
    _floor.Scale(200, 20, 1);
    _floor.ShaderUse(_simplex);
    _floor.MeshShare(_rectangleMesh);
    bitFireEngine->Load(_floor, L"Texture/MissingTexture.bmp");
    _floor.UsedTexture->TextureWrap(ImageWrap::Repeat);

    _playerCharacterNyte.Scale(0.5);
    _playerCharacterNyte.MoveTo(100, 12, 0.3);
    _playerCharacterNyte.ShaderUse(_simplex);
    _playerCharacterNyte.MeshShare(_rectangleMesh);
    bitFireEngine->Load(_playerCharacterNyte, L"Texture/Nyte.png");

    _playerCharacterLuna.Scale(0.5);
    _playerCharacterLuna.MoveTo(123, 12, 0.1);
    _playerCharacterLuna.ShaderUse(_simplex);
    _playerCharacterLuna.MeshShare(_rectangleMesh);
    bitFireEngine->Load(_playerCharacterLuna, L"Texture/Theia.png");

    // _playerCharacterLuna.EnablePhysics = true;








    _menuButtonA.MeshShare(_rectangleMesh);
    _menuButtonA.ShaderUse(_hudShaderID);
    _menuButtonA.ScaleSet(0.2f, 0.1f, 1);
    _menuButtonA.MoveTo(-0.9, -0.6, -0.1);
    bitFireEngine->Load(_menuButtonA, L"Texture/Button.png"); //DialogBoxBorder

   // _buttonTextA.SetText();



    _menuButtonB.MeshShare(_rectangleMesh);
    _menuButtonB.ShaderUse(_hudShaderID);
    _menuButtonB.ScaleSet(0.2f, 0.1f, 1);
    _menuButtonB.MoveTo(-0.9, -0.7, -0.1);
    bitFireEngine->Load(_menuButtonB, L"Texture/Button.png"); //DialogBoxBorder

    _menuButtonC.MeshShare(_rectangleMesh);
    _menuButtonC.ShaderUse(_hudShaderID);
    _menuButtonC.ScaleSet(0.2f, 0.1f, 1);
    _menuButtonC.MoveTo(-0.9, -0.8, -0.1);
    bitFireEngine->Load(_menuButtonC, L"Texture/Button.png"); //DialogBoxBorder



       // Make Rectangle
    _menuFrame.MeshShare(_rectangleMesh);
    _menuFrame.ShaderUse(_hudShaderID);
    _menuFrame.ScaleSet(0.25, 0.25f, 1);
    _menuFrame.MoveTo(-1, -1, 0);
    bitFireEngine->Load(_menuFrame, L"Texture/SkyBox_Bottom.png"); //DialogBoxBorder



   /*


    // Gravity
    _gravityField.PullForce = -GravityForceEarth * 0.001;
    _gravityField.PullDirection.Set(0, -1, 0);
    _gravityField.BoundingBox.Set(170, 0, 30, 70);
    GameSystem.Resource.Add(&_gravityField);


#if 1
   // _fireplace.Set(20, 0, 0.2, "Sprite_FirePlace", "Texture/Fireplace.png");
   // GameSystem.Resource.Add(_fireplace);



    _floor.Set(10, -2, 0.0, "Floor", "Texture/Brick.bmp");
    _floor.MaterialList[0].Texture->ImageWrapSet(ImageWrap::Repeat);
    _floor.MatrixModel.Scale(200, 20, 1);
   // _floor.MatrixModel.Move(100, -83, 0);
    GameSystem.Resource.Add(_floor);
#endif




#if 1
    PXCube cube;

    GameSystem.Resource.CubeHitBoxViewModel.ConvertFrom(cube.VertexList, cube.VertexListSize, cube.IndexList, cube.IndexListSize, RenderMode::Square);
    GameSystem.Resource.CubeHitBoxViewModel.NameChange("Cube-HitBoxView");

    GameSystem.Resource.PushToGPU(GameSystem.Resource.CubeHitBoxViewModel);
#endif // 1





    //---<DialogBox>-----------------------------------------------------------


    _dialogBox.BackGroundTexture.Set(-0.07f, -0.05f, 0, "DialogBoxBorder", "Texture/DialogBoxBorder.png");
    GameSystem.Resource.Add(_dialogBox.BackGroundTexture);
    _dialogBox.BackGroundTexture.MeshList[0].RenderInfo.ShaderProgramID = hudShaderID.ID;


    GameSystem.Resource.Add(font, L"Font/harrington.fnt");
    _dialogBox.Content.SetFont(font);
    _dialogBox.Content.SetText("Text...");
    _dialogBox.Content.MatrixModel.Scale(1);
    _dialogBox.Content.MatrixModel.MoveTo(-0.3, -0.5, -1);
    _dialogBox.BackGroundTexture.MatrixModel.Scale(1, 0.75, 1);
    _dialogBox.BackGroundTexture.MatrixModel.Move(0, -0.5, 0);
    _dialogBox.Content.UpdateText();
    GameSystem.Resource.Add(_dialogBox.Content);
    GameSystem.Resource.PushToGPU(_dialogBox.Content);
    _dialogBox.Content.MeshList[0].RenderInfo.ShaderProgramID = hudShaderID.ID;*/

    //-------------------------------------------------------------------------

    bitFireEngine->PrintContent(true);
#endif
    //text = new PXUIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
    //text->RenderInformation.ShaderProgramID = hudShaderID.ID;
    //text->SetFont(*Resource.DefaultFont);
    //GameSystem.Resource.Add(*text);

 

    //PXCameraRotate(&bitFireEngine->MainCamera, 0, 0);
    //PXCameraMove(&bitFireEngine->MainCamera, 240, 15, 60);
    //  _camera->CurrentRotation.Set(-90, 0, 0);
    //PXCameraMove(&bitFireEngine->MainCamera,Vector3F(0, 0, -60));
    //PXCameraRotate(&bitFireEngine->MainCamera, 0, 0);
    //_camera->MatrixModel.Rotate(90, 0, 0);


    // _camera->Target = &_playerCharacterLuna.MatrixModel;
   // _camera->Offset.Set(0, 20, 60);
    bitFireEngine->MainCamera.FollowSpeed = 1;

}
void OnShutDown(const BFEngine* bitFireEngine)
{

}
void OnUpdateGameLogic(const BFEngine* bitFireEngine, const float deltaTime)
{
    _deltaTime = deltaTime;

    PXCameraFollow(&bitFireEngine->MainCamera, deltaTime);


    char buffer[64];
    PXText pxText;

    int bufferSize = sprintf_s(buffer, 64, "[BitFireEngine] FPS:%5.2f, ms:%4.2f", bitFireEngine->TimeFPS, bitFireEngine->TimeMS);
    PXTextMakeExternA(&pxText, buffer, bufferSize);


    PXWindowTitleSet(&bitFireEngine->WindowMain, &pxText);

}
void OnUpdateInput(BFEngine* const bitFireEngine, BFInputContainer* input)
{
#if 1
    PXWindow* pxWindow = &bitFireEngine->WindowMain;
    PXKeyBoard* keyboard = &input->KeyBoardInput;
    PXMouse* mouse = &input->MouseInput;
    PXCamera* camera = &bitFireEngine->MainCamera;
    PXVector3F movement = {0,0,0};

    if (PXKeyBoardKeyPressedGet(keyboard, KeyShiftLeft)) { PXVector3FAddXYZ(&movement, 0, -1, 0, &movement); }
    if (PXKeyBoardKeyPressedGet(keyboard, KeyW)) { PXVector3FAddXYZ(&movement, 0, 0, 1, &movement); }
    if (PXKeyBoardKeyPressedGet(keyboard, KeyS)) { PXVector3FAddXYZ(&movement, -1, 0, 0, &movement); }
    if (PXKeyBoardKeyPressedGet(keyboard, KeyA)) { PXVector3FAddXYZ(&movement, 0, 0, -1, &movement); }
    if (PXKeyBoardKeyPressedGet(keyboard, KeyD)) { PXVector3FAddXYZ(&movement, 1, 0, 0, &movement); }
    if (PXKeyBoardKeyPressedGet(keyboard, KeySpace))
    {


      //  PXCamera.Velocity.Set(0.0f, 6.0f, .0f);

        PXVector3FAddXYZ(&movement, 0, 1, 0, &movement);

    }
#if 0
    if (keyboard.F.IsShortPressed())
    {
        keyboard.F.Value = 0xFF;

        if (_sign.Interactable)
        {
            printf("[Event] Clicked Sign\n");
        }
    }
#endif

    //_playerCharacterLuna.MatrixModel.Move(movement);

    if(PXWindowInteractable(pxWindow) || 1)
    {
       // PXCameraMove(camera, &movement);

        PXVector3F mouseMovement = { mouse->Delta[0], mouse->Delta[1], 0};

       // printf("[#][OnMouseMove] X:%5.2f Y:%5.2f\n", mouseMovement.X, mouseMovement.Y);

        PXCameraRotate(camera, &mouseMovement);
    }

    //printf("[#][OnMouseMove] X:%5.2f Y:%5.2f\n", mouse.Position[0], mouse.Position[1]);

    PXCameraUpdate(camera, _deltaTime);    
   // PXKeyboardIncrementButtonTick(keyboard);
    PXMouseInputReset(mouse);
#else
    KeyBoard& keyboard = input.KeyBoardInput;
    Mouse& mouse = input.MouseInput;
    Camera& camera = *_camera;
    Vector3<float> movementCamera;
    Vector3<float> movementCharacter;

    if(keyboard.Eight.IsPressed()) { movementCamera.Add(0, 1, 0); }
    if(keyboard.Four.IsPressed()) { movementCamera.Add(-1, 0, 0); }
    if(keyboard.Two.IsPressed()) { movementCamera.Add(0, -1, 0); }
    if(keyboard.Six.IsPressed()) { movementCamera.Add(1, 0, 0); }


    if(keyboard.W.IsPressed()) { movementCharacter.Add(0, 1, 0); }
    if(keyboard.A.IsPressed()) { movementCharacter.Add(-1, 0, 0); }
    if(keyboard.S.IsPressed()) { movementCharacter.Add(0, -1, 0); }
    if(keyboard.D.IsPressed()) { movementCharacter.Add(1, 0, 0); }
    if(keyboard.SpaceBar.IsPressed())
    {
        _playerCharacterLuna.Velocity.Add(0.0f, 6.0f, .0f);

        movementCharacter.Add(0, 1, 0);
    }

    if(keyboard.F.IsLongPressed())
    {
        switch(camera.Perspective)
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
