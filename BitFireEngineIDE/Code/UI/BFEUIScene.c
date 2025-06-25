#include "BFEUIScene.h"

void PXAPI BFSceneOnStartup(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnUserInputUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);
void PXAPI OnNetworkUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnGameUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnRenderUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI PXOnUserInputUpdateScene(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);


void PXAPI BFEUISceneCreate(BFEUIScene* const bfeUIScene, PXEngine* const pxEngine, PXWindow* const parent)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    //-----------------------------------------------------
    // TAB::Scene
    //-----------------------------------------------------
    {
        PXEngineStartInfo pxEngineStartInfo;
        PXClear(PXEngineStartInfo, &pxEngineStartInfo);
        pxEngineStartInfo.Owner = pxEngine;
        //pxEngineStartInfo.WindowRenderTarget = parent;
        pxEngineStartInfo.System = PXGraphicSystemOpenGL;
        pxEngineStartInfo.OnStartUp = BFSceneOnStartup;
        pxEngineStartInfo.OnUserUpdate = PXOnUserInputUpdateScene;
        pxEngineStartInfo.OnRenderUpdate = OnRenderUpdateEvent;
        pxEngineStartInfo.OnGameUpdate = OnGameUpdateEvent;
        //pxEngineStartInfo.UseMouseInput = PXTrue;

        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "SceneRender";
        pxResourceCreateInfo.ObjectReference = &bfeUIScene->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeRenderFrame;
        pxResourceCreateInfo.UIElement.WindowCurrent = parent;
        pxResourceCreateInfo.UIElement.WindowParent = parent;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder| PXWindowAllignCenter;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Data.SceneRender.Engine = pxEngine;
        pxResourceCreateInfo.UIElement.Data.SceneRender.StartInfo = &pxEngineStartInfo;


        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

#if 0
        pxEngineScene.OnRenderUpdate = OnRenderUpdateEvent;
        pxEngineScene.OnStartUp = OnStartUpEvent;
        pxEngineScene.OnShutDown = OnShutDownEvent;
        pxEngineScene.OnUserUpdate = OnUserInputUpdate;
        pxEngineScene.OnNetworkUpdate = OnNetworkUpdate;
        pxEngineScene.OnGameUpdate = OnGameUpdateEvent;
        pxEngineScene.OnRenderUpdate = OnRenderUpdateEvent;
#endif

    }

#if 0
    //-----------------------------------------------------
 // Panel::Scene::Text
 //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "Scene";
        pxResourceCreateInfo.ObjectReference = &_panelMenuButtonFileText;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
        pxResourceCreateInfo.UIElement.WindowParent = parent;
        pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourDefaultText;
        pxResourceCreateInfo.UIElement.Position.Form.Height = PXDefaultTitleBar;

        //PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#endif
}





PXShaderProgram* _pxWorldGridShader = 0;
PXShaderProgram* _pxObjectShader = 0;
PXShaderProgram* _pxGismoShader = 0;

PXSkyBox* _sceneSkyBox = 0;

PXModel _pxModelMapWorldGridTrue;
PXModel* _pxModelMapWorldGrid = &_pxModelMapWorldGridTrue;

PXModel* _pxModelMap = 0;
PXModel* _pxGismo = 0;

PXCamera _worldCamera;


// Register world grid
const float vertexData[] =
{
    -1, 0,-1,
        1, 0,1,
    1, 0,-1,


     1, 0,1,
       -1, 0,-1,
    -1, 0,1,

};

const PXInt8U indexDATA[] =
{
    0,1,2,3,4,5
};






void PXAPI BFSceneOnStartup(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
    PXResourceCreateInfo pxUIElementCreateData;

#if 0
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeSound;
        pxUIElementCreateData.ObjectReference = &_musicTest;
        pxUIElementCreateData.FilePath = "H:\\[Cache]\\chip.wav";
        pxUIElementCreateData.Sound.SoundLoop = PXTrue;

        //PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);


        PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;
        // TODO: Silly
        if(pxAudio)
        {
            if(pxAudio->DeviceOpen)
            {
                pxAudio->DeviceOpen(pxAudio->SystemReference, &_soundAudioDevice, PXAudioDeviceTypeOutput, 0);
            }

            if(pxAudio->DeviceLoad)
            {
                pxAudio->DeviceLoad(pxAudio->SystemReference, &_soundAudioDevice, _musicTest);
            }
        }
    }
#endif


    //-----------------------------------------------------
    // Shader-Object
    //-----------------------------------------------------
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeShaderProgram;
        pxUIElementCreateData.ObjectReference = &_pxObjectShader;
        pxUIElementCreateData.ShaderProgram.ShaderVertexFilePath = "Shader/Object_Vertex.glsl";
        pxUIElementCreateData.ShaderProgram.ShaderPixelFilePath = "Shader/Object_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeShaderProgram;
        pxUIElementCreateData.ObjectReference = &_pxGismoShader;
        pxUIElementCreateData.ShaderProgram.ShaderVertexFilePath = "Shader/Gismo_Vertex.glsl";
        pxUIElementCreateData.ShaderProgram.ShaderPixelFilePath = "Shader/Gismo_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }










#if 0

    PXUIElementConstruct(&_textureTestA, PXUIElementTypeImage);
    _textureTestA.IsHoverable = PXTrue;
    PXUIElementColorSet4F(&_textureTestA, 0.5, 0.5, 0.5, 0.5);
    PXUIElementPositionSetXYWH(&_textureTestA, 0.55f, -0.52f, 0.88f, 0.67f, PXUIElementPositionRelative);
    _textureTestA.TextureID = _testImage.ID;

    PXGraphicUIElementRegister(pxGraphic, &_textureTestA);
#endif


    // TEXT






/*
PXUIElementConstruct(&_positionText, PXUIElementTypeText);
_positionText.FontID = &DefaultFont;
PXUIElementColorSet4F(&_positionText, 1, 1, 1, 1);
PXUIElementPositionSetXYWH(&_positionText, -0.9, 0.75, -0.8, 0.9);
//PXUIElementPositionSetXYWH(&_positionText, -0.82f, -0.52f, 0.38f, -0.67f);

PXUIElementTextSetA(&_positionText, "Assets");

PXGraphicUIElementRegister(pxGraphic, &_positionText);*/



//PXGraphicTextureLoadA(pxGraphic, &_dialogBoxTexture, (char*)"C:\\Users\\BitPaw\\Videos\\SquareBlue.png");

    //-----------------------------------------------------
    // Skybox
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeSkybox;
        pxUIElementCreateData.Flags = PXResourceCreateBehaviourSpawnInScene | PXResourceCreateBehaviourLoadASYNC;
        pxUIElementCreateData.ObjectReference = &_sceneSkyBox;
        pxUIElementCreateData.SkyBox.ShaderProgramCreateInfo.ShaderVertexFilePath = "Shader/SkyBox_Vertex.glsl";
        pxUIElementCreateData.SkyBox.ShaderProgramCreateInfo.ShaderPixelFilePath = "Shader/SkyBox_Fragment.glsl";
        pxUIElementCreateData.SkyBox.SkyBoxTextureA = "Texture/SkyBox_Side.png";
        pxUIElementCreateData.SkyBox.SkyBoxTextureB = "Texture/SkyBox_Side.png";
        pxUIElementCreateData.SkyBox.SkyBoxTextureC = "Texture/SkyBox_Top.png";
        pxUIElementCreateData.SkyBox.SkyBoxTextureD = "Texture/SkyBox_Bottom.png";
        pxUIElementCreateData.SkyBox.SkyBoxTextureE = "Texture/SkyBox_Side.png";
        pxUIElementCreateData.SkyBox.SkyBoxTextureF = "Texture/SkyBox_Side.png";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    //-----------------------------------------------------
    // Worldgrid-Shader
    //-----------------------------------------------------
    {
        PXResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.Type = PXResourceTypeShaderProgram;
        pxSkyBoxCreateEventData.ObjectReference = &_pxWorldGridShader;
        pxSkyBoxCreateEventData.ShaderProgram.ShaderVertexFilePath = "Shader/WorldGrid_Vertex.glsl";
        pxSkyBoxCreateEventData.ShaderProgram.ShaderPixelFilePath = "Shader/WorldGrid_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxSkyBoxCreateEventData);
    }

    //-----------------------------------------------------
    // Worldgrid-Model
    //-----------------------------------------------------
    {
        PXModelConstruct(_pxModelMapWorldGrid);
        _pxModelMapWorldGrid->Mesh.VertexBufferListAmount = 1;
        _pxModelMapWorldGrid->Mesh.VertexBufferPrime.Info.Behaviour |= PXResourceInfoConstData;
        _pxModelMapWorldGrid->Mesh.VertexBufferPrime.VertexDataSize = sizeof(vertexData);
        _pxModelMapWorldGrid->Mesh.VertexBufferPrime.VertexData = vertexData;
        _pxModelMapWorldGrid->Mesh.VertexBufferPrime.Format = PXVertexBufferFormatP3F32;

        _pxModelMapWorldGrid->Mesh.IndexBuffer.DataIndexPosition = indexDATA;
        _pxModelMapWorldGrid->Mesh.IndexBuffer.DataIndexSizeSegment = sizeof(indexDATA);
        _pxModelMapWorldGrid->Mesh.IndexBuffer.IndexDataType = PXTypeInt08U;
        _pxModelMapWorldGrid->Mesh.IndexBuffer.DrawModeID = PXDrawModeIDTriangle; // PXDrawModeIDPoint | PXDrawModeIDLine;


        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeModel;
        pxUIElementCreateData.ObjectReference = &_pxModelMapWorldGrid;
        pxUIElementCreateData.Model.ShaderProgramReference = _pxWorldGridShader;
        pxUIElementCreateData.Model.Scale = 1000;

#if 0
        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

        _pxModelMapWorldGrid->RenderBothSides = PXTrue;
#endif
    }

    // Load model
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeModel;
        pxUIElementCreateData.ObjectReference = &_pxModelMap;
        pxUIElementCreateData.FilePath = "Model/Dust_II/DustII.obj";
        // pxUIElementCreateData.FilePath = "C:/Data/WorkSpace/[GIT]/PXUltima/Code/PXUltimaCTest/_TEST_DATA_OUTPUT_/WAD_TEMP_3/0000000027681530.R3D2.obj";
        pxUIElementCreateData.Model.ShaderProgramReference = _pxObjectShader;
        pxUIElementCreateData.Model.Scale = 1;// 5.0f;
        pxUIElementCreateData.Model.HitBoxBehaviour = PXHitBoxBehaviourWallStatic;

#if 1
        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
#endif

    }


    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeModel;
        pxUIElementCreateData.ObjectReference = &_pxGismo;
        pxUIElementCreateData.FilePath = "Model/GismoTreeD.obj";
        pxUIElementCreateData.Model.ShaderProgramReference = _pxGismoShader;
        pxUIElementCreateData.Model.Scale = 1.0f;

#if 0
        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
#endif

    }

    PXCameraConstruct(&_worldCamera);
}









void PXAPI OnUserInputUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo)
{
#if 0
    if(KeyBoardIDF01 & pxEngine->KeyBoardCurrentInput.Actions)
    {
        PXLogPrint
        (
            PXLoggingInfo,
            "BFE",
            "Input",
            "Swap-Page"
        );

        // how to fix?
        PXWindowTabListSwapPage(_tabControlMain);

        bfBitFireIDE->EngineScene.DoRendering = (_tabPageScene->Info.Behaviour & PXResourceInfoSelected) > 0;

        Sleep(1);
    }
#endif

#if 0
    PXWindow* pxWindow = &pxEngine->Window;
    PXKeyBoard* keyboard = &pxEngine->KeyBoardCurrentInput;
    PXMouse* mouse = &pxEngine->MouseCurrentInput;

#if 0
    if(keyboard.F.IsShortPressed())
    {
        keyboard.F.Value = 0xFF;

        if(_sign.Interactable)
        {
            printf("[Event] Clicked Sign\n");
        }
    }
#endif

    // PXControllerDataGet(&bfEngine->Controller);

    //printf("%6i, %6i\n", bitFireEngine->Controller.Axis[0], bitFireEngine->Controller.Axis[1]);

    //_playerCharacterLuna.MatrixModel.Move(movement);


    if(pxPlayerMoveInfo->IsWindowInFocus && (IsPressedButtonLeft(mouse->Buttons) && IsPressedButtonLeft(mouse->ButtonsDelta)))
    {
        if(bfEngine->CollisionCheckInfo.CurrentElement)
        {
#if 0
            PXUIElementInteractInfo pxUIElementInteractInfo;
            PXClear(PXUIElementInteractInfo, &pxUIElementInteractInfo);
            pxUIElementInteractInfo.UIElementSender = bfEngine->CollisionCheckInfo.CurrentElement;
            pxUIElementInteractInfo.Type = PXUIElementInteractTypeSelect;

            PXFunctionInvoke(bfEngine->CollisionCheckInfo.CurrentElement->InteractCallBack, &pxUIElementInteractInfo);
#endif
        }
    }

    const PXBool isMouseInputWanted = pxPlayerMoveInfo->IsWindowInFocus && IsPressedButtonRight(mouse->Buttons);

    pxPlayerMoveInfo->ActionCommit = isMouseInputWanted;
#endif
}

void PXAPI OnNetworkUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{

}

void PXAPI OnGameUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
#if 0
    float xx = PXMathSinusRADF32(animation);

    titleColor.Red = (0.2);
    titleColor.Green = (-xx) * 0.4;
    titleColor.Blue = (xx);

    animation += 0.01;
#endif

    // PXCameraRotateXYZ(bfBitFireIDE->EngineScene.CameraCurrent, 0.01, 0.5, 0.2);
   //  PXCameraUpdate(bfBitFireIDE->EngineScene.CameraCurrent, 1);
}

void PXAPI OnRenderUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
#if 0
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();
#endif
}
