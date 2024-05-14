#pragma check_stack(off)

int _fltused = 0;

#include "main.h"

#include <OS/Console/PXConsole.h>
#include <OS/Memory/PXMemory.h>


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
    PXEngine pxEngine;

    // Start
    {
        PXEngineStartInfo pxEngineStartInfo;
        PXClear(PXEngineStartInfo, &pxEngineStartInfo);
        pxEngineStartInfo.Mode = PXGraphicInitializeModeWindowfull;
        pxEngineStartInfo.System = PXGraphicSystemOpenGL;
        pxEngineStartInfo.OnStartUp = OnStartUpEvent;
        pxEngineStartInfo.OnShutDown = OnShutDownEvent;
        pxEngineStartInfo.OnUserUpdate = OnIntereact;
        pxEngineStartInfo.OnGameUpdate = OnGameUpdateEvent;
        pxEngineStartInfo.OnRenderUpdate = OnRenderUpdateEvent;
        pxEngineStartInfo.Name = "Cleaved";
        pxEngineStartInfo.Owner = PXNull;
        pxEngineStartInfo.UseMouseInput = PXTrue;

        const PXActionResult startResult = PXEngineStart(&pxEngine, &pxEngineStartInfo);

        if(PXActionSuccessful != startResult)
        {
            return EXIT_FAILURE;
        }
    }   

    while (PXEngineIsRunning(&pxEngine))
    {
        PXEngineUpdate(&pxEngine);
    }

    PXEngineStop(&pxEngine);

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

    //Sleep(1);
}

void PXAPI OnStartUpEvent(void* const owner, PXEngine* const pxEngine)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    PXGraphic* const pxGraphicContext = &pxEngine->Graphic;

    //PXWindowCursorCaptureMode(&bitFireEngine->WindowMain, PXWindowCursorLockAndHide);


    //-----------------------------------------------------
    // Object Shader
    //-----------------------------------------------------
    {    
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeShaderProgram;
        pxResourceCreateInfo.ObjectReference = &_worldShader;
        pxResourceCreateInfo.ShaderProgram.ShaderVertexFilePath = "Shader/Object_Vertex.glsl";
        pxResourceCreateInfo.ShaderProgram.ShaderPixelFilePath = "Shader/Object_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }

    //-----------------------------------------------------
    // SkyBox
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSkybox;
        pxResourceCreateInfo.SpawnEnabled = PXTrue;
        pxResourceCreateInfo.ObjectReference = &_skybox;
        pxResourceCreateInfo.SkyBox.ShaderProgramCreateInfo.ShaderVertexFilePath = "Shader/SkyBox_Vertex.glsl";
        pxResourceCreateInfo.SkyBox.ShaderProgramCreateInfo.ShaderPixelFilePath = "Shader/SkyBox_Fragment.glsl";
        pxResourceCreateInfo.SkyBox.SkyBoxTextureA = "Texture/MissingTexture.bmp";
        pxResourceCreateInfo.SkyBox.SkyBoxTextureB = "Texture/MissingTexture.bmp";
        pxResourceCreateInfo.SkyBox.SkyBoxTextureC = "Texture/MissingTexture.bmp";
        pxResourceCreateInfo.SkyBox.SkyBoxTextureD = "Texture/MissingTexture.bmp";
        pxResourceCreateInfo.SkyBox.SkyBoxTextureE = "Texture/MissingTexture.bmp";
        pxResourceCreateInfo.SkyBox.SkyBoxTextureF = "Texture/MissingTexture.bmp";

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }



    //-----------------------------------------------------
    // Background
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXTrue;
        pxResourceCreateInfo.ObjectReference = &_backGround;
        pxResourceCreateInfo.FilePath = "Texture/BackGround.png";
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.Position.Z = -0.5;
        pxResourceCreateInfo.Sprite.Scaling.X = 20;
        pxResourceCreateInfo.Sprite.Scaling.Y = 20;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }


    //-----------------------------------------------------
    // Background
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXTrue;
        pxResourceCreateInfo.ObjectReference = &_floor;
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.Position.Y = -16.5;
        pxResourceCreateInfo.Sprite.Position.Z = -0.5;
        pxResourceCreateInfo.Sprite.Scaling.X = 20;
        pxResourceCreateInfo.Sprite.Scaling.Y = 1;
        pxResourceCreateInfo.Sprite.HitBoxCreate = PXTrue;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        //_floor->HitBox->Info.Behaviour = PXHitBoxBehaviourKeepOut;
    }



    //-----------------------------------------------------
    // Nyte
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXTrue;
        pxResourceCreateInfo.ObjectReference = &_playerCharacterNyte;
        pxResourceCreateInfo.FilePath = "Texture/Nyte.png";
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.Position.X = 0.0f;
        pxResourceCreateInfo.Sprite.Position.Y = -0.8;
        pxResourceCreateInfo.Sprite.Position.Z = 0.01;
        pxResourceCreateInfo.Sprite.Scaling.X = 5.5;
        pxResourceCreateInfo.Sprite.Scaling.Y = 5.5;
        pxResourceCreateInfo.Sprite.HitBoxCreate = PXTrue;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

       // pxEngine->CameraCurrent->Target = &_playerCharacterNyte->Model.ModelMatrix;
        pxEngine->CameraCurrent->Offset.Y = 08.0f;
       pxEngine->CameraCurrent->Offset.Z = 20.0f;
        //pxEngine->CameraCurrent->Offset.Z = 40.0f;
       pxEngine->CameraCurrent->DeadZone.X = 30.3;
        pxEngine->CameraCurrent->DeadZone.Y = 3.8;
    }



    //-----------------------------------------------------
    // Theia
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXTrue;
        pxResourceCreateInfo.ObjectReference = &_playerCharacterLuna;
        pxResourceCreateInfo.FilePath = "Texture/Theia.png";
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.Position.X = 5.80f;
        pxResourceCreateInfo.Sprite.Position.Y = -5.80f;
        pxResourceCreateInfo.Sprite.Position.Z = 5.01;
        pxResourceCreateInfo.Sprite.Scaling.X = 5.5f;
        pxResourceCreateInfo.Sprite.Scaling.Y = 5.5f;
        pxResourceCreateInfo.Sprite.HitBoxCreate = PXTrue;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        _playerCharacterLuna->HitBox->Info.Behaviour = PXHitBoxBehaviourDetect;
    }



    //-----------------------------------------------------
    // Sign
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXTrue;
        pxResourceCreateInfo.ObjectReference = &_sign;
        pxResourceCreateInfo.FilePath = "Texture/Sign.png";
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.Position.X = -6.40f;
        pxResourceCreateInfo.Sprite.Position.Y = -5.80f;
        pxResourceCreateInfo.Sprite.Position.Z = 5.3;
        pxResourceCreateInfo.Sprite.Scaling.X = 5.6f;
        pxResourceCreateInfo.Sprite.Scaling.Y = 5.6f;
        pxResourceCreateInfo.Sprite.HitBoxCreate = PXTrue;
      //  pxEngineResourceCreateInfo.Sprite.HitboxData.Flags = ;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        _sign->HitBox->Info.Behaviour = PXHitBoxBehaviourKeepOut;
    }



    //-----------------------------------------------------
    // Lamp
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXTrue;
        pxResourceCreateInfo.ObjectReference = &_lamp;
        pxResourceCreateInfo.FilePath = "Texture/LampB.png";
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.Position.X = -12.20f;
        pxResourceCreateInfo.Sprite.Position.Y = -5.80f;
        pxResourceCreateInfo.Sprite.Position.Z = 5.3;
        pxResourceCreateInfo.Sprite.Scaling.X = 5.6f;
        pxResourceCreateInfo.Sprite.Scaling.Y = 5.6f;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }



    //-----------------------------------------------------
    // Dialog
    //-----------------------------------------------------
    {
        PXClear(PXEngineDialogBox, &pxDialogBox);

        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXFalse;
        pxResourceCreateInfo.ObjectReference = &pxDialogBox.DialogBoxSprite;
        pxResourceCreateInfo.FilePath = "Texture/Dialog.png";
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.ViewPositionIgnore = 1;
        pxResourceCreateInfo.Sprite.ViewRotationIgnore = 1;
        //pxSpriteCreateEventData.Position.X = 0;
        pxResourceCreateInfo.Sprite.Position.Y = -0.65;
        //pxSpriteCreateEventData.Position.Z = 0.02;
        pxResourceCreateInfo.Sprite.Scaling.X = 1.8f;
        pxResourceCreateInfo.Sprite.Scaling.Y = 0.4f;
        pxResourceCreateInfo.Sprite.TextureScalingPoints[0].X = 0.2 / pxResourceCreateInfo.Sprite.Scaling.X;
        pxResourceCreateInfo.Sprite.TextureScalingPoints[0].Y = 0.2 / pxResourceCreateInfo.Sprite.Scaling.Y;
        pxResourceCreateInfo.Sprite.TextureScalingPoints[1].X = 0.3;
        pxResourceCreateInfo.Sprite.TextureScalingPoints[1].Y = 0.3;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }



    //-----------------------------------------------------
    // Font
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeFont;
        pxResourceCreateInfo.ObjectReference = &_font;
        pxResourceCreateInfo.FilePath = "Font/segoe.fnt";
        pxResourceCreateInfo.Font.ShaderProgramCurrent = _worldShader;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }



    //-----------------------------------------------------
    // Dialog-Sprite
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeSprite;
        pxResourceCreateInfo.SpawnEnabled = PXFalse;
        pxResourceCreateInfo.ObjectReference = &pxChracterFace;
        pxResourceCreateInfo.Sprite.ShaderProgramCurrent = _worldShader;
        pxResourceCreateInfo.Sprite.ViewRotationIgnore = 1;
        pxResourceCreateInfo.Sprite.ViewPositionIgnore = 1;
        pxResourceCreateInfo.Sprite.Position.X = -1.20f;
        pxResourceCreateInfo.Sprite.Position.Y = -0.65;
        pxResourceCreateInfo.Sprite.Scaling.X = 0.25f;
        pxResourceCreateInfo.Sprite.Scaling.Y = 0.25f;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        //PXTextCopyA("Face", 4, pxChracterFace->Name, 20);

        pxDialogBox.SpriteCharacterFace = pxChracterFace;
    }

    //-----------------------------------------------------
    // Dialog-Text
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeText;
        pxResourceCreateInfo.SpawnEnabled = PXFalse;
        pxResourceCreateInfo.ObjectReference = &pxDialogBox.DialogBoxText;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

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
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeTimer;
        pxResourceCreateInfo.ObjectReference = &pxDialogBox.DialogBoxTextTimer;
        pxResourceCreateInfo.SpawnEnabled = PXFalse;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        pxDialogBox.DialogBoxTextTimer->Owner = &pxDialogBox;
        pxDialogBox.DialogBoxTextTimer->CallBack = PXEngineDialogBoxTimerTrigger;
        pxDialogBox.DialogBoxTextTimer->TimeDeltaTarget = 1000000 / 2;
    }



    //-----------------------------------------------------
    // Dialog-Text-Sound
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeEngineSound;
        pxResourceCreateInfo.ObjectReference = &_dialogLetterPopSFX;
        pxResourceCreateInfo.FilePath = "Audio/SFX/text.wav";

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }







    //-----------------------------------------------------
// Loading Texture
//-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeTexture2D;
        pxResourceCreateInfo.ObjectReference = &pxChracterImageA;
        pxResourceCreateInfo.FilePath = "Texture/en_distressed.png";

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    //-----------------------------------------------------


    //-----------------------------------------------------
    // Loading Texture
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeTexture2D;
        pxResourceCreateInfo.ObjectReference = &pxChracterImageB;
        pxResourceCreateInfo.FilePath = "Texture/en_distressed2.png";

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    //-----------------------------------------------------


    //-----------------------------------------------------
    // Loading Texture
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeTexture2D;
        pxResourceCreateInfo.ObjectReference = &pxChracterImageC;
        pxResourceCreateInfo.FilePath = "Texture/en_upset.png";

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    //-----------------------------------------------------

    //-----------------------------------------------------
    // Loading Texture
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeTexture2D;
        pxResourceCreateInfo.ObjectReference = &pxChracterImageD;
        pxResourceCreateInfo.FilePath = "Texture/en_upset2.png";

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
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

void PXAPI OnShutDownEvent(void* const owner, PXEngine* const pxEngine)
{

}

void PXAPI OnGameUpdateEvent(void* const owner, PXEngine* const pxEngine)
{
    //PXCameraFollow(bitFireEngine->Engine.CameraCurrent, deltaTime);   
}

void PXAPI OnRenderUpdateEvent(void* const owner, PXEngine* const pxEngine)
{
   
}