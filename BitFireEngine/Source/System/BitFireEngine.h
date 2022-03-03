#pragma once

#include "IBitFireEngineListener.hpp"

// OpenAL - Sound
//#include <AL/al.h>
//#include <AL/alc.h>

// OpenGL - Graphics
#include <GL/glew.h>

// Resource System
#include <Math/Geometry/Matrix4x4.hpp>
#include <Time/StopWatch.h>
#include <Async/Thread.h>
#include <Async/AsyncLock.h>
#include <Container/LinkedList.hpp>
#include <Font/Font.h>
#include <Sound/Sound.h>
#include <Model/Model.h>

//#include "Window/Window.h"

#include "../Resource/SkyBox.h"
#include "../Player/Player.h"
#include "../Sound/AudioClip.h"
#include "../Sound/AudioSource.h"
#include "../Resource/Sprite.h"
#include "../Camera/Camera.h"
#include "../Physic/Collider.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderType.h"
#include "../Shader/ShaderProgram.h"

#include <Window/Window.h>

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
        static void OnMouseMove(const short x, const short y);
        static void OnKeyBoardKey(const KeyBoardKeyInfo keyBoardKeyInfo);
        static void OnWindowCreated(Window& window);
        static void OnWindowSizeChanged(const unsigned int width, const unsigned int height);
        static void OnWindowsMouseCaptureChanged();


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

        FileActionResult Load(Renderable& renderable, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize);
        FileActionResult Load(Texture& texture, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(Font& font, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously = true);
        FileActionResult Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath);
        FileActionResult Load
        (
            Sprite& sprite,
            const wchar_t* filePath
        );
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

        void ModelsRender(float deltaTime);
        void BoundingBoxRender(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, Vector3<float> color);

        void PrintContent(bool detailed);



        // Convert
        static const unsigned short ToRenderMode(const RenderMode renderMode);
        
        static ShaderType ToShaderType(unsigned int token);
        static unsigned int ToShaderType(ShaderType shaderType);

        static ImageDataFormat ToImageFormat(unsigned int token);
        static unsigned int ToImageFormat(ImageDataFormat imageFormat);

        static ImageType ToImageType(unsigned int token);
        static unsigned int ToImageType(ImageType imageType);

        static int ImageWrapToOpenGLFormat(ImageWrap imageWrap);
        static int ImageLayoutToOpenGLFormat(ImageLayout layout);

        unsigned int ToChannalFormat(const unsigned short numerOfChannels, const unsigned short bitsPerSample);

        static const char* ShaderTypeToString(int type);
	};
}