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
 
    bfEngine.OnStartUp = OnStartUpEvent;
    bfEngine.OnShutDown = OnShutDownEvent;
    bfEngine.Engine.OnUserUpdate = OnNetworkUpdate;
    bfEngine.OnNetworkUpdate = OnNetworkUpdate;
    bfEngine.OnGameUpdate = OnGameUpdateEvent;
    bfEngine.Engine.OnRenderUpdate = OnRenderUpdateEvent;

    PXEngineStart(&bfEngine.Engine);

    while (PXEngineIsRunning(&bfEngine.Engine))
    {
        PXEngineUpdate(&bfEngine.Engine);
    }

    PXEngineStop(&bfEngine.Engine);

    return EXIT_SUCCESS;
}

void OnNetworkUpdate(const BFEngine* bitFireEngine)
{
    //wsprintfW(_dialogBox.Content.TextContent, L"FPS: %4i", (PXMathCeiling(1 / _deltaTime)));

  //text.UpdateText();

// wsprintf_s(text.TextContent, "FPS: %4i", );

 // printf("FPS: %4i", (PXMathCeiling(1 / _deltaTime));

  // Vector4<float> position = _camera->MatrixModel.CurrentPosition();

  //printf("CamPos: <%f|%f|%f>\n", position.X, position.Y, position.Z);

  //text->SetText(text->TextContent);
}

void OnStartUpEvent(BFEngine* const bitFireEngine)
{
    PXGraphic* const pxGraphicContext = &bitFireEngine->Engine.Graphic;

    //PXWindowCursorCaptureMode(&bitFireEngine->WindowMain, PXWindowCursorLockAndHide);

    bitFireEngine->Engine.Graphic.Select(bitFireEngine->Engine.Graphic.EventOwner);


    //---<Setup>
    _simplex.ResourceID.PXID = -1;
    _worldShader.ResourceID.PXID = -1;
    _hudShaderID.ResourceID.PXID = -1;

    //PXGraphicBlendingMode(&bitFireEngine->WindowMain.GraphicInstance, PXBlendingModeOneToOne);
       
    pxGraphicContext->ShaderProgramCreateFromFileVPA(pxGraphicContext->EventOwner, &_hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");
    pxGraphicContext->ShaderProgramCreateFromFileVPA(pxGraphicContext->EventOwner, &_worldShader, "Shader/Object_Vertex.glsl", "Shader/Object_Fragment.glsl");
    pxGraphicContext->ShaderProgramCreateFromFileVPA(pxGraphicContext->EventOwner, &_simplex, "Shader/Simplex.vert", "Shader/Simplex.frag");
       




    //-----------------------------------------------------
    // SkyBox
    //-----------------------------------------------------
    {
        PXSkyBoxCreateEventData pxSkyBoxCreateEventData;
        PXClear(PXSkyBoxCreateEventData, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.SkyboxReference = &_skybox;
        pxSkyBoxCreateEventData.SkyBoxShaderVertex = "Shader/SkyBox_Vertex.glsl";
        pxSkyBoxCreateEventData.SkyBoxShaderPixel = "Shader/SkyBox_Fragment.glsl";
        pxSkyBoxCreateEventData.SkyBoxTextureA = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBoxTextureB = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBoxTextureC = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBoxTextureD = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBoxTextureE = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBoxTextureF = "Texture/MissingTexture.bmp";

        PXSkyBoxCreate(&bitFireEngine->Engine, &pxSkyBoxCreateEventData);
    }

    //-----------------------------------------------------
    // Background
    //-----------------------------------------------------
    {
        PXSpriteCreateEventData pxSpriteCreateEventData;
        PXClear(PXSpriteCreateEventData, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.SpriteReference = &_backGround;
        pxSpriteCreateEventData.TextureName = "Texture/BackGround.png";
        pxSpriteCreateEventData.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Scaling.X = 2;
        pxSpriteCreateEventData.Scaling.Y = 2;

        PXSpriteCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }


    //-----------------------------------------------------
    // Nyte
    //-----------------------------------------------------
    {
        PXSpriteCreateEventData pxSpriteCreateEventData;
        PXClear(PXSpriteCreateEventData, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.SpriteReference = &_playerCharacterNyte;
        pxSpriteCreateEventData.TextureName = "Texture/Nyte.png";
        pxSpriteCreateEventData.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Position.X = 0;
        pxSpriteCreateEventData.Position.Y = -0.8;
        pxSpriteCreateEventData.Position.Z = 0.01;
        pxSpriteCreateEventData.Scaling.X = 0.5;
        pxSpriteCreateEventData.Scaling.Y = 0.5;

        PXSpriteCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }
    

    //-----------------------------------------------------
    // Dialog
    //-----------------------------------------------------
    {
        PXSpriteCreateEventData pxSpriteCreateEventData;
        PXClear(PXSpriteCreateEventData, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.SpriteReference = &_dialogBox;
        pxSpriteCreateEventData.TextureName = "Texture/Dialog.png";
        pxSpriteCreateEventData.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.ViewPositionIgnore = 1;
        pxSpriteCreateEventData.ViewRotationIgnore = 1;
        //pxSpriteCreateEventData.Position.X = 0;
        pxSpriteCreateEventData.Position.Y = -0.65;
        //pxSpriteCreateEventData.Position.Z = 0.02;
        pxSpriteCreateEventData.Scaling.X = 1.6f;
        pxSpriteCreateEventData.Scaling.Y = 0.4f;
        pxSpriteCreateEventData.TextureScalingPoints[0].X = 0.2 / pxSpriteCreateEventData.Scaling.X;
        pxSpriteCreateEventData.TextureScalingPoints[0].Y = 0.2 / pxSpriteCreateEventData.Scaling.Y;
        pxSpriteCreateEventData.TextureScalingPoints[1].X = 0.3;
        pxSpriteCreateEventData.TextureScalingPoints[1].Y = 0.3;

        PXSpriteCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }

   



    //-----------------------------------------------------
    // Sign
    //-----------------------------------------------------
    {
        PXSpriteCreateEventData pxSpriteCreateEventData;
        PXClear(PXSpriteCreateEventData, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.SpriteReference = &_sign;
        pxSpriteCreateEventData.TextureName = "Texture/Sign.png";
        pxSpriteCreateEventData.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Position.X = -1.40f;
        pxSpriteCreateEventData.Position.Y = -0.80f;
        pxSpriteCreateEventData.Scaling.X = 0.6f;
        pxSpriteCreateEventData.Scaling.Y = 0.6f;

        PXSpriteCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }


    //-----------------------------------------------------
    // Lamp
    //-----------------------------------------------------
    {
        PXSpriteCreateEventData pxSpriteCreateEventData;
        PXClear(PXSpriteCreateEventData, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.SpriteReference = &_lamp;
        pxSpriteCreateEventData.TextureName = "Texture/LampB.png";
        pxSpriteCreateEventData.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Position.X = -1.80f;
        pxSpriteCreateEventData.Position.Y = -0.80f;
        pxSpriteCreateEventData.Scaling.X = 1;
        pxSpriteCreateEventData.Scaling.Y = 1;

        PXSpriteCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }





#if 0

  
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
    
  //  bitFireEngine->CameraCurrent->FollowSpeed = 1;

}
void OnShutDownEvent(const BFEngine* bitFireEngine)
{

}
void OnGameUpdateEvent(const BFEngine* bitFireEngine, const float deltaTime)
{
    //PXCameraFollow(bitFireEngine->Engine.CameraCurrent, deltaTime);

    PXText pxText;
    PXTextConstructBufferW(&pxText, 64);

    PXTextClear(&pxText);

    PXTextPrint(&pxText, L"[Cleaved] FPS:%5.2f, ms:%4.2f", bitFireEngine->Engine.FramesPerSecound, bitFireEngine->Engine.FrameTime);

    PXWindowTitleSet(&bitFireEngine->Engine.Window, &pxText);
}

void OnRenderUpdateEvent(BFEngine* const bitFireEngine, BFInputContainer* input)
{

    PXOpenGLSkyboxDraw(&bitFireEngine->Engine.Graphic.OpenGLInstance, bitFireEngine->DefaultSkyBox, bitFireEngine->Engine.CameraCurrent);


    PXDictionary* const spirteList = &bitFireEngine->Engine.Graphic.SpritelLookUp;

    for (PXSize i = 0; i < spirteList->EntryAmountCurrent; ++i)
    {
        PXDictionaryEntry pxDictionaryEntry;
        PXSprite* pxSprite = PXNull;

        PXDictionaryIndex(spirteList, i, &pxDictionaryEntry);

        pxSprite = *(PXSprite**)pxDictionaryEntry.Value;

        PXGraphicSpriteDraw(&bitFireEngine->Engine.Graphic, pxSprite, bitFireEngine->Engine.CameraCurrent);
    }  
}