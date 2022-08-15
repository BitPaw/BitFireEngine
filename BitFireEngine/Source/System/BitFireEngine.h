#pragma once

// OpenAL - Sound
//#include <AL/al.h>
//#include <AL/alc.h>

// OpenGL - Graphics
#include <GL/glew.h>
#include <Graphic/OpenGL/OpenGL.h>


// Resource System
#include <File/Font.h>
#include <File/Image.h>

#include <Time/StopWatch.h>
#include <Async/Thread.h>
#include <Async/AsyncLock.h>
#include <Camera/Camera.h>
#include <Container/LinkedList.hpp>
#include <Math/Geometry/Matrix4x4.hpp>
#include <Video/Shader.h>
#include <Model/Model.h>
#include <Media/Sound/AudioClip.h>
#include <Media/Sound/AudioSource.h>
#include <Media/Sound/Sound.h>

//#include "Window/Window.h"

//#include "../Resource/SkyBox.h"
#include "../Player/Player.h"

//#include "../Resource/Sprite.h"

#include <Window/Window.h>

#include "../Level/Level.h"
#include "../Physic/Collider.h"
#include <Graphic/OpenGL/Renderable.h>
#include <Graphic/OpenGL/SkyBox.h>
#include <Graphic/OpenGL/Sprite.h>
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
		StopWatch _stopWatch;

		float _deltaTime;

        InputContainer _inputContainer;

        //Queue<> Engine Event
		//----------------------------------------------

        // Resources
        LinkedList<Renderable*> _renderList;
        LinkedList<Texture*> _textureList;
        LinkedList<AudioClip*> _audioClipList;

        //LinkedList<Sound*> _soundList;
        LinkedList<Font*> _fontList;
        LinkedList<ShaderProgram*> _shaderProgramList;
        //LinkedList<Dialog*> _dialogList;
        //LinkedList<Level*> _levelList;
        LinkedList<Collider*> _physicList;
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
        AsyncLock _imageAdd;
        AsyncLock _modelAdd;
        //-------------------------




        static void GLAPIENTRY ErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

        static void OnMouseButton(const void* const receiver, const CWindow* sender, const MouseButton mouseButton, const ButtonState buttonState);
        static void OnMouseMove(const void* const receiver, const CWindow* sender, const Mouse* mouse);
        static void OnKeyBoardKey(const void* const receiver, const CWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo);
        static void OnWindowCreated(const void* const receiver, const CWindow* sender);
        static void OnWindowSizeChanged(const void* const receiver, const CWindow* sender, const size_t width, const size_t height);
        static void OnWindowsMouseCaptureChanged(const void* const receiver, const CWindow* sender);

#if defined(OSUnix)
        static void OnSystemSignal(int signalID);
#elif defined(OSWindows)
        static void __CRTDECL OnSystemSignal(int signalID);
#endif

		void UpdateInput(InputContainer& input);

        //---------------------------------------------------------------------

		public:
        Window _mainWindow;

		bool IsRunning;
        Camera MainCamera;
        Font* DefaultFont;
        SkyBox* DefaultSkyBox;

        UpdateUIEvent UpdateUICallBack;
        StartUpEvent StartUpCallBack;
        ShutDownEvent ShutDownCallBack;
        UpdateGameLogicEvent UpdateGameLogicCallBack;
        UpdateInputEvent UpdateInputCallBack;


		BitFireEngine();

        void Start();
		void Update();
		void Stop();

       // ShaderProgram ShaderHitBox;

       // BF::Model CubeHitBoxViewModel;

        //void Load(Sprite& sprite, const char* model, const char* texturePath);
      //  Matrix4x4<float> TransformBoundingBox(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, bool half);


        void Register(Texture& texture);
        void Register(TextureCube& textureCube);
        void Register(Renderable& renderable, const Model& model);
        void Register(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize);
        void Register(SkyBox& skyBox);
        bool Register(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath);
        void Register(AudioSource& audioSource);
        void Register(CFont& font);
        void Register(AudioClip& audioClip, const Sound& sound);

        void Use(Texture& texture);
        void Use(const ImageType imageType, const int textureID);
        void Use(Renderable& renderable);
        void Use(SkyBox& skyBox);
        void Use(const AudioSource& audioSource, const AudioClip& audioClip);

        void Update(const AudioSource& audioSource);

        void UnRegister(AudioSource& audioSource);
        void UnRegister(AudioClip& audioClip);


        void MakeRectangle(Renderable& renderable);


        static ThreadResult LoadResourceAsync(void* resourceAdress);

        ActionResult Load(Resource* resource, const wchar_t* filePath, const bool loadAsynchronously = true);
        ActionResult Load(Level& level, const wchar_t* filePath, const bool loadAsynchronously = true);


        ActionResult Load(CFont& font, const wchar_t* filePath, bool loadAsynchronously = true);
        ActionResult Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath);

        // Model
        ActionResult Load(Model& model, const wchar_t* filePath, const bool loadAsynchronously = true);
        ActionResult Load(Renderable& renderable, const wchar_t* filePath, bool loadAsynchronously = true);
        ActionResult Load(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize);

        // Texture
        ActionResult Load(Image& image, const wchar_t* filePath, bool loadAsynchronously = true);
        ActionResult Load(Texture& texture, const wchar_t* filePath, bool loadAsynchronously = true);
        ActionResult Load(Sprite& sprite, const wchar_t* filePath);

        // Audio
        ActionResult Load(Sound& sound, const wchar_t* filePath, const bool loadAsynchronously = true);
        ActionResult Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously = true);


        ActionResult Load(Collider* collider);
        ActionResult Load
        (
            SkyBox& skyBox,
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
        void BoundingBoxRender(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, Vector3<float> color);

        void PrintContent(bool detailed);



        // Convert
        static const unsigned short ToRenderMode(const RenderMode renderMode);

        static const ShaderType ToShaderType(const OpenGLID token);
        static const OpenGLID ToShaderType(const ShaderType shaderType);

        static const ImageDataFormat ToImageFormat(const OpenGLID token);
        static const OpenGLID ToImageFormat(const ImageDataFormat imageFormat);

        static const ImageType ToImageType(const OpenGLID token);
        static const OpenGLID ToImageType(const ImageType imageType);

        static int ImageWrapToOpenGLFormat(ImageWrap imageWrap);
        static int ImageLayoutToOpenGLFormat(ImageLayout layout);

        unsigned int ToChannalFormat(const unsigned short numerOfChannels, const unsigned short bitsPerSample);

        static const char* ShaderTypeToString(int type);
	};
}
