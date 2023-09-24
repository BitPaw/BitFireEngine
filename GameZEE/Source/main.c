#include "main.h"

#if !defined(_DEBUG) && defined(OSWindows5)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif  
{
#if 0
    PXSteam stream;

    PXSteamConstruct(&stream);

    PXSteamInitialize(&stream);

    PXSteamFriend pxSteamFriend[60];

    unsigned int number = PXSteamFriendsFetchList(&stream, PXSteamFriendFlagAll, pxSteamFriend, 60);

    for (size_t i = 0; i < number; ++i)
    {
        PXSteamFriend* pxFriend = &pxSteamFriend[i];

        printf("Friend [%3i] %s\n", pxFriend->Level, pxFriend->NameProfile);
    }

    PXSteamShutdown(&stream);
#endif

    BFEngine bitFireEngine;
    BFEngineConstruct(&bitFireEngine);

    bitFireEngine.UpdateUICallBack = OnUpdateUI;
    bitFireEngine.StartUpCallBack = OnStartUp; // StartDoc
    bitFireEngine.ShutDownCallBack = OnShutDown;
    bitFireEngine.UpdateGameLogicCallBack = OnUpdateGameLogic;
    bitFireEngine.UpdateInputCallBack = OnUpdateInput;

    BFEngineStart(&bitFireEngine);

    while (BFEngineIsRunning(&bitFireEngine))
    {
        BFEngineUpdate(&bitFireEngine);
    }

    BFEngineStop(&bitFireEngine);

    return EXIT_SUCCESS;
}

PXTexture2D _dialogBoxTexture;
PXTexture2D _dialogBoxTextureSelected;

PXVertexStructure _cubeThing;
PXRenderable _bohrThing;
PXFont _textFont;

//PXUIPanel pxUIPanelMain;
//PXUIPanel pxUIPanelMainCopy;

//PXUIButton pxDoStuffButton;

//PXUIText pxUITextFPS;
//PXUIText pxUITextPosition;


void OnUIOnClick(PXUIElement* const pxUIElement)
{
    printf("[#][Event] Mouse button clicked\n");
}
void OnUIOnMouseEnter(PXUIElement* const pxUIElement)
{
    printf("[#][Event] Mouse button enter\n");

   // pxUIPanelMain.UIElement.Renderable.MeshSegmentList[0].TextureID = _dialogBoxTextureSelected.ID;
}
void OnUIOnMouseLeave(PXUIElement* const pxUIElement)
{
    printf("[#][Event] Mouse button leave\n");

   // pxUIPanelMain.UIElement.Renderable.MeshSegmentList[0].TextureID = _dialogBoxTexture.ID;
}


void OnStartUp(BFEngine* const bitFireEngine)
{    
    PXGraphicContext* const graphicContext = &bitFireEngine->WindowMain.GraphicInstance;


//    PXWindowCursorCaptureMode(&bitFireEngine->WindowMain, PXWindowCursorLockAndHide);


    _worldShader.ResourceID.PXID = -1;
    _hudShaderID.ResourceID.PXID = -1;

    PXGraphicShaderProgramCreateVPA(graphicContext, &_worldShader, "Shader/WorldShader_V.glsl", "Shader/WorldShader_F.glsl");
        
    PXGraphicSkyboxRegisterA
    (
        graphicContext,
        &_skybox,
        "Shader/SkyBox.vert",
        "Shader/SkyBox.frag",
        "Texture/SkyBox/Right.png",
        "Texture/SkyBox/Left.png",
        "Texture/SkyBox/Top.png",
        "Texture/SkyBox/Bottom.png",
        "Texture/SkyBox/Back.png",
        "Texture/SkyBox/Front.png"
    );   

    PXGraphicTexture2DLoadA(graphicContext, &_dialogBoxTexture, "Texture/DialogueBox.bmp");

    PXGraphicTexture2DLoadA(graphicContext, &_dialogBoxTextureSelected, "Texture/DialogueBoxB.bmp");
   

   // PXGraphicModelLoadA(graphicContext, &_cubeModel, "Model/Dust_II/DustII.obj");
    PXGraphicModelShaderSet(graphicContext, &_cubeModel, &_worldShader);

 
   // PXGraphicModelLoadA(graphicContext, &_bohrThing, "Model/Bohr.obj");
    PXGraphicModelShaderSet(graphicContext, &_bohrThing, &_worldShader);

 //-----<UI>----------------------------------------------------------------
#if 1    
    
    //GraphicUIPanelRegister(graphicContext, &pxUIPanelMainCopy);
    //GraphicModelShaderSet(graphicContext, &pxUIPanelMainCopy.Renderable, &_worldShader);
    //PXMatrix4x4FScaleSet(1, 1, 1, &pxUIPanelMainCopy.Renderable.MatrixModel);
    //pxUIPanelMainCopy.Renderable.MeshSegmentList[0].RenderMode = GraphicRenderModeSquare;

    /*

    PXGraphicShaderProgramLoadGLSLA(graphicContext, &_hudShaderID, (char*)"Shader/HUD_V.glsl", (char*)"Shader/HUD_F.glsl");

    PXFontLoadA(&_textFont, (char*)"Font/A.fnt");

    
    PXGraphicUIButtonRegister(graphicContext, &pxDoStuffButton, 0, 0, 1, 1, (char*)"Button", &_textFont, &_hudShaderID);
    pxDoStuffButton.UIElement.OnClickCallback = OnUIOnClick;
    pxDoStuffButton.UIElement.OnMouseEnterCallback = OnUIOnMouseEnter;
    pxDoStuffButton.UIElement.OnMouseLeaveCallback = OnUIOnMouseLeave;

    PXGraphicUIPanelRegister(graphicContext, &pxUIPanelMain);
    PXGraphicModelShaderSet(graphicContext, &pxUIPanelMain.UIElement.Renderable, &_hudShaderID);    // _hudShaderID
    PXMatrix4x4FScaleSet(0.3, 0.13, 1, &pxUIPanelMain.UIElement.Renderable.MatrixModel);
    PXMatrix4x4FMoveToScaleXY(&pxUIPanelMain.UIElement.Renderable.MatrixModel, -0.9, -0.9, &pxUIPanelMain.UIElement.Renderable.MatrixModel);
    pxUIPanelMain.UIElement.Renderable.MeshSegmentList[0].RenderMode = PXGraphicRenderModeSquare;
    pxUIPanelMain.UIElement.Renderable.MeshSegmentList[0].TextureID = _dialogBoxTexture.ID;
    */
 

#endif
    //-------------------------------------------------------------------------




#if EnableMusic // Sound Enable
//BF::MID midi;
//midi.Load("Sound/CaveStory.mid");
//midi.Save("Sound/CaveStory_NEW.mid");

//sound.Load("Sound/Our.mp3");
//sound.Load("Sound/CaveStory.mid");

    //>>bitFireEngine->Register(_audioSource);
    //>>bitFireEngine->Load(_audioClip, L"Sound/CatFeet.wav", false);
    //>>bitFireEngine->Use(_audioSource, _audioClip);

    // GameSystem.LoopPart(audioSource, 100, 100);
    // GameSystem.Play(audioSource, sound);

#endif // Sound Enable
  //  GameSystem.MainCamera.Update(0);
   // GameSystem.MainCamera.Move(0, 0, -100);

   // bitFireEngine->PrintContent(true);
}

void OnShutDown(const BFEngine* bitFireEngine)
{

}

//BF::Vector3<float> rot(0.0349066, 0, 0);

void OnUpdateGameLogic(const BFEngine* bitFireEngine, const float deltaTime)
{
    /*
    if (cube.MatrixModel.CurrentPosition().Y <= 0)
    {
       // cube.MatrixModel.Move(0, 200, 0);
        cube.Force.Add(0, 50, 0);
    }*/

    _deltaTime = deltaTime;
}

void OnUpdateInput(BFEngine* const bitFireEngine, BFInputContainer* input)
{
#if EnableMusic
    PXBool changed = PXFalse;
    float value = 0.01f;

    /*
    if(InputButtonIsPressed(input->KeyBoardInput.O))
    {
        //>> _audioSource.PitchIncrease(value);

        changed = PXTrue;
    }

    if(InputButtonIsPressed(input->KeyBoardInput.L))
    {
        //>> _audioSource.PitchReduce(value);

        changed = PXTrue;
    }


    if (InputButtonIsShortPressed(input->KeyBoardInput.I))
    {       

        //pxUIPanelMain.UIElement.Renderable.DoRendering = !pxUIPanelMain.UIElement.Renderable.DoRendering;
        input->KeyBoardInput.I = 0xFF;
    }
    */

    if(changed)
    {
        //>>   bitFireEngine->Update(_audioSource);
    }
#endif


    if (bitFireEngine->WindowMain.CursorModeCurrent == PXWindowCursorShow) // If we are not in focus, do not handle input
    {
        return;
    }

    PXKeyBoard* keyboard = &bitFireEngine->WindowMain.KeyBoardCurrentInput;
    PXMouse* mouse = &bitFireEngine->WindowMain.MouseCurrentInput;
    PXVector3F movement = { 0,0,0 };

    if (keyboard->Commands & KeyBoardIDShiftLeft)
    {
        PXVector3FAddXYZ(&movement, 0, -1, 0, &movement);
    }
    if (keyboard->Letters & KeyBoardIDLetterW)
    {
        PXVector3FAddXYZ(&movement, 0, 0, 1, &movement);
    }
    if (keyboard->Letters & KeyBoardIDLetterA) { PXVector3FAddXYZ(&movement, -1, 0, 0, &movement); }
    if (keyboard->Letters & KeyBoardIDLetterS) { PXVector3FAddXYZ(&movement, 0, 0, -1, &movement); }
    if (keyboard->Letters & KeyBoardIDLetterD) { PXVector3FAddXYZ(&movement, 1, 0, 0, &movement); }
    if (keyboard->Letters & KeyBoardIDSpace)
    {


        //  PXCamera.Velocity.Set(0.0f, 6.0f, .0f);

        PXVector3FAddXYZ(&movement, 0, 1, 0, &movement);

    }

    PXCameraMove(bitFireEngine->CameraCurrent, &movement);
    PXCameraRotateXYZ(bitFireEngine->CameraCurrent, mouse->Delta[0], mouse->Delta[1], 0);
}

void OnUpdateUI(const BFEngine* bitFireEngine)
{
    //sprintf_s(text->TextContent, "FPS: %4i", (BF::MathCeiling(1 / _deltaTime)));
    //text->SetText(text->TextContent);

    if(model == 0)
    {
        // model = GameSystem.Resource.GetModel(0);
    }
    else
    {
        // model->ModelMatrix.Rotate(rot);
    }
}