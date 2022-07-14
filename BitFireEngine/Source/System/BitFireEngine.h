#pragma once

#include "IBitFireEngineListener.hpp"

// OpenAL - Sound
//#include <AL/al.h>
//#include <AL/alc.h>

// OpenGL - Graphics
#include <GL/glew.h>
#include <Graphic/OpenGL/OpenGL.h>


// Resource System
#include <Time/StopWatch.h>
#include <Async/Thread.h>
#include <Async/AsyncLock.h>
#include <Camera/Camera.h>
#include <Container/LinkedList.hpp>
#include <Media/Font/Font.h>
#include <Math/Geometry/Matrix4x4.hpp>
#include <Shader/GLSL/ShaderType.h>
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

namespace BF
{
	class BitFireEngine// : protected IWindowListener
	{
		private:
		//---[Elements}---------------------------------
		StopWatch _stopWatch;
        Window _mainWindow;
		float _deltaTime;
        static BitFireEngine* _instance;

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

        static void OnMouseButton(const MouseButton mouseButton, const ButtonState buttonState);
        static void OnMouseMove(const double positionX, const double positionY, const double deltaX, const double deltaY);
        static void OnKeyBoardKey(const KeyBoardKeyInfo keyBoardKeyInfo);
        static void OnWindowCreated(Window& window);
        static void OnWindowSizeChanged(const size_t width, const size_t height);
        static void OnWindowsMouseCaptureChanged();


        static void __CRTDECL OnSystemSignal(int signalID);

		void UpdateInput(InputContainer& input);

        //---------------------------------------------------------------------

		public:
		bool IsRunning;
        Camera MainCamera;
        Font* DefaultFont;
        SkyBox* DefaultSkyBox;
		IBitFireEngineListener* _callbackListener;

		BitFireEngine();

        static BitFireEngine* Instance() { return _instance; }

		void SetCallBack(IBitFireEngineListener* callbackListener);

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
        void Register(Font& font);
        void Register(AudioClip& audioClip, const Sound& sound);

        void Use(Texture& texture);
        void Use(const ImageType imageType, const int textureID);
        void Use(Renderable& renderable);
        void Use(SkyBox& skyBox);
        void Use(const AudioSource& audioSource, const AudioClip& audioClip);

        void Update(const AudioSource& audioSource);

        void UnRegister(AudioSource& audioSource);
        void UnRegister(AudioClip& audioClip);



        static ThreadFunctionReturnType LoadResourceAsync(void* resourceAdress);

        FileActionResult Load(Resource* resource, const wchar_t* filePath, const bool loadAsynchronously = true);
        FileActionResult Load(Level& level, const wchar_t* filePath, const bool loadAsynchronously = true);


        FileActionResult Load(Font& font, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath);

        // Model
        FileActionResult Load(Model& model, const wchar_t* filePath, const bool loadAsynchronously = true);
        FileActionResult Load(Renderable& renderable, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize);

        // Texture
        FileActionResult Load(Image& image, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(Texture& texture, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(Sprite& sprite, const wchar_t* filePath);

        // Audio
        FileActionResult Load(Sound& sound, const wchar_t* filePath, const bool loadAsynchronously = true);
        FileActionResult Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously = true);


        FileActionResult Load(Collider* collider);
        FileActionResult Load
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
