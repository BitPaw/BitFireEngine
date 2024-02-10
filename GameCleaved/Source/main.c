#include "main.h"

#include <OS/Console/PXConsole.h>


PXSprite pxChracterImageA;
PXSprite pxChracterImageB;

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
        PXEngineResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.CreateType = PXEngineCreateTypeSkybox;
        pxSkyBoxCreateEventData.SkyBox.SkyboxReference = &_skybox;
        pxSkyBoxCreateEventData.SkyBox.SkyBoxShaderVertex = "Shader/SkyBox_Vertex.glsl";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxShaderPixel = "Shader/SkyBox_Fragment.glsl";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureA = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureB = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureC = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureD = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureE = "Texture/MissingTexture.bmp";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureF = "Texture/MissingTexture.bmp";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSkyBoxCreateEventData);
    }



    //-----------------------------------------------------
    // Background
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &_backGround;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/BackGround.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.Position.Z = -0.5;
        pxSpriteCreateEventData.Sprite.Scaling.X = 2;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 2;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }



    //-----------------------------------------------------
    // Nyte
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &_playerCharacterNyte;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/Nyte.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.Position.X = 0.0f;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.8;
        pxSpriteCreateEventData.Sprite.Position.Z = 0.01;
        pxSpriteCreateEventData.Sprite.Scaling.X = 0.5;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.5;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }



    //-----------------------------------------------------
    // Theia
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &_playerCharacterLuna;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/Theia.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.Position.X = 1.80f;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.80f;
        pxSpriteCreateEventData.Sprite.Position.Z = 0.01;
        pxSpriteCreateEventData.Sprite.Scaling.X = 0.5f;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.5f;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }
    

    //-----------------------------------------------------
    // Sign
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &_sign;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/Sign.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.Position.X = -1.40f;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.80f;
        pxSpriteCreateEventData.Sprite.Position.Z = 0.3;
        pxSpriteCreateEventData.Sprite.Scaling.X = 0.6f;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.6f;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }


    //-----------------------------------------------------
    // Lamp
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &_lamp;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/LampB.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.Position.X = 1.20f;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.80f;
        pxSpriteCreateEventData.Sprite.Position.Z = 0.3;
        pxSpriteCreateEventData.Sprite.Scaling.X = 0.6f;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.6f;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }



    //-----------------------------------------------------
    // Dialog
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &pxDialogBox.DialogBoxSprite;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/Dialog.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.ViewPositionIgnore = 1;
        pxSpriteCreateEventData.Sprite.ViewRotationIgnore = 1;
        //pxSpriteCreateEventData.Position.X = 0;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.65;
        //pxSpriteCreateEventData.Position.Z = 0.02;
        pxSpriteCreateEventData.Sprite.Scaling.X = 1.6f;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.4f;
        pxSpriteCreateEventData.Sprite.TextureScalingPoints[0].X = 0.2 / pxSpriteCreateEventData.Sprite.Scaling.X;
        pxSpriteCreateEventData.Sprite.TextureScalingPoints[0].Y = 0.2 / pxSpriteCreateEventData.Sprite.Scaling.Y;
        pxSpriteCreateEventData.Sprite.TextureScalingPoints[1].X = 0.3;
        pxSpriteCreateEventData.Sprite.TextureScalingPoints[1].Y = 0.3;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }


    //-----------------------------------------------------
    // Font
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.CreateType = PXEngineCreateTypeFont;
        pxSkyBoxCreateEventData.Font.FontReference = &_font;
        pxSkyBoxCreateEventData.Font.FontFilePath = "Font/segoe.fnt";
        pxSkyBoxCreateEventData.Font.ShaderProgramCurrent = &_worldShader;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSkyBoxCreateEventData);
    }


    //-----------------------------------------------------
    // Dialog-Sprite
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &pxChracterImageA;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/en_upset.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.ViewRotationIgnore = 1;
        pxSpriteCreateEventData.Sprite.ViewPositionIgnore = 1;
        pxSpriteCreateEventData.Sprite.Position.X = -1.20f;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.65;
        pxSpriteCreateEventData.Sprite.Scaling.X = 0.25f;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.25f;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);

        pxDialogBox.DialogBoxCharacterImage = &pxChracterImageA;
    }
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.Sprite.SpriteReference = &pxChracterImageB;
        pxSpriteCreateEventData.Sprite.TextureName = "Texture/en_upset2.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = &_worldShader;
        pxSpriteCreateEventData.Sprite.ViewRotationIgnore = 1;
        pxSpriteCreateEventData.Sprite.ViewPositionIgnore = 1;
        pxSpriteCreateEventData.Sprite.Position.X = -1.20f;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.65;
        pxSpriteCreateEventData.Sprite.Scaling.X = 0.25f;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.25f;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }


    //-----------------------------------------------------
    // Dialog-Text
    //-----------------------------------------------------
    {
        PXTextMakeFixedGlobalA(&pxDialogBox.DialogBoxText.Text, "The world machine will be done soon.\nI hope it will be as good as i plan to.\n\nIt really is difficult.");
        pxDialogBox.DialogBoxText.Font = &_font;

        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeText;
        pxSpriteCreateEventData.Text.EngineTextReference = &pxDialogBox.DialogBoxText;
        pxDialogBox.DialogBoxText.Position.X = 0.57f;
        pxDialogBox.DialogBoxText.Position.Y = 0.60f;
        pxDialogBox.DialogBoxText.Scaling.X = 0.40f;
        pxDialogBox.DialogBoxText.Scaling.Y = 0.55f;
        pxDialogBox.DialogBoxText.DoubleRenderForShadow = PXTrue;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }



    //-----------------------------------------------------
    // Dialog-Text-Timer
    //-----------------------------------------------------
    {       
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeTimer;
        pxSpriteCreateEventData.Timer.TimerReference = &pxDialogBox.DialogBoxTextTimer;
       
        pxDialogBox.DialogBoxTextTimer.Owner = &pxDialogBox;
        pxDialogBox.DialogBoxTextTimer.CallBack = PXEngineDialogBoxTimerTrigger;
        pxDialogBox.DialogBoxTextTimer.TimeDeltaTarget = 1000000/2;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }



    //-----------------------------------------------------
    // Dialog-Text-Timer
    //-----------------------------------------------------00
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSound;
        pxSpriteCreateEventData.Sound.EngineSoundReference = &_dialogLetterPopSFX;
        pxSpriteCreateEventData.Sound.FilePath = "Audio/SFX/text.wav";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }


#if 0
    bitFireEngine->Engine.Audio.DevicePitchSet
    (
        &bitFireEngine->Engine.Audio,
        &bitFireEngine->Engine.AudioStandardOutDevice,
    1000
        );
#endif



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


    if (bitFireEngine->Engine.Window.KeyBoardCurrentInput.Letters & KeyBoardIDLetterF && !pxDialogBox.IsLocked)
    {
        pxDialogBox.IsLocked = PXTrue;

        if (pxDialogBox.DialogBoxText.TextRenderAmount < pxDialogBox.DialogBoxText.Text.SizeUsed)
        {
            ++pxDialogBox.DialogBoxText.TextRenderAmount;
        }
    } 
    if (!(bitFireEngine->Engine.Window.KeyBoardCurrentInput.Letters & KeyBoardIDLetterF))
    {
        pxDialogBox.IsLocked = PXFalse;
    }

}

void OnRenderUpdateEvent(BFEngine* const bitFireEngine, BFInputContainer* input)
{
    {
        PXEngineResourceRenderInfo pxEngineResourceRenderInfo;
        pxEngineResourceRenderInfo.Type = PXEngineCreateTypeSkybox;
        pxEngineResourceRenderInfo.CameraReference = bitFireEngine->Engine.CameraCurrent;
        pxEngineResourceRenderInfo.SkyBoxRender.SkyBoxReference = &_skybox;

        PXEngineResourceRender(&bitFireEngine->Engine, &pxEngineResourceRenderInfo);
    }


    // Sprite
    {
        PXDictionary* const spirteList = &bitFireEngine->Engine.SpritelLookUp;

        for (PXSize i = 0; i < spirteList->EntryAmountCurrent; ++i)
        {
            PXDictionaryEntry pxDictionaryEntry;
            PXSprite* pxSprite = PXNull;

            PXDictionaryIndex(spirteList, i, &pxDictionaryEntry);

            pxSprite = *(PXSprite**)pxDictionaryEntry.Value;


            PXEngineResourceRenderInfo pxEngineResourceRenderInfo;
            pxEngineResourceRenderInfo.Type = PXEngineCreateTypeSprite;
            pxEngineResourceRenderInfo.CameraReference = bitFireEngine->Engine.CameraCurrent;
            pxEngineResourceRenderInfo.SpriteRender.SpriteReference = pxSprite;

            PXEngineResourceRender(&bitFireEngine->Engine, &pxEngineResourceRenderInfo);
        }
    }

    // Text
    {
        PXDictionary* const textList = &bitFireEngine->Engine.TextLookUp;

        for (PXSize i = 0; i < textList->EntryAmountCurrent; ++i)
        {
            PXDictionaryEntry pxDictionaryEntry;
            PXEngineText* pxEngineText = PXNull;

            PXDictionaryIndex(textList, i, &pxDictionaryEntry);

            pxEngineText = *(PXEngineText**)pxDictionaryEntry.Value;

            PXEngineResourceRenderInfo pxEngineResourceRenderInfo;
            pxEngineResourceRenderInfo.Type = PXEngineCreateTypeText;
            pxEngineResourceRenderInfo.CameraReference = bitFireEngine->Engine.CameraCurrent;
            pxEngineResourceRenderInfo.TextRender.TextReference = pxEngineText;

            PXEngineResourceRender(&bitFireEngine->Engine, &pxEngineResourceRenderInfo);
        }
    }   
}