#ifndef BFEngineINCLUDE
#define BFEngineINCLUDE

#include <Media/PXImage.h>
#include <Media/PXType.h>
#include <OS/Graphic/PXGraphic.h>
#include <OS/Async/PXLock.h>
#include <OS/Async/PXThread.h>
#include <OS/Window/PXWindow.h>
#include <OS/Time/PXTime.h>
#include <OS/Hardware/PXController.h>
#include <System/Device/KeyBoard/KeyBoardCache.h>
#include <Engine/PXEngine.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct BFInputContainer_
    {
        KeyBoardCache KeyBoardInput;
    }
    BFInputContainer;

    typedef struct BFEngine_
    {
        PXEngine Engine;


        PXEngineStartUpEvent OnStartUp;
        PXEngineShutDownEvent OnShutDown;
        PXEngineUserUpdateEvent OnUserUpdate;
        PXEngineNetworkUpdateEvent OnNetworkUpdate;
        PXEngineGameUpdateEvent OnGameUpdate;
        PXEngineRenderUpdateEvent OnRenderUpdate;



        //---[Private}---------------------------------
        PXTime _lastUpdate;

        float _deltaTime;


        BFInputContainer InputContainer;
        //----------------------------------------------


        // Render -runtime info
        unsigned int _lastUsedShaderProgram;
        unsigned int _defaultShaderID;
        unsigned int _defaultTextureID;
        //---------------------------------------------------------------------

        PXController Controller;

        PXCamera CameraFree;
        PXCamera CameraPlayer;

        PXCamera* CameraCurrent;

        PXFont* DefaultFont;
        PXSkyBox* DefaultSkyBox;

        PXVertexStructure pxModelTEST;
    }
    BFEngine;

    PXPublic void BFEngineConstruct(BFEngine* const pxBitFireEngine);

    PXPrivate void BFEngineOnMouseButton(const BFEngine* const receiver, const PXWindow* sender, const PXMouseButton mouseButton, const PXKeyPressState buttonState);
    PXPrivate void BFEngineOnMouseMove(const BFEngine* const receiver, const PXWindow* sender, const PXMouse* mouse);
    PXPrivate void BFEngineOnKeyBoardKey(const BFEngine* const receiver, const PXWindow* sender, const PXKeyBoardKeyInfo keyBoardKeyInfo);
    PXPrivate void BFEngineOnWindowCreated(const BFEngine* const receiver, const PXWindow* sender);
    PXPrivate void BFEngineOnWindowSizeChanged(const BFEngine* const receiver, const PXWindow* sender);
    PXPrivate void BFEngineOnWindowsMouseCaptureChanged(const BFEngine* const receiver, const PXWindow* sender);

    PXPublic void BFEngineStart(BFEngine* const bfEngine, PXEngine* const pxEngine);
        PXPublic void BFEngineUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine);
        PXPublic void BFEngineStop(BFEngine* const bfEngine, PXEngine* const pxEngine);

    PXPrivate void BFEngineSceneRender(BFEngine* const bfEngine, PXEngine* const pxEngine);


    PXPrivate void PXCalculateUIOffset(PX);

    PXPrivate void BFEngineRenderScene(BFEngine* const bfEngine);



    PXPrivate void BFEngineUIElementRender(BFEngine* const bfEngine, PXUIElement* const pxUIElement);



    /*

    void MakeRectangle(PXRenderable& renderable);

    static PXThreadResult LoadResourceAsync(void* resourceAdress);

    //  PXActionResult Load(Resource* resource, const wchar_t* filePath, const bool loadAsynchronously = true);
    PXActionResult Load(Level& level, const wchar_t* filePath, const bool loadAsynchronously = true);


    PXActionResult Load(PXFont& font, const wchar_t* filePath, bool loadAsynchronously = true);
    PXActionResult Load(ShaderProgram& shaderProgram, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

    // Model
    PXActionResult Load(PXModel& model, const wchar_t* filePath, const bool loadAsynchronously = true);
    PXActionResult Load(PXRenderable& renderable, const char* filePath, bool loadAsynchronously = true);
    PXActionResult Load(PXRenderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize);

    // Texture
    PXActionResult Load(Image& image, const wchar_t* filePath, bool loadAsynchronously = true);


    PXActionResult Load(PXTexture& texture, const wchar_t* filePath, bool loadAsynchronously = true);
    //  PXActionResult Load(Sprite& sprite, const wchar_t* filePath);

      // Audio
     // PXActionResult Load(Sound& sound, const wchar_t* filePath, const bool loadAsynchronously = true);
     // PXActionResult Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously = true);


    PXActionResult Load(Collider* collider);
    PXActionResult Load
    (
        PXSkyBox* skyBox,
        const char* shaderVertex,
        const char* shaderFragment,
        const char* textureRight,
        const char* textureLeft,
        const char* textureTop,
        const char* textureBottom,
        const char* textureBack,
        const char* textureFront
    );
 

    void UnloadAll();

    void ModelsPhysicsApply(float deltaTime);

    void ModelsRender(const float deltaTime);

    void PrintContent(bool detailed);
       */

#ifdef __cplusplus
}
#endif

#endif