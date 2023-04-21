#ifndef BFEngineINCLUDE
#define BFEngineINCLUDE

#include <Container/LinkedList/PXLinkedList.h>
#include <Graphic/PXCamera.h>
#include <Device/PXMouse.h>
#include <Media/PXFont.h>
#include <Media/PXImage.h>
#include <Media/PXType.h>
#include <Graphic/PXGraphic.h>
#include <OS/Thread/PXLock.h>
#include <OS/Thread/PXThread.h>
#include <OS/Window/PXWindow.h>
#include <OS/Time/PXTime.h>

#include <System/Device/KeyBoard/KeyBoardCache.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct BFInputContainer_
    {
        KeyBoardCache KeyBoardInput;
        PXMouse MouseInput;
    }
    BFInputContainer;


    typedef struct BFEngine_ BFEngine;

    typedef void (*UpdateUIEvent)(BFEngine* const bitFireEngine);
    typedef void (*StartUpEvent)(BFEngine* const bitFireEngine);
    typedef void (*ShutDownEvent)(BFEngine* const bitFireEngine);
    typedef void (*UpdateGameLogicEvent)(BFEngine* const bitFireEngine, const float deltaTime);
    typedef void (*UpdateInputEvent)(BFEngine* const bitFireEngine, BFInputContainer* const input);

    typedef struct BFEngine_
    {
        //---[Private}---------------------------------
        PXTime _lastUpdate;



        float _deltaTime;

        PXInt64U TimeCounterStart;
        PXInt64U TimeCounterDelta;
        PXInt64U TimeCounterEnd;
        PXInt64U TimeFrequency;
        float TimeFPS;
        float TimeMS;

        BFInputContainer InputContainer;
        //----------------------------------------------


        // Render -runtime info
        unsigned int _lastUsedShaderProgram;
        unsigned int _defaultShaderID;
        unsigned int _defaultTextureID;
        //---------------------------------------------------------------------

   
        PXWindow WindowMain;

        PXCamera MainCamera;
        PXFont* DefaultFont;
        PXSkyBox* DefaultSkyBox;

        UpdateUIEvent UpdateUICallBack;
        StartUpEvent StartUpCallBack;
        ShutDownEvent ShutDownCallBack;
        UpdateGameLogicEvent UpdateGameLogicCallBack;
        UpdateInputEvent UpdateInputCallBack;
    }
    BFEngine;

    PXPublic void BFEngineConstruct(BFEngine* const pxBitFireEngine);

    PXPrivate void BFEngineOnMouseButton(const BFEngine* const receiver, const PXWindow* sender, const MouseButton mouseButton, const ButtonState buttonState);
    PXPrivate void BFEngineOnMouseMove(const BFEngine* const receiver, const PXWindow* sender, const PXMouse* mouse);
    PXPrivate void BFEngineOnKeyBoardKey(const BFEngine* const receiver, const PXWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo);
    PXPrivate void BFEngineOnWindowCreated(const BFEngine* const receiver, const PXWindow* sender);
    PXPrivate void BFEngineOnWindowSizeChanged(const BFEngine* const receiver, const PXWindow* sender, const size_t width, const size_t height);
    PXPrivate void BFEngineOnWindowsMouseCaptureChanged(const BFEngine* const receiver, const PXWindow* sender);

    PXPublic void BFEngineStart(BFEngine* const pxBitFireEngine);
    PXPublic void BFEngineUpdate(BFEngine* const pxBitFireEngine);
    PXPublic PXBool BFEngineIsRunning(const BFEngine* const pxBitFireEngine);
    PXPublic void BFEngineStop(BFEngine* const pxBitFireEngine);

    PXPrivate void BFEngineSceneRender(BFEngine* const pxBitFireEngine);

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