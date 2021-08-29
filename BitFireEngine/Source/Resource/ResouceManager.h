#pragma once

#include "../../../ResourceSystem/Source/ResourceType.hpp"

#include "../../../ResourceSystem/Source/Shader/Shader.h"
#include "../../../ResourceSystem/Source/Image/Image.h"
#include "../../../ResourceSystem/Source/Image/ImageWrap.h"
#include "../../../ResourceSystem/Source/Model/Model.h"
#include "../../../ResourceSystem/Source/Sound/Sound.h"
#include "../../../ResourceSystem/Source/Font/Font.h"
#include "../../../ResourceSystem/Source/Dialog/Dialog.h"
#include "../../../ResourceSystem/Source/Font/FNT/FNT.h"
#include "../../../ResourceSystem/Source/Level/Level.h"
#include "../../../ResourceSystem/Source/Game/SkyBox.h"

#include "../../../ResourceSystem/Source/Container/LinkedList.hpp"
#include "ResourceLoadMode.h"

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

        void UpdateVBOData(Model& model);


        public:
        Camera MainCamera;
        Font* DefaultFont;
        SkyBox* DefaultSkyBox;

        ResourceManager();
        ~ResourceManager();

        void UnloadAll();

        void PushToGPU(Model& model);
        void PushToGPU(Image& image);
        //void Add(Sound& sound);
        //void RegisterGPU(Font& font);

     

        Resource* Load(const char* filePathString, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);

        ResourceLoadingResult Load(Model& model, const char* filePath, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);
        ResourceLoadingResult Load(Image& image, const char* filePath, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);
        ResourceLoadingResult Load(Sound& sound, const char* filePath, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);
        ResourceLoadingResult Load(Font& font, const char* filePath, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);
        ResourceLoadingResult Load(ShaderProgram& shaderProgram, const char* filePath, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);
        ResourceLoadingResult Load(Dialog& dialog, const char* filePath, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);
        ResourceLoadingResult Load(Level& level, const char* filePath, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);

        ResourceLoadingResult Load(ShaderProgram& shaderProgram, const char* vertexShader, const char* fragmentShader, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);

        void Add(Model& model);
        void Add(Image& image);
        void Add(Font& font);
        void Add(ShaderProgram& shaderProgram);
        void Add(SkyBox& skyBox);
       
        void ModelsPhysicsApply(float deltaTime);
        void ModelsRender(float deltaTime);

        void PrintContent(bool detailed);
    };
}