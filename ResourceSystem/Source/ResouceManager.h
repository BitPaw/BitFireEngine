#pragma once

#include "ResourceType.hpp"

#include "Shader/Shader.h"
#include "Image/Image.h"
#include "Image/ImageWrap.h"
#include "Model/Model.h"
#include "Sound/Sound.h"
#include "Font/Font.h"
#include "Dialog/Dialog.h"
#include "Font/FNT/FNT.h"
#include "Level/Level.h"

#include "Container/LinkedList.hpp"
#include "../../BitFireEngine/Source/Graphics/Camera/FirstPersonCamera.h"

namespace BF
{
    /*
    Stores resources and manages them to the GPU.
    */
    class ResourceManager
    {
        private:
        unsigned int _lastUsedShaderProgram;

        LinkedList<Model*> _modelList;
        LinkedList<Image*> _imageList;
        LinkedList<Sound*> _soundList;
        LinkedList<Font*> _fontList;
        LinkedList<ShaderProgram*> _shaderProgramList;
        LinkedList<Dialog*> _dialogList;
        LinkedList<Level*> _levelList;

        unsigned int _defaultShaderID;
        unsigned int _defaultTextureID;

        int ImageWrapToOpenGLFormat(ImageWrap imageWrap);
        int ImageLayoutToOpenGLFormat(ImageLayout layout);

        void UpdateVBOData(Model& model);


        public:
        FirstPersonCamera MainCamera;
        Font* DefaultFont;

        ResourceManager();
        ~ResourceManager();

        void UnloadAll();

        void PushToGPU(Model& model);
        void PushToGPU(Image& image);
        //void Add(Sound& sound);
        //void RegisterGPU(Font& font);


        Resource* Load(const char* filePathString);
        Resource* Load(AsciiString& filePath);

        ErrorCode Load(Model& model, const char* filePath);
        ErrorCode Load(Image& image, const char* filePath);
        ErrorCode Load(Sound& sound, const char* filePath);
        ErrorCode Load(Font& font, const char* filePath);
        ErrorCode Load(ShaderProgram& shaderProgram, const char* filePath);
        ErrorCode Load(Dialog& dialog, const char* filePath);
        ErrorCode Load(Level& level, const char* filePath);

        void Add(Model& model);
        void Add(Image& image);
        void Add(Font& font);

        unsigned int AddShaderProgram(const char* vertexShader, const char* fragmentShader);
        unsigned int AddShaderProgram(AsciiString& vertexShader, AsciiString& fragmentShader);

        void RenderModels(GameTickData& gameTickData);

        void PrintContent(bool detailed);
    };
}