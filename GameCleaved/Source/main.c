#include "main.h"

#include <OS/Console/PXConsole.h>


PXSprite* pxChracterFace = 0;

PXTexture2D* pxChracterImageA = 0;
PXTexture2D* pxChracterImageB = 0;
PXTexture2D* pxChracterImageC = 0;
PXTexture2D* pxChracterImageD = 0;


PXDialogMessagePage _pxDialogMessagePage[4];



void PXAPI OnIntereact(void* const owner, PXEngine* const pxEngine);

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
    bfEngine.Engine.OnInteract = OnIntereact;

    PXEngineStart(&bfEngine.Engine);

    while (PXEngineIsRunning(&bfEngine.Engine))
    {
        PXEngineUpdate(&bfEngine.Engine);
    }

    PXEngineStop(&bfEngine.Engine);

    return EXIT_SUCCESS;
}

void PXAPI OnIntereact(void* const owner, PXEngine* const pxEngine)
{
    if (!pxDialogBox.IsLocked)
    {
        pxDialogBox.IsLocked = PXTrue;

        PXEngineDialogBoxOpen(pxEngine, &pxDialogBox, _pxDialogMessagePage, 4);
    }
    else
    {
        PXEngineDialogBoxPageNext(pxEngine, &pxDialogBox);
    }

    Sleep(1);
}

void PXAPI OnNetworkUpdate(const BFEngine* bitFireEngine)
{
    //wsprintfW(_dialogBox.Content.TextContent, L"FPS: %4i", (PXMathCeiling(1 / _deltaTime)));

  //text.UpdateText();

// wsprintf_s(text.TextContent, "FPS: %4i", );

 // printf("FPS: %4i", (PXMathCeiling(1 / _deltaTime));

  // Vector4<float> position = _camera->MatrixModel.CurrentPosition();

  //printf("CamPos: <%f|%f|%f>\n", position.X, position.Y, position.Z);

  //text->SetText(text->TextContent);
}

void PXAPI OnStartUpEvent(BFEngine* const bitFireEngine)
{
    PXGraphic* const pxGraphicContext = &bitFireEngine->Engine.Graphic;

    //PXWindowCursorCaptureMode(&bitFireEngine->WindowMain, PXWindowCursorLockAndHide);


    //-----------------------------------------------------
    // Object Shader
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxEngineResourceCreateInfo;
        PXClear(PXEngineResourceCreateInfo, &pxEngineResourceCreateInfo);
        pxEngineResourceCreateInfo.CreateType = PXEngineCreateTypeShaderProgram;
        pxEngineResourceCreateInfo.ObjectReference = &_worldShader;
        pxEngineResourceCreateInfo.ShaderProgram.VertexShaderFilePath = "Shader/Object_Vertex.glsl";
        pxEngineResourceCreateInfo.ShaderProgram.PixelShaderFilePath = "Shader/Object_Fragment.glsl";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxEngineResourceCreateInfo);
    }

    //-----------------------------------------------------
    // SkyBox
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.CreateType = PXEngineCreateTypeSkybox;
        pxSkyBoxCreateEventData.SpawnEnabled = PXTrue;
        pxSkyBoxCreateEventData.ObjectReference = &_skybox;
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
        pxSpriteCreateEventData.SpawnEnabled = PXTrue;
        pxSpriteCreateEventData.ObjectReference = &_backGround;
        pxSpriteCreateEventData.FilePath = "Texture/BackGround.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = _worldShader;
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
        pxSpriteCreateEventData.SpawnEnabled = PXTrue;
        pxSpriteCreateEventData.ObjectReference = &_playerCharacterNyte;
        pxSpriteCreateEventData.FilePath = "Texture/Nyte.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = _worldShader;
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
        pxSpriteCreateEventData.SpawnEnabled = PXTrue;
        pxSpriteCreateEventData.ObjectReference = &_playerCharacterLuna;
        pxSpriteCreateEventData.FilePath = "Texture/Theia.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = _worldShader;
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
        pxSpriteCreateEventData.SpawnEnabled = PXTrue;
        pxSpriteCreateEventData.ObjectReference = &_sign;
        pxSpriteCreateEventData.FilePath = "Texture/Sign.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = _worldShader;
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
        pxSpriteCreateEventData.SpawnEnabled = PXTrue;
        pxSpriteCreateEventData.ObjectReference = &_lamp;
        pxSpriteCreateEventData.FilePath = "Texture/LampB.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = _worldShader;
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
        PXClear(PXEngineDialogBox, &pxDialogBox);

        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.SpawnEnabled = PXFalse;
        pxSpriteCreateEventData.ObjectReference = &pxDialogBox.DialogBoxSprite;
        pxSpriteCreateEventData.FilePath = "Texture/Dialog.png";
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = _worldShader;
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
        pxSkyBoxCreateEventData.ObjectReference = &_font;
        pxSkyBoxCreateEventData.FilePath = "Font/segoe.fnt";
        pxSkyBoxCreateEventData.Font.ShaderProgramCurrent = _worldShader;

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSkyBoxCreateEventData);
    }



    //-----------------------------------------------------
    // Dialog-Sprite
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeSprite;
        pxSpriteCreateEventData.SpawnEnabled = PXFalse;
        pxSpriteCreateEventData.ObjectReference = &pxChracterFace;
        pxSpriteCreateEventData.Sprite.ShaderProgramCurrent = _worldShader;
        pxSpriteCreateEventData.Sprite.ViewRotationIgnore = 1;
        pxSpriteCreateEventData.Sprite.ViewPositionIgnore = 1;
        pxSpriteCreateEventData.Sprite.Position.X = -1.20f;
        pxSpriteCreateEventData.Sprite.Position.Y = -0.65;
        pxSpriteCreateEventData.Sprite.Scaling.X = 0.25f;
        pxSpriteCreateEventData.Sprite.Scaling.Y = 0.25f;      

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);

        PXTextCopyA("Face", 4, pxChracterFace->Name, 20);

        pxDialogBox.SpriteCharacterFace = pxChracterFace;
    }

    //-----------------------------------------------------
    // Dialog-Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeText;
        pxSpriteCreateEventData.SpawnEnabled = PXFalse;
        pxSpriteCreateEventData.ObjectReference = &pxDialogBox.DialogBoxText;   

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);

        pxDialogBox.DialogBoxText->Position.X = 0.63f;
        pxDialogBox.DialogBoxText->Position.Y = 0.60f;
        pxDialogBox.DialogBoxText->Scaling.X = 0.40f;
        pxDialogBox.DialogBoxText->Scaling.Y = 0.55f;
        pxDialogBox.DialogBoxText->DoubleRenderForShadow = PXTrue;
        pxDialogBox.DialogBoxText->Font = _font;
    }



    //-----------------------------------------------------
    // Dialog-Text-Timer
    //-----------------------------------------------------
    {       
        PXEngineResourceCreateInfo pxTimerCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxTimerCreateEventData);
        pxTimerCreateEventData.CreateType = PXEngineCreateTypeTimer;
        pxTimerCreateEventData.ObjectReference = &pxDialogBox.DialogBoxTextTimer;
        pxTimerCreateEventData.SpawnEnabled = PXFalse;      

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxTimerCreateEventData);

        pxDialogBox.DialogBoxTextTimer->Owner = &pxDialogBox;
        pxDialogBox.DialogBoxTextTimer->CallBack = PXEngineDialogBoxTimerTrigger;
        pxDialogBox.DialogBoxTextTimer->TimeDeltaTarget = 1000000 / 2;
    }



    //-----------------------------------------------------
    // Dialog-Text-Sound
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSpriteCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSpriteCreateEventData);
        pxSpriteCreateEventData.CreateType = PXEngineCreateTypeEngineSound;
        pxSpriteCreateEventData.ObjectReference = &_dialogLetterPopSFX;
        pxSpriteCreateEventData.FilePath = "Audio/SFX/text.wav";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxSpriteCreateEventData);
    }







    //-----------------------------------------------------
// Loading Texture
//-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxEngineResourceCreateInfo;
        PXClear(PXEngineResourceCreateInfo, &pxEngineResourceCreateInfo);
        pxEngineResourceCreateInfo.CreateType = PXEngineCreateTypeTexture2D;
        pxEngineResourceCreateInfo.ObjectReference = &pxChracterImageA;
        pxEngineResourceCreateInfo.FilePath = "Texture/en_distressed.png";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxEngineResourceCreateInfo);
    }
    //-----------------------------------------------------


    //-----------------------------------------------------
    // Loading Texture
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxEngineResourceCreateInfo;
        PXClear(PXEngineResourceCreateInfo, &pxEngineResourceCreateInfo);
        pxEngineResourceCreateInfo.CreateType = PXEngineCreateTypeTexture2D;
        pxEngineResourceCreateInfo.ObjectReference = &pxChracterImageB;
        pxEngineResourceCreateInfo.FilePath = "Texture/en_distressed2.png";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxEngineResourceCreateInfo);
    }
    //-----------------------------------------------------


    //-----------------------------------------------------
    // Loading Texture
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxEngineResourceCreateInfo;
        PXClear(PXEngineResourceCreateInfo, &pxEngineResourceCreateInfo);
        pxEngineResourceCreateInfo.CreateType = PXEngineCreateTypeTexture2D;
        pxEngineResourceCreateInfo.ObjectReference = &pxChracterImageC;
        pxEngineResourceCreateInfo.FilePath = "Texture/en_upset.png";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxEngineResourceCreateInfo);
    }
    //-----------------------------------------------------

    //-----------------------------------------------------
    // Loading Texture
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxEngineResourceCreateInfo;
        PXClear(PXEngineResourceCreateInfo, &pxEngineResourceCreateInfo);
        pxEngineResourceCreateInfo.CreateType = PXEngineCreateTypeTexture2D;
        pxEngineResourceCreateInfo.ObjectReference = &pxChracterImageD;
        pxEngineResourceCreateInfo.FilePath = "Texture/en_upset2.png";

        PXEngineResourceCreate(&bitFireEngine->Engine, &pxEngineResourceCreateInfo);
    }
    //-----------------------------------------------------



    _pxDialogMessagePage[0].CharacterMood = PXDialogCharacterMoodInvalid;
    _pxDialogMessagePage[0].CharacterMoodCounter = 0;
    _pxDialogMessagePage[0].CharacterSprite = pxChracterImageA;
    PXTextMakeFixedGlobalA(&_pxDialogMessagePage[0].Text, "Greetings!");

    _pxDialogMessagePage[1].CharacterMood = PXDialogCharacterMoodInvalid;
    _pxDialogMessagePage[1].CharacterMoodCounter = 0;
    _pxDialogMessagePage[1].CharacterSprite = pxChracterImageB;
    PXTextMakeFixedGlobalA(&_pxDialogMessagePage[1].Text, "So...\nAs you know i am working\non this project for a while now.");

    _pxDialogMessagePage[2].CharacterMood = PXDialogCharacterMoodInvalid;
    _pxDialogMessagePage[2].CharacterMoodCounter = 0;
    _pxDialogMessagePage[2].CharacterSprite = pxChracterImageC;
    PXTextMakeFixedGlobalA(&_pxDialogMessagePage[2].Text, "The world machine will be done soon.\nI hope it will be as good as i plan to.");

    _pxDialogMessagePage[3].CharacterMood = PXDialogCharacterMoodInvalid;
    _pxDialogMessagePage[3].CharacterMoodCounter = 0;
    _pxDialogMessagePage[3].CharacterSprite = pxChracterImageD;
    PXTextMakeFixedGlobalA(&_pxDialogMessagePage[3].Text, "It really is difficult.");

}
void PXAPI OnShutDownEvent(const BFEngine* bitFireEngine)
{

}
void PXAPI OnGameUpdateEvent(const BFEngine* bitFireEngine, const float deltaTime)
{
    //PXCameraFollow(bitFireEngine->Engine.CameraCurrent, deltaTime);

    PXText pxText;
    PXTextConstructBufferW(&pxText, 64);

    PXTextClear(&pxText);

    PXTextPrint(&pxText, L"[Cleaved] FPS:%5.2f, ms:%4.2f", bitFireEngine->Engine.FramesPerSecound, bitFireEngine->Engine.FrameTime);

    PXWindowTitleSet(&bitFireEngine->Engine.Window, &pxText);



}

void PXAPI OnRenderUpdateEvent(BFEngine* const bitFireEngine, BFInputContainer* input)
{
    {
        PXEngineResourceRenderInfo pxEngineResourceRenderInfo;
        pxEngineResourceRenderInfo.Type = PXEngineCreateTypeSkybox;
        pxEngineResourceRenderInfo.CameraReference = bitFireEngine->Engine.CameraCurrent;
        pxEngineResourceRenderInfo.SkyBoxRender.SkyBoxReference = _skybox;

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

            if (!pxSprite->Enabled)
            {
                continue;
            }

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

            if (!pxEngineText->Enabled)
            {
                continue;
            }

            PXEngineResourceRenderInfo pxEngineResourceRenderInfo;
            pxEngineResourceRenderInfo.Type = PXEngineCreateTypeText;
            pxEngineResourceRenderInfo.CameraReference = bitFireEngine->Engine.CameraCurrent;
            pxEngineResourceRenderInfo.TextRender.TextReference = pxEngineText;

            PXEngineResourceRender(&bitFireEngine->Engine, &pxEngineResourceRenderInfo);
        }
    }   
}