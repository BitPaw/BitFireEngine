#pragma once

#include "../../../SystemResource/Source/ResourceType.hpp"

#include "../../../SystemResource/Source/Shader/Shader.h"
#include "../../../SystemResource/Source/Image/Image.h"
#include "../../../SystemResource/Source/Image/ImageWrap.h"
#include "../../../SystemResource/Source/Model/Model.h"
#include "../../../SystemResource/Source/Sound/Sound.h"
#include "../../../SystemResource/Source/Font/Font.h"
#include "../../../SystemResource/Source/Dialog/Dialog.h"
#include "../../../SystemResource/Source/Font/FNT/FNT.h"
#include "../../../SystemResource/Source/Level/Level.h"
#include "../../../SystemResource/Source/Game/SkyBox.h"
#include "../../../SystemResource/Source/Container/LinkedList.hpp"
#include "../../../SystemResource/Source/Async/AsyncLock.h"

#include "ResourceLoadMode.h"

#include <thread>

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

        // Async Locks
        AsyncLock _imageAdd;
        AsyncLock _modelAdd;

        public:
        Camera MainCamera;
        Font* DefaultFont;
        SkyBox* DefaultSkyBox;

        ResourceManager();
        ~ResourceManager();

        Model* GetModel(unsigned int index);

        void UnloadAll();

        void PushToGPU(Model& model);
        void PushToGPU(Image& image);
        //void Add(Sound& sound);
        //void RegisterGPU(Font& font);

        void CheckUncachedData();

        Resource* Load(const char* filePathString, ResourceLoadMode ResourceLoadMode = ResourceLoadMode::LoadToCacheAndUse);

        void LoadAsync(const char* filePath);

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