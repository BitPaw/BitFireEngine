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
#include <Engine/PXEngine.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct BFEngineUIElementCollisionCheckInfo_
    {
        float MousePosition[4];

        PXUIElement* OverlappedElement; // Element beeing under the current selected one. Is NULL when no object is under current.
        PXUIElement* CurrentElement; // Element beeing selected
    }
    BFEngineUIElementCollisionCheckInfo;

    typedef struct BFEngine_
    {
        PXEngine Engine;


        PXEngineStartUpEvent OnStartUp;
        PXEngineShutDownEvent OnShutDown;
        PXEngineUserUpdateEvent OnUserUpdate;
        PXEngineNetworkUpdateEvent OnNetworkUpdate;
        PXEngineGameUpdateEvent OnGameUpdate;
        PXEngineRenderUpdateEvent OnRenderUpdate;




        BFEngineUIElementCollisionCheckInfo CollisionCheckInfo;


        // Render -runtime info
        unsigned int _lastUsedShaderProgram;
        unsigned int _defaultShaderID;
        unsigned int _defaultTextureID;
        //---------------------------------------------------------------------

        PXController Controller;

        PXCamera CameraPlayer;

        PXFont* DefaultFont;
        PXSkyBox* DefaultSkyBox;

        PXModel pxModelTEST;
    }
    BFEngine;

    PXPublic void PXAPI BFEngineConstruct(BFEngine* const pxBitFireEngine);

    PXPrivate void PXAPI BFEngineOnWindowsMouseCaptureChanged(const BFEngine* const receiver, const PXWindow* sender);

    PXPublic void PXAPI BFEngineStart(BFEngine* const bfEngine, PXEngine* const pxEngine);
    PXPublic void PXAPI BFEngineUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine);
    PXPublic void PXAPI BFEngineStop(BFEngine* const bfEngine, PXEngine* const pxEngine);

    PXPrivate void PXAPI BFEngineSceneRender(BFEngine* const bfEngine, PXEngine* const pxEngine);

    PXPrivate void PXAPI BFEngineRenderScene(BFEngine* const bfEngine);

    PXPrivate void PXAPI BFEngineUIElementCollision(BFEngine* const bfEngine, PXUIElement* const pxUIElement);

    PXPrivate void PXAPI BFEngineUIElementRender(BFEngine* const bfEngine, PXUIElement* const pxUIElement);



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
