#pragma once

#include <Graphic/Graphic.h>
#include <Graphic/OpenGL/OpenGL.h>
#include <Async/PXLock.h>
#include <Async/PXThread.h>
#include <Graphic/PXCamera.h>
#include <OS/PXWindow.h>
#include <Time/PXTime.h>
#include <Container/LinkedList/PXLinkedList.h>

// Resource System
#include <Format/Font.h>
#include <Format/Image.h>

#include "../Level/Level.h"
#include "../Physic/Collider.h"
#include "InputContainer.h"

namespace BF
{
    class BitFireEngine;

    typedef void (*UpdateUIEvent)(const BitFireEngine* bitFireEngine);
    typedef void (*StartUpEvent)(BitFireEngine* const bitFireEngine);
    typedef void (*ShutDownEvent)(const BitFireEngine* bitFireEngine);
    typedef void (*UpdateGameLogicEvent)(const BitFireEngine* bitFireEngine, const float deltaTime);
    typedef void (*UpdateInputEvent)(BitFireEngine* const bitFireEngine, BF::InputContainer& input);

	class BitFireEngine// : protected IWindowListener
	{
		private:
		//---[Elements}---------------------------------
        PXTime _lastUpdate;

		float _deltaTime;

        InputContainer _inputContainer;

        //Queue<> Engine Event
		//----------------------------------------------

        // Resources
        PXLinkedListFixed _renderList; // PXRenderable
        PXLinkedListFixed _textureList; // PXTexture
        //LinkedList<AudioClip*> _audioClipList;

        //LinkedList<Sound*> _soundList;
        PXLinkedListFixed _fontList; // PXFont
        PXLinkedListFixed _shaderProgramList; // ShaderProgram;
        //LinkedList<Dialog*> _dialogList;
        //LinkedList<Level*> _levelList;
        //LinkedList<Collider*> _physicList;
        //---------------

        // Render -runtime info
        unsigned int _lastUsedShaderProgram;
        unsigned int _defaultShaderID;
        unsigned int _defaultTextureID;
        //-------------------------

        // Sound
        //ALCdevice* _audioDevice;
        //ALCcontext* _audioContext;
        //----

        // ASYNC LOCKS
        PXLock _imageAdd;
        PXLock _modelAdd;
        //-------------------------




       // static void GLAPIENTRY ErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

        static void OnMouseButton(const void* const receiver, const PXWindow* sender, const MouseButton mouseButton, const ButtonState buttonState);
        static void OnMouseMove(const void* const receiver, const PXWindow* sender, const Mouse* mouse);
        static void OnKeyBoardKey(const void* const receiver, const PXWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo);
        static void OnWindowCreated(const void* const receiver, const PXWindow* sender);
        static void OnWindowSizeChanged(const void* const receiver, const PXWindow* sender, const size_t width, const size_t height);
        static void OnWindowsMouseCaptureChanged(const void* const receiver, const PXWindow* sender);

#if defined(OSUnix)
        static void OnSystemSignal(int signalID);
#elif defined(OSWindows)
        static void __CRTDECL OnSystemSignal(int signalID);
#endif

		void UpdateInput(InputContainer& input);

        //---------------------------------------------------------------------

		public:
        PXWindow _mainWindow;

		bool IsRunning;
        PXCamera MainCamera;
        PXFont* DefaultFont;
        PXSkyBox* DefaultSkyBox;

        UpdateUIEvent UpdateUICallBack;
        StartUpEvent StartUpCallBack;
        ShutDownEvent ShutDownCallBack;
        UpdateGameLogicEvent UpdateGameLogicCallBack;
        UpdateInputEvent UpdateInputCallBack;


		BitFireEngine();

        void Start();
		void Update();
		void Stop();
  
        void MakeRectangle(PXRenderable& renderable);

        static PXThreadResult LoadResourceAsync(void* resourceAdress);

      /*  ActionResult Load(Resource* resource, const wchar_t* filePath, const bool loadAsynchronously = true); */
        ActionResult Load(Level& level, const wchar_t* filePath, const bool loadAsynchronously = true);


        ActionResult Load(PXFont& font, const wchar_t* filePath, bool loadAsynchronously = true);
        ActionResult Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath);

        // Model
        ActionResult Load(PXModel& model, const wchar_t* filePath, const bool loadAsynchronously = true);
        ActionResult Load(PXRenderable& renderable, PXModel* model, const wchar_t* filePath, bool loadAsynchronously = true);
        ActionResult Load(PXRenderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize);

        // Texture
        ActionResult Load(Image& image, const wchar_t* filePath, bool loadAsynchronously = true);
       
        
        ActionResult Load(PXTexture& texture, const wchar_t* filePath, bool loadAsynchronously = true);
      //  ActionResult Load(Sprite& sprite, const wchar_t* filePath);

        // Audio
       // ActionResult Load(Sound& sound, const wchar_t* filePath, const bool loadAsynchronously = true);
       // ActionResult Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously = true);


        ActionResult Load(Collider* collider);
        ActionResult Load
        (
            PXSkyBox& skyBox,
            const wchar_t* shaderVertex,
            const wchar_t* shaderFragment,
            const wchar_t* textureRight,
            const wchar_t* textureLeft,
            const wchar_t* textureTop,
            const wchar_t* textureBottom,
            const wchar_t* textureBack,
            const wchar_t* textureFront
        );

        void UnloadAll();

        void ModelsPhysicsApply(float deltaTime);

        void ModelsRender(const float deltaTime);

        void PrintContent(bool detailed);
	};
}
