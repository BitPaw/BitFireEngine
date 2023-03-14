#pragma once

#include <Graphic/PXGraphic.h>
#include <OS/Thread/PXLock.h>
#include <OS/Thread/PXThread.h>
#include <OS/Window/PXWindow.h>
#include <OS/Time/PXTime.h>
#include <Container/LinkedList/PXLinkedList.h>
#include <Format/PXFont.h>
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
     
        //-------------------------




       // static void GLAPIENTRY ErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

        static void OnMouseButton(const void* const receiver, const PXWindow* sender, const MouseButton mouseButton, const ButtonState buttonState);
        static void OnMouseMove(const void* const receiver, const PXWindow* sender, const Mouse* mouse);
        static void OnKeyBoardKey(const void* const receiver, const PXWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo);
        static void OnWindowCreated(const void* const receiver, const PXWindow* sender);
        static void OnWindowSizeChanged(const void* const receiver, const PXWindow* sender, const size_t width, const size_t height);
        static void OnWindowsMouseCaptureChanged(const void* const receiver, const PXWindow* sender);


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

      /*  PXActionResult Load(Resource* resource, const wchar_t* filePath, const bool loadAsynchronously = true); */
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
	};
}
