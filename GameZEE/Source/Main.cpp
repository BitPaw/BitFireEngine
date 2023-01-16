#include "main.h"

#include <Device/InputButton.h>

#if !defined(_DEBUG) && defined(OSWindows5)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif  
{
    BitFireEngine bitFireEngine;

    bitFireEngine.UpdateUICallBack = OnUpdateUI;
    bitFireEngine.StartUpCallBack = OnStartUp; // StartDoc
    bitFireEngine.ShutDownCallBack = OnShutDown;
    bitFireEngine.UpdateGameLogicCallBack = OnUpdateGameLogic;
    bitFireEngine.UpdateInputCallBack = OnUpdateInput;

    bitFireEngine.Start();

    while (bitFireEngine.IsRunning)
    {
        bitFireEngine.Update();
    }

    bitFireEngine.Stop();

    return EXIT_SUCCESS;
}

PXTexture _dialogBoxTexture;
PXTexture _dialogBoxTextureSelected;

PXModel _cubeThing;
PXRenderable _bohrThing;
PXFont _textFont;

PXUIPanel pxUIPanelMain;
PXUIPanel pxUIPanelMainCopy;

PXUIButton pxDoStuffButton;

PXUIText pxUITextFPS;
PXUIText pxUITextPosition;


#include <Format/FNT/FNT.h>


void OnUIOnClick(PXUIElement* const pxUIElement)
{
    printf("[#][Event] Mouse button clicked\n");
}
void OnUIOnMouseEnter(PXUIElement* const pxUIElement)
{
    printf("[#][Event] Mouse button enter\n");

    pxUIPanelMain.UIElement.Renderable.MeshSegmentList[0].TextureID = _dialogBoxTextureSelected.ID;
}
void OnUIOnMouseLeave(PXUIElement* const pxUIElement)
{
    printf("[#][Event] Mouse button leave\n");

    pxUIPanelMain.UIElement.Renderable.MeshSegmentList[0].TextureID = _dialogBoxTexture.ID;
}


void OnStartUp(BitFireEngine* const bitFireEngine)
{    
    PXGraphicContext* const graphicContext = &bitFireEngine->_mainWindow.GraphicInstance;

    _worldShader.ID = -1;
    _hudShaderID.ID = -1;

    PXGraphicShaderProgramLoadGLSLA(graphicContext, &_worldShader, (char*)"Shader/WorldShader_V.glsl", (char*)"Shader/WorldShader_F.glsl");

    bitFireEngine->Load
    (
        &skybox,
        "Shader/SkyBox.vert",
        "Shader/SkyBox.frag",
        "Texture/SkyBox/Right.png",
        "Texture/SkyBox/Left.png",
        "Texture/SkyBox/Top.png",
        "Texture/SkyBox/Bottom.png",
        "Texture/SkyBox/Back.png",
        "Texture/SkyBox/Front.png"
    );


   

    PXGraphicTextureLoadA(graphicContext, &_dialogBoxTexture, (char*)"Texture/DialogueBox.bmp");

    PXGraphicTextureLoadA(graphicContext, &_dialogBoxTextureSelected, (char*)"Texture/DialogueBoxB.bmp");
   


    PXGraphicModelLoadA(graphicContext, &_cubeModel, (char*)"Model/Dust_II/DustII.obj");
    PXGraphicModelShaderSet(graphicContext, &_cubeModel, &_worldShader);

 
    //PXGraphicModelLoadA(graphicContext, &_bohrThing, (char*)"Model/Bohr.obj");
    //PXGraphicModelShaderSet(graphicContext, &_bohrThing, &_worldShader);

 //-----<UI>----------------------------------------------------------------
#if 1    
    
    //GraphicUIPanelRegister(graphicContext, &pxUIPanelMainCopy);
    //GraphicModelShaderSet(graphicContext, &pxUIPanelMainCopy.Renderable, &_worldShader);
    //PXMatrix4x4FScaleSet(1, 1, 1, &pxUIPanelMainCopy.Renderable.MatrixModel);
    //pxUIPanelMainCopy.Renderable.MeshSegmentList[0].RenderMode = GraphicRenderModeSquare;

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

    bitFireEngine->PrintContent(true);
}

void OnShutDown(const BitFireEngine* bitFireEngine)
{

}

//BF::Vector3<float> rot(0.0349066, 0, 0);

void OnUpdateGameLogic(const BitFireEngine* bitFireEngine, const float deltaTime)
{
    /*
    if (cube.MatrixModel.CurrentPosition().Y <= 0)
    {
       // cube.MatrixModel.Move(0, 200, 0);
        cube.Force.Add(0, 50, 0);
    }*/

    _deltaTime = deltaTime;
}

void OnUpdateInput(BitFireEngine* const bitFireEngine, BF::InputContainer& input)
{
#if EnableMusic
    bool changed = false;
    float value = 0.01f;

    if(InputButtonIsPressed(input.KeyBoardInput.O))
    {
        //>> _audioSource.PitchIncrease(value);

        changed = true;
    }

    if(InputButtonIsPressed(input.KeyBoardInput.L))
    {
        //>> _audioSource.PitchReduce(value);

        changed = true;
    }


    if (InputButtonIsShortPressed(input.KeyBoardInput.I))
    {       

        pxUIPanelMain.UIElement.Renderable.DoRendering = !pxUIPanelMain.UIElement.Renderable.DoRendering;
        input.KeyBoardInput.I = 0xFF;
    }


    if(changed)
    {
        //>>   bitFireEngine->Update(_audioSource);
    }
#endif


    if (bitFireEngine->_mainWindow.CursorModeCurrent == PXWindowCursorShow) // If we are not in focus, do not handle input
    {
        return;
    }

    KeyBoardCache& keyboard = input.KeyBoardInput;
    MouseCache& mouse = input.MouseInput;
    PXCamera& camera = bitFireEngine->MainCamera;
    PXVector3F movement = { 0,0,0 };

    if(InputButtonIsPressed(keyboard.ShitftLeft)) { PXVector3FAddXYZ(&movement, 0, -1, 0, &movement); }
    if(InputButtonIsPressed(keyboard.W)) { PXVector3FAddXYZ(&movement,0, 0, 1, &movement); }
    if(InputButtonIsPressed(keyboard.A)) { PXVector3FAddXYZ(&movement,-1, 0, 0, &movement); }
    if(InputButtonIsPressed(keyboard.S)) { PXVector3FAddXYZ(&movement,0, 0, -1, &movement); }
    if(InputButtonIsPressed(keyboard.D)) { PXVector3FAddXYZ(&movement,1, 0, 0, &movement); }
    if(InputButtonIsPressed(keyboard.SpaceBar))
    {
        //camera.Velocity.Set(0.0f, 6.0f, .0f);

        PXVector3FAddXYZ(&movement, 0, 1, 0, &movement);
    }

    PXCameraMove(&camera, &movement);
    PXCameraRotateXYZ(&camera, mouse.InputAxis[0], mouse.InputAxis[1], 0);
}

void OnUpdateUI(const BitFireEngine* bitFireEngine)
{
    //sprintf_s(text->TextContent, "FPS: %4i", (BF::MathCeiling(1 / _deltaTime)));
    //text->SetText(text->TextContent);

    if(model == nullptr)
    {
        // model = GameSystem.Resource.GetModel(0);
    }
    else
    {
        // model->ModelMatrix.Rotate(rot);
    }
}