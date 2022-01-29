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

#include "../../../SystemResource/Source/Async/Thread.h"
#include "../../../SystemResource/Source/Async/AsyncLock.h"

#include "ResourceLoadMode.h"

#include "../../../SystemResource/Source/Math/Physic/Collider.h"
#include "../../../SystemResource/Source/Game/Sprite.h"

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
        LinkedList<Collider*> _physicList;

        unsigned int _defaultShaderID;
        unsigned int _defaultTextureID;

        // Async Locks
        AsyncLock _imageAdd;
        AsyncLock _modelAdd;





        public:
        Camera MainCamera;
        Font* DefaultFont;
        SkyBox* DefaultSkyBox;

        ShaderProgram ShaderHitBox;

        BF::Model CubeHitBoxViewModel;

        ResourceManager();
        ~ResourceManager();


        Model* GetModel(unsigned int index);

        void UnloadAll();

        void PushToGPU(Model& model);
        void PushToGPU(Image& image);
        //void Add(Sound& sound);
        //void RegisterGPU(Font& font);

        void CheckUncachedData();

        Resource* Load(const wchar_t* filePathString);

        //void Load(Sprite& sprite, const char* model, const char* texturePath);
        Matrix4x4<float> TransformBoundingBox(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, bool half);


        static ThreadFunctionReturnType LoadResourceAsync(void* resourceAdress);

        void Load(Model& model);
        void Load(Model& model, const wchar_t* filePath);
        void Load(Image& image);
        void Load(Image& image, const wchar_t* filePath);
        void Load(Sound& sound, const wchar_t* filePath);
        void Load(Font& font, const wchar_t* filePath);
        void Load(ShaderProgram& shaderProgram, const wchar_t* filePath);
        void Load(Dialog& dialog, const wchar_t* filePath);
        void Load(Level& level, const wchar_t* filePath);
        void Load(ShaderProgram& shaderProgram, const wchar_t* vertexShader, const wchar_t* fragmentShader);
        void Load
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

        void Add(Sprite& sprite);
        void Add(Model& model, bool loadAsynchronously = true);
        void Add(Model& model, const wchar_t* filePath, bool loadAsynchronously = true);
        void Add(Image& image, bool loadAsynchronously = true);
        void Add(Image& image, const wchar_t* filePath, bool loadAsynchronously = true);
        void Add(Font& font);
        void Add(ShaderProgram& shaderProgram);
        void Add(SkyBox& skyBox);
        void Add(Collider* collider);

        void ModelsPhysicsApply(float deltaTime);

        void ModelsRender(float deltaTime);
        void BoundingBoxRender(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, Vector3<float> color);

        void PrintContent(bool detailed);
    };
}