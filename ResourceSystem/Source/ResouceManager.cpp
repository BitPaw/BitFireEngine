#include "ResouceManager.h"
#include "Font/FNT/FNTPage.h"
#include "File/File.h"
#include "../../RenderSystem/Source/OpenGLAPI.h"
#include "Async/Thread.h"
#include "Async/AsyncLock.h"
#include <thread>

void BF::ResourceManager::UpdateVBOData(Model& model)
{
    LinkedMesh& mesh = model.GlobalMesh;
    List<float>& vertexData = model.RenderInformation.VertexData;
    List<unsigned int>& indexData = model.RenderInformation.IndexData;

    unsigned int dataIndex = 0;// renderInformation->VertexDataPosition;
    //unsigned int indiceIndex = renderInformation->IndiceIndex;

   // printf("Update: <%p> <%.2u> %s\n", renderInformation, renderInformation->RenderID, &(renderInformation->RenderModel->ModelName[0]));

    if (model.RenderInformation.IndexData.Size() == 0)
    {

        printf("[Could not UpdateVBOData(), index data empty or not set.]\n");
        return;
    }

    for (unsigned int i = 0; i < mesh.IndexList.Size(); i++)
    {
        //renderInformation->IndexData[indiceIndex++] = i;// +renderInformation->IndexOffset;
        MeshIndexData* indexList = mesh.IndexList[i];

        Vector4<float> defaultColor(1, 1, 1, 1);
        Point<float> defaultTexturepoint;
        Position<float> normalPosition;

        Vertex* vertex = nullptr;
        Vector4<float>* color = nullptr;
        Position<float>* position = nullptr;
        Position<float>* normal = nullptr;
        Point<float>* texture = nullptr;

        unsigned int vertexIndex = indexList->VertexPositionID;
        unsigned int textureIndex = indexList->TexturePointID;
        unsigned int normalIndex = indexList->NormalVectorID;

        if (vertexIndex == -1)
        {
            throw "Invalid Vertex";
        }

        vertex = mesh.VertexList[vertexIndex];

        bool hasColor = !model.ColorList.IsEmpty() && vertex->ColorID != -1;
        bool hasNormal = !mesh.NormalPointList.IsEmpty();
        bool hasTexture = !mesh.TexturePointList.IsEmpty();

        color = hasColor ? &model.ColorList[vertex->ColorID] : &defaultColor;
        normal = hasNormal ? model.GlobalMesh.NormalPointList[normalIndex] : &normalPosition;
        texture = hasTexture ? model.GlobalMesh.TexturePointList[textureIndex] : &defaultTexturepoint;

        position = &vertex->CurrentPosition;

        indexData[i] = i;

        vertexData[dataIndex++] = position->X;
        vertexData[dataIndex++] = position->Y;
        vertexData[dataIndex++] = position->Z;

        vertexData[dataIndex++] = normal->X;
        vertexData[dataIndex++] = normal->Y;
        vertexData[dataIndex++] = normal->Z;

        void* destination = &vertexData[dataIndex++];
        void* source = color;

        memcpy(destination, source, 4 * sizeof(float));

        dataIndex += 3;

        vertexData[dataIndex++] = texture->X;
        vertexData[dataIndex++] = texture->Y;
    }

    //renderInformation->VertexDataLength = dataIndex - renderInformation->VertexDataPosition -1;
    //renderInformation->IndiceIndexLength = indiceIndex - renderInformation->IndiceIndex-1;
}

BF::ResourceManager::ResourceManager()
{
    _lastUsedShaderProgram = -1;
    _defaultShaderID = 0;
    _defaultTextureID = 0;

    DefaultFont = nullptr;
}

BF::ResourceManager::~ResourceManager()
{
    UnloadAll();
}

void BF::ResourceManager::UnloadAll()
{

}

void BF::ResourceManager::PushToGPU(Model& model)
{
    unsigned int& modelID = model.ID;
    bool isAlreadyLinked = modelID != -1;
    ModelRenderInformation& renderInfo = model.RenderInformation;

    if (isAlreadyLinked)
    {
        UpdateVBOData(model);

        if (renderInfo.VertexData.Size() != 0)
        {
            OpenGLAPI::VertexArrayUpdate(renderInfo.VertexBufferID, renderInfo.VertexData.SizeInBytes(), &renderInfo.VertexData[0]);
        }
    }
    else
    {
        modelID = _modelList.Size();

        renderInfo.VertexData.ReSize(model.GlobalMesh.IndexList.Size() * (3 + 3 + 4 + 2));
        renderInfo.IndexData.ReSize(model.GlobalMesh.IndexList.Size());

        UpdateVBOData(model);

        // Allocate GPU Buffer
        OpenGLAPI::VertexArrayDefine(&renderInfo.VertexArrayID);
        OpenGLAPI::VertexArrayBind(renderInfo.VertexArrayID);

        OpenGLAPI::VertexDataDefine(&renderInfo.VertexBufferID, sizeof(float) * renderInfo.VertexData.Size(), &renderInfo.VertexData[0]);

        int sizeList[4] = { 3,3,4,2 };

        OpenGLAPI::VertexAttributeArrayDefine(sizeof(float), 4, sizeList);

        OpenGLAPI::IndexDataDefine(&renderInfo.IndexBufferID, renderInfo.IndexData.SizeInBytes(), &renderInfo.IndexData[0]);
    }
}

void BF::ResourceManager::PushToGPU(Image& image)
{
    OpenGLAPI::RegisterImage(image);
}

BF::Resource* BF::ResourceManager::Load(const char* filePathString, ResourceLoadMode resourceLoadMode)
{
    Resource* resource = nullptr;
    ResourceType resourceType = ResourceType::Unknown;
    File file(filePathString);
    AsciiString fileExtension(&file.Extension[0]);
    bool doesFileExist = file.DoesFileExist();
    ErrorCode errorCode = doesFileExist ? ErrorCode::Undefined : ErrorCode::FileNotFound;

    AsciiString filePath(filePathString);

    if (doesFileExist)
    {
        {
            bool isModel = Model::CheckFileExtension(file.Extension) != ModelType::UnKown;
            bool isImage = Image::CheckFileExtension(fileExtension) != ImageFileExtension::Unkown;
            bool isSound = false;
            bool isFont = Font::IsFontFile(file.Extension);
            bool isShader = false;
            bool isDialog = false;
            bool isLevel = fileExtension.CompareIgnoreCase("lev");

            if (isModel) resourceType = ResourceType::Model;
            if (isImage) resourceType = ResourceType::Image;
            if (isSound) resourceType = ResourceType::Sound;
            if (isFont) resourceType = ResourceType::Font;
            if (isShader) resourceType = ResourceType::Shader;
            if (isDialog) resourceType = ResourceType::Dialog;
            if (isLevel) resourceType = ResourceType::Level;
        }

        printf("[i][Resource] Load <%s> from <%s>.\n", ResourceTypeToString(resourceType), filePathString);

        switch (resourceType)
        {
            case ResourceType::Dialog:
            {             
                Dialog* dialog = new Dialog();
                errorCode = Load(*dialog, filePathString);
                break;
            }            

            case ResourceType::Font:
            {
                Font* font = new Font();
                errorCode = Load(*font, filePathString);

                if (errorCode == ErrorCode::NoError)
                {
                    Add(*font);
                }

                break;
            }

            case ResourceType::Image:
            {
                Image* image = new Image();
                errorCode = Load(*image, filePathString);

                if (errorCode == ErrorCode::NoError)
                {
                    Add(*image);
                }

                break;
            }

            case ResourceType::Level:
            {        
                Level* level = new Level();
                errorCode = Load(*level, filePathString);
                break;
            }

            case ResourceType::Model:
            {        
                Model* model = new Model();
                errorCode = Load(*model, filePathString);
                
                if (errorCode == ErrorCode::NoError)
                {
                    Add(*model);
                }

                break;
            }
            case ResourceType::Shader:
            {
       
                break;
            }
            case ResourceType::Sound:
            {
                Sound* sound = new Sound();
                errorCode = Load(*sound, filePathString);
                break;
            }
        }
    }

    switch (errorCode)
    {
        case ErrorCode::NoError:
        {
            break;
        }
        case ErrorCode::FileNotFound:
        {
            printf("[Error] File is missing at path <%s>\n", &filePath[0]);
            break;
        }
        case ErrorCode::LoadingFailed:
        {
            printf("[Error] Loading file failed at path <%s>\n", &filePath[0]);
            break;
        }
        case ErrorCode::SavingFailed:
        {
            printf("[Error] File saving failed at path <%s>\n", &filePath[0]);
            break;
        }
        case ErrorCode::Undefined:
        {
            printf
            (
                "[Warning] Fileextension <%s> is not supported or reconised by the system!\n"
                "          Resource at path <%s> could not be loaded\n",
                &fileExtension[0],
                &filePath[0]
            );
            break;
        }
    }

    return resource;
}

BF::ErrorCode BF::ResourceManager::Load(Model& model, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    printf("[>][Resource][Model] Loading from <%s>\n", filePath);

    ErrorCode errorCode = model.Load(filePath);

    if (errorCode == ErrorCode::NoError)
    {
        for (unsigned int i = 0; i < model.MaterialList.Size(); i++)
        {
            Material& material = model.MaterialList[i];
            Image* image = new Image();

            ErrorCode imageErrorCode = Load(*image, material.TextureFilePath);

            if (imageErrorCode == ErrorCode::NoError)
            {
                material.Texture = image;

                Add(*image);
            }
        }
    }

    return errorCode;
}

BF::ErrorCode BF::ResourceManager::Load(Image& image, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    printf("[>][Resource][Image] Loading from <%s>\n", filePath);

    ErrorCode errorCode = image.Load(filePath);

    if (errorCode == ErrorCode::NoError)
    {    
        Add(image);
    }

    return errorCode;
}

BF::ErrorCode BF::ResourceManager::Load(Sound& resource, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    printf("[>][Resource][Sound] Loading from <%s>\n", filePath);

    return ErrorCode();
}

BF::ErrorCode BF::ResourceManager::Load(Font& font, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    printf("[>][Resource][Font] Loading from <%s>\n", filePath);

    ErrorCode errorCode = font.Load(filePath);

    if (errorCode == ErrorCode::NoError)
    {
        for (unsigned int i = 0; i < font.AdditionalResourceListSize; i++)
        {
            AsciiString path(filePath);
            char* resourcePath = &font.AdditionalResourceList[i];          
            char textureFilePath[50];
            memset(textureFilePath, 0, 50);

            int resourcePathSize = strlen(resourcePath);
            int startIndex = path.FindLast('/') + 1;

            memcpy(textureFilePath, &filePath[0], startIndex);

            int length = strlen(textureFilePath);

            memcpy(&textureFilePath[length], &resourcePath[0], resourcePathSize);
            
            // Does file exist?

            font.Texture = new Image();

           // errorCode = ErrorCode::FileNotFound;
            errorCode = Load(*font.Texture, textureFilePath);

            if (errorCode != ErrorCode::NoError)
            {
                delete font.Texture;
                font.Texture = nullptr;
            }
        }

        font.ID = _fontList.Size();
        font.FilePathSet(&filePath[0]);   
    }

    return errorCode;
}

BF::ErrorCode BF::ResourceManager::Load(ShaderProgram& resource, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    printf("[>][Resource][ShaderProgram] Loading from <%s>\n", filePath);

    return ErrorCode::NoError;
}

BF::ErrorCode BF::ResourceManager::Load(Dialog& resource, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    printf("[>][Resource][Dialog] Loading from <%s>\n", filePath);
    return ErrorCode::NoError;
}

BF::ErrorCode BF::ResourceManager::Load(Level& level, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    List<AsciiString> fileLines;
    File file(filePath);
    ErrorCode errorCode = ErrorCode::LoadingFailed;

    printf("[>][Resource][Level] Loading from <%s>\n", filePath);

    const char _modelToken = 'O';
    const char _textureToken = 'T';
    const char _musicToken = 'M';
    const char _fontToken = 'F';
    const char _shaderToken = 'S';
    const char _dialogToken = 'D';
    const char _emptyToken = ' ';
    const char _commentToken = '#';
    unsigned int modelCounter = 0;
    unsigned int imageCounter = 0;
    unsigned int soundCounter = 0;
    unsigned int fontCounter = 0;
    unsigned int shaderCounter = 0;
    unsigned int dialogCounter = 0;
    unsigned int amountOfLines;

    file.ReadAsLines(fileLines);

    amountOfLines = fileLines.Size();

    // Step I - Count objects
    for (unsigned int i = 0; i < amountOfLines; i++)
    {
        AsciiString& line = fileLines[i];
        char character = line.GetFirstNonEmpty();

        switch (character)
        {
            case _modelToken:
                modelCounter++;
                break;

            case _textureToken:
                imageCounter++;
                break;

            case _musicToken:
                soundCounter++;
                break;

            case _fontToken:
                fontCounter++;
                break;

            case _shaderToken:
                shaderCounter++;
                break;

            case _dialogToken:
                dialogCounter++;
                break;

            case _commentToken:
            case _emptyToken:
            default:
                // Do nothinf
                break;
        }
    }

    // Step II - Reserve space
    level.ModelList.ReSize(modelCounter);
    level.ImageList.ReSize(imageCounter);
    level.SoundList.ReSize(soundCounter);
    level.FontList.ReSize(fontCounter);
    level.ShaderList.ReSize(shaderCounter);
    level.DialogList.ReSize(dialogCounter);

    modelCounter = 0;
    imageCounter = 0;
    soundCounter = 0;
    fontCounter = 0;
    shaderCounter = 0;
    dialogCounter = 0;

    // Step II - Parse and Load
    for (unsigned int i = 0; i < amountOfLines; i++)
    {
        AsciiString& line = fileLines[i];
        char* currentLine = &line[0];
        char character = line.GetFirstNonEmpty();
        char dummyBuffer[30];
        char path[120];

        switch (character)
        {
            case _modelToken:
            {
                char positionText[30];
                char rotationText[30];
                char scaleText[30];
                Position<float> position;
                Position<float> rotation;
                Position<float> scale;

                sscanf(currentLine, "%s %s %s %s %s", dummyBuffer, path, positionText, rotationText, scaleText);                

                // Get raw Data-------------------------                         

                // Replace 0|0|0 -> 0 0 0 
                for (size_t i = 0; i < positionText[i] != '\0'; i++)
                {
                    if (positionText[i] == '|')
                    {
                        positionText[i] = ' ';
                    }
                }

                for (size_t i = 0; i < rotationText[i] != '\0'; i++)
                {
                    if (rotationText[i] == '|')
                    {
                        rotationText[i] = ' ';
                    }
                }

                for (size_t i = 0; i < scaleText[i] != '\0'; i++)
                {
                    if (scaleText[i] == '|')
                    {
                        scaleText[i] = ' ';
                    }
                }

                sscanf(positionText, "%f %f %f", &position.X, &position.Y, &position.Z);
                sscanf(rotationText, "%f %f %f", &rotation.X, &rotation.Y, &rotation.Z);
                sscanf(scaleText, "%f %f %f", &scale.X, &scale.Y, &scale.Z);
                //------------------------------------------------

                // Load Model----------------
                Model* loadedModel = new Model(); 

                errorCode = Load(*loadedModel, path);

                if (loadedModel == nullptr)
                {
                    printf("[Warning] Loading failed!\n");
                    break;
                }

                level.ModelList[modelCounter++] = loadedModel;
                //-------------------

                //--[Apply Data]-------------
                loadedModel->MoveTo(position);
                loadedModel->Rotate(rotation);
                loadedModel->Scale(scale);
                loadedModel->UpdateGlobalMesh();

                Add(*loadedModel);
                //-----------------------
                break;
            }
            case _textureToken:
            {
                sscanf(currentLine, "%s %s", dummyBuffer, path);

                Image* image = new Image();

                errorCode = Load(*image, path);

                Add(*image);

                level.ImageList[imageCounter++] = image;
                break;
            }
            case _musicToken:
            {
                sscanf(currentLine, "%s %s", dummyBuffer, path);

                Sound* sound = new Sound();
                
                errorCode = Load(*sound, path);

                level.SoundList[soundCounter++] = sound;
                break;
            }
            case _fontToken:
            {
                sscanf(currentLine, "%s %s", dummyBuffer, path);

                Font* font = new Font();
                
                errorCode = Load(*font, path);          

                level.FontList[fontCounter++] = font;

                for (size_t i = 0; i < font->AdditionalResourceListSize; i++)
                {
                    font->AdditionalResourceList[i];
                }

                Add(*font);
                break;
            }
            case _shaderToken:
            {
                break;
            }
            case _dialogToken:
            {
                break;
            }
            case _commentToken:
            case _emptyToken:
            default:
                // Do nothinf
                break;
        }
    }

    return errorCode;
}

BF::ErrorCode BF::ResourceManager::Load(ShaderProgram& shaderProgram, const char* vertexShader, const char* fragmentShader, ResourceLoadMode ResourceLoadMode)
{
    shaderProgram.AddShader((char*)vertexShader, (char*)fragmentShader);
    shaderProgram.Load();

    bool validShader = OpenGLAPI::ShaderCompile(shaderProgram);

    if (validShader)
    {
        Add(shaderProgram);
    }

    return ErrorCode::NoError;
}

void BF::ResourceManager::Add(Model& model)
{
    if (!model.LoadedToGPU)
    {
        _modelList.Add(&model);

        model.LoadedToGPU = true;
    }

    PushToGPU(model);
}

void BF::ResourceManager::Add(Image& image)
{
    bool firstImage = _imageList.Size() == 0;

    if (!image.LoadedToGPU)
    {
        _imageList.Add(&image);

        image.LoadedToGPU = true;
    }

    PushToGPU(image);

    if (firstImage)
    {
        _defaultTextureID = image.ID;
    }
}

void BF::ResourceManager::Add(Font& font)
{
    bool firstImage = _fontList.Size() == 0;

    if (!font.LoadedToGPU)
    {
        _fontList.Add(&font);

        font.LoadedToGPU = true;
    }

    if (firstImage)
    {
        DefaultFont = &font;
    }
}

void BF::ResourceManager::Add(ShaderProgram& shaderProgram)
{
    bool firstShaderProgram = _shaderProgramList.Size() == 0;

    _shaderProgramList.Add(&shaderProgram);

    if (firstShaderProgram)
    {
        _defaultShaderID = shaderProgram.ID;

        MainCamera.FetchGPUReferences(_defaultShaderID);
    }
}

void BF::ResourceManager::Add(SkyBox& skyBox)
{
    

    OpenGLAPI::SkyBoxSet(skyBox);
   // OpenGLAPI::SkyBoxUse(skyBox);

    DefaultSkyBox = &skyBox;
}

void BF::ResourceManager::RenderModels(GameTickData& gameTickData)
{
    LinkedListNode<Model*>* currentModel = _modelList.GetFirst();

    OpenGLAPI::RenderClear();

    // Render Skybox first, if it is used
    {
        bool hasSkyBox = DefaultSkyBox != NULL;

        if (hasSkyBox)
        {
            OpenGLAPI::DepthMaskEnable(false);            
            OpenGLAPI::UseShaderProgram(DefaultSkyBox->Shader.ID);

            MainCamera.FetchGPUReferences(DefaultSkyBox->Shader.ID);
            MainCamera.Update(gameTickData);

            OpenGLAPI::SkyBoxSet(*DefaultSkyBox);
            OpenGLAPI::SkyBoxUse(*DefaultSkyBox);  
            
            OpenGLAPI::Render(RenderMode::Triangle, 0, 36);

            OpenGLAPI::DepthMaskEnable(true);
        }
    }

    while (currentModel != nullptr)
    {
        Model* model = currentModel->Element;
        ModelRenderInformation& renderInfo = model->RenderInformation;
        unsigned int shaderProgramID = renderInfo.ShaderProgramID;
        bool useDefaultShader = shaderProgramID == -1;
        bool changeShader = shaderProgramID != _lastUsedShaderProgram;

        currentModel = currentModel->Next;

        if (!model->ShouldBeRendered)
        {
            continue;
        }

        if (useDefaultShader)
        {
            shaderProgramID = _defaultShaderID;
            changeShader = shaderProgramID != _lastUsedShaderProgram;
        }

      

        OpenGLAPI::VertexArrayBind(renderInfo.VertexArrayID);

        //-----[Shader Lookup]--------------------------------------------------------------------
        if (changeShader)
        {
            OpenGLAPI::UseShaderProgram(shaderProgramID);

            _lastUsedShaderProgram = shaderProgramID;

            MainCamera.FetchGPUReferences(shaderProgramID);

            OpenGLAPI::ShaderSetUniformMatrix4x4(MainCamera.GetModelMatrixID(), model->ModelMatrix.Data);
        }

        //---[Change Shader Data?
        MainCamera.Update(gameTickData);
        //-----------------------------------------------------------------------------------------

        //model->PrintModelData();

        unsigned int currentIndex = 0;

        for (unsigned int i = 0; i < model->MeshList.Size(); i++)
        {
            Mesh& mesh = model->MeshList[i];
            Material* material = mesh.MeshMaterial;
            bool hasMaterial = material != nullptr;
            unsigned int textureID = _defaultTextureID;
            unsigned int amountToRender;

            if (hasMaterial)
            {
                Image* texture = material->Texture;
                bool hasTexture = texture != nullptr;

                if (hasTexture)
                {
                    textureID = texture->ID;
                }
            }       

            // TextureLookup ----------------------------     
            OpenGLAPI::TextureUse(textureID);
            //-------------------------------------------------

                 //---RenderStyle-------------------------
            if (renderInfo.RenderType != RenderMode::Unkown)
            {
                amountToRender = mesh.IndexList.Size();

                OpenGLAPI::Render(renderInfo.RenderType, currentIndex, amountToRender);

                currentIndex += amountToRender;
            }
            //------------------------------------------------------------------------------
        }
    }
}

void BF::ResourceManager::PrintContent(bool detailed)
{
    unsigned int modelListSize = _modelList.Size();
    unsigned int imageListSize = _imageList.Size();
    unsigned int soundListSize = _soundList.Size();
    unsigned int shaderListSize = _shaderProgramList.Size();
    unsigned int fontListSize = _fontList.Size();
    unsigned int dialogListSize = _dialogList.Size();

    if (detailed)
    {
        const char* empty = "|                                                                                                  |\n";

        const char* message =
            "+--------------------------------------------------------------------------------------------------+\n"
            "|   Loaded Resources                                                                               |\n"
            "+---<Models <%u>>-----------------------------------------------------------------------------------+\n";


        printf(message, modelListSize);
        printf(empty);


        LinkedListNode<Model*>* currentModel = _modelList.GetFirst();

        while (currentModel != nullptr)
        {
            Model* model = currentModel->Element;

            printf("| ID:%u %s\n", model->ID, &model->FilePath[0]);

            currentModel = currentModel->Next;
        }


        printf(empty);
        printf("+---<Image <%u>>------------------------------------------------------------------------------------+\n", imageListSize);
        printf(empty);


        LinkedListNode<Image*>* currentImage = _imageList.GetFirst();

        while (currentImage != nullptr)
        {
            Image* image = currentImage->Element;

            printf("| ID:%u Fomat:%s %s\n", image->ID, ImageFormatToString(image->Format),image->FilePath);

            currentImage = currentImage->Next;
        }


        printf(empty);
        printf("+---<Sound <%u>>------------------------------------------------------------------------------------+\n", soundListSize);
        printf(empty);

        for (size_t i = 0; i < soundListSize; i++)
        {

        }

        printf(empty);
        printf("+---<Font <%u>>-------------------------------------------------------------------------------------+\n", fontListSize);
        printf(empty);


        LinkedListNode<Font*>* currentFont = _fontList.GetFirst();

        while (currentFont != nullptr)
        {
            Font* font = currentFont->Element;

            printf("| ID:%u Font Source: %s\n", font->ID, &font->FilePath[0]);

            currentFont = currentFont->Next;
        }


        printf(empty);
        printf("+---<Shader <%u>>-----------------------------------------------------------------------------------+\n", shaderListSize);
        printf(empty);


        LinkedListNode<ShaderProgram*>* currentChaderProgram = _shaderProgramList.GetFirst();

        while (currentChaderProgram != nullptr)
        {
            ShaderProgram* shaderProgram = currentChaderProgram->Element;

            printf("| ID:%u ShaderProgram\n", shaderProgram->ID);

            for (size_t i = 0; i < 2; i++)
            {
                Shader& shader = shaderProgram->ShaderList[i];                

                printf("| - Sub-Shader ID:%u Type:%u Source:%s\n", shader.ID, shader.Type, &shader.FilePath[0]);
            }

            currentChaderProgram = currentChaderProgram->Next;
        }


        printf(empty);
        printf("+---<Dialog <%u>>-----------------------------------------------------------------------------------+\n", dialogListSize);
        printf(empty);

        for (size_t i = 0; i < dialogListSize; i++)
        {

        }

        printf(empty);
        printf("+--------------------------------------------------------------------------------------------------+\n");
    }
    else
    {
        const char* message =
            "+--------------------------------------------------+\n"
            "| Loaded Resources\n"
            "| - Models <%u>\n"
            "| - Image  <%u>\n"
            "| - Sound  <%u>\n"
            "| - Font   <%u>\n"
            "| - Shader <%u>\n"
            "| - Dialog <%u>\n"
            "+--------------------------------------------------+\n";

        printf
        (
            message,
            modelListSize,
            imageListSize,
            soundListSize,
            shaderListSize,
            fontListSize,
            dialogListSize
        );
    }
}