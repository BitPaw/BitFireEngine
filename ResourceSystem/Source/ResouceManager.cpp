#include "ResouceManager.h"
#include "Font/FNT/FNTPage.h"
#include "File/File.h"
#include "../../RenderSystem/Source/OpenGLAPI.h"


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

        RGBA<float> defaultColor(1, 1, 1, 1);
        Point<float> defaultTexturepoint;
        Position<float> normalPosition;

        Vertex* vertex = nullptr;
        RGBA<float>* color = nullptr;
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

        vertexData[dataIndex++] = color->Red;
        vertexData[dataIndex++] = color->Green;
        vertexData[dataIndex++] = color->Blue;
        vertexData[dataIndex++] = color->Alpha;

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

void* BF::ResourceManager::Load(const char* string)
{
    AsciiString asciiString(string);

    return Load(asciiString);
}

void* BF::ResourceManager::Load(AsciiString& filePath)
{
    void* loadedResource = nullptr;
    ResourceType resourceType = ResourceType::Unknown;
    File file(filePath);
    AsciiString fileExtension(&file.Extension[0]);
    bool doesFileExist = file.DoesFileExist();
    ErrorCode errorCode = doesFileExist ? ErrorCode::Undefined : ErrorCode::FileNotFound;

    if (doesFileExist)
    {
        {
            bool isModel = Model::CheckFileExtension(fileExtension) != ModelType::UnKown;
            bool isImage = Image::CheckFileExtension(fileExtension) != ImageFileExtension::Unkown;
            bool isSound = false;
            bool isFont = Font::IsFontFile(fileExtension);
            bool isShader = false;
            bool isDialog = false;
            bool isLevel = file.Extension.CompareIgnoreCase("lev");

            if (isModel) resourceType = ResourceType::Model;
            if (isImage) resourceType = ResourceType::Image;
            if (isSound) resourceType = ResourceType::Sound;
            if (isFont) resourceType = ResourceType::Font;
            if (isShader) resourceType = ResourceType::Shader;
            if (isDialog) resourceType = ResourceType::Dialog;
            if (isLevel) resourceType = ResourceType::Level;
        }

        switch (resourceType)
        {
            case ResourceType::Dialog:
                break;

            case ResourceType::Font:
            {
                Font* font = new Font();
                FontFormat fontFormat = Font::ParseFontFormat(fileExtension);

                errorCode = font->Load(filePath);

                if (errorCode == ErrorCode::NoError)
                {
                    for (size_t i = 0; i < font->AdditionalResourceList.Size(); i++)
                    {
                        AsciiString& string = font->AdditionalResourceList[i];

                        AsciiString fullPath;

                        filePath.Cut(0, filePath.FindLast('/'), fullPath);

                        fullPath.AttachToBack('/');
                        fullPath.AttachToBack(string);

                        font->Texture = (Image*)Load(fullPath);
                    }

                    font->ID = _fontList.Size();
                    font->FilePathSet(&filePath[0]);

                    _fontList.Add(font);

                    loadedResource = font;
                    DefaultFont = font;
                }




                /*
                if (fontFormat == FontFormat::FNT)
                {
                    FNT* fnt = (FNT*)font;
                    unsigned int amountOfTextures = fnt->FontPages.Size();

                    for (unsigned int i = 0; i < amountOfTextures; i++)
                    {
                        FNTPage& fontPage = fnt->FontPages[i];
                        AsciiString& fileName = fontPage.PageFileName;
                        AsciiString path;
                        unsigned int lastDot = filePath.FindLast('/') + 1;

                        filePath.Cut(0, lastDot, path);

                        path.AttachToBack(fileName);

                        Load(path);
                    }
                }*/

                break;
            }

            case ResourceType::Image:
            {
                Image* image = new Image();
                errorCode = image->Load(filePath);

                if (errorCode == ErrorCode::NoError)
                {
                    bool firstImage = _imageList.Size() == 0;

                    Add(*image);

                    if (firstImage)
                    {
                        _defaultTextureID = image->ID;
                    }

                    loadedResource = image;
                }

                break;
            }

            case ResourceType::Level:
            {
                Level* level = new Level();
                List<AsciiString> fileLines;
                File file(filePath);

                errorCode = ErrorCode::LoadingFailed;

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
                level->ModelList.ReSize(modelCounter);
                level->ImageList.ReSize(imageCounter);
                level->SoundList.ReSize(soundCounter);
                level->FontList.ReSize(fontCounter);
                level->ShaderList.ReSize(shaderCounter);
                level->DialogList.ReSize(dialogCounter);

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
                    char dummyBuffer[10];
                    char path[30];

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
                            Model* loadedModel = reinterpret_cast<Model*>(Load(path));

                            if (loadedModel == nullptr)
                            {
                                printf("[Warning] Loading failed!\n");
                                break;
                            }

                            level->ModelList[modelCounter++] = &loadedModel;
                            //-------------------

                            //--[Apply Data]-------------
                            loadedModel->MoveTo(position);
                            loadedModel->Rotate(rotation);
                            loadedModel->Scale(scale);
                            loadedModel->UpdateGlobalMesh();
                            PushToGPU(*loadedModel);
                            //-----------------------
                            break;
                        }
                        case _textureToken:
                        {
                            sscanf(currentLine, "%s %s", dummyBuffer, path);

                            Image* image = reinterpret_cast<Image*>(Load(path));
                            level->ImageList[imageCounter++] = &image;
                            break;
                        }
                        case _musicToken:
                        {
                            sscanf(currentLine, "%s %s", dummyBuffer, path);

                            Sound* sound = reinterpret_cast<Sound*>(Load(path));
                            level->SoundList[soundCounter++] = &sound;
                            break;
                        }
                        case _fontToken:
                        {
                            sscanf(currentLine, "%s %s", dummyBuffer, path);

                            Font* font = reinterpret_cast<Font*>(Load(path));
                            level->FontList[fontCounter++] = &font;
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


                _levelList.Add(level);

                loadedResource = level;

                errorCode = ErrorCode::NoError;

                break;
            }

            case ResourceType::Model:
            {
                Model* model = new Model();

                errorCode = model->Load(filePath);

                if (errorCode == ErrorCode::NoError)
                {
                    for (unsigned int i = 0; i < model->MaterialList.Size(); i++)
                    {
                        Material& material = model->MaterialList[i];
                        AsciiString imageFilePath(material.TextureFilePath);
                        Image* image = reinterpret_cast<Image*>(Load(imageFilePath));

                        if (image != nullptr)
                        {
                            material.Texture = image;

                            Add(*image);
                        }
                    }

                    Add(*model);

                    loadedResource = model;
                }
                break;
            }
            case ResourceType::Shader:
            {
                break;
            }
            case ResourceType::Sound:
            {
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

    return loadedResource;
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
    if (!image.LoadedToGPU)
    {
        _imageList.Add(&image);

        image.LoadedToGPU = true;
    }

    PushToGPU(image);
}

unsigned int BF::ResourceManager::AddShaderProgram(AsciiString& vertexShader, AsciiString& fragmentShader)
{
    return AddShaderProgram(&vertexShader[0], &fragmentShader[0]);
}

unsigned int BF::ResourceManager::AddShaderProgram(const char* vertexShader, const char* fragmentShader)
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    bool firstShaderProgram = _shaderProgramList.Size() == 0;

    shaderProgram->AddShader((char*)vertexShader, (char*)fragmentShader);
    shaderProgram->Load();

    _shaderProgramList.Add(shaderProgram);

    OpenGLAPI::ShaderCompile(*shaderProgram);

    if (firstShaderProgram)
    {
        _defaultShaderID = shaderProgram->ID;
        MainCamera.FetchGPUReferences(_defaultShaderID);
    }

    return shaderProgram->ID;
}

void BF::ResourceManager::RenderModels(GameTickData& gameTickData)
{
    LinkedListNode<Model*>* currentModel = _modelList.GetFirst();

    OpenGLAPI::RenderClear();

    while (currentModel != nullptr)
    {
        Model* model = currentModel->Element;
        ModelRenderInformation& renderInfo = model->RenderInformation;
        unsigned int shaderProgramID = renderInfo.ShaderProgramID;
        bool useDefaultShader = shaderProgramID == -1;
        bool changeShader = shaderProgramID != _lastUsedShaderProgram;

        if (useDefaultShader)
        {
            shaderProgramID = _defaultShaderID;
            changeShader = shaderProgramID != _lastUsedShaderProgram;
        }

        currentModel = currentModel->Next;

        OpenGLAPI::VertexArrayBind(renderInfo.VertexArrayID);

        //-----[Shader Lookup]--------------------------------------------------------------------
        if (changeShader)
        {
            OpenGLAPI::UseShaderProgram(shaderProgramID);

            _lastUsedShaderProgram = shaderProgramID;

            MainCamera.FetchGPUReferences(shaderProgramID);
        }

        //---[Change Shader Data?
        MainCamera.Update(gameTickData);
        //-----------------------------------------------------------------------------------------

        //model->PrintModelData();

        unsigned int currentIndex = 0;

        for (size_t i = 0; i < model->MeshList.Size(); i++)
        {
            Mesh& mesh = model->MeshList[i];
            Material* material = mesh.MeshMaterial;
            bool hasMaterial = material != nullptr;
            unsigned int textureID = _defaultTextureID;
            unsigned int amountToRender;

            if (hasMaterial && material != (void*)0xCDCDCDCD)
            {
                Image* texture = material->Texture;
                bool hasTexture = texture != nullptr;

                if (hasTexture)
                {
                    textureID = texture->ID;
                }
            }

            // TextureLookup ----------------------------         
            OpenGLAPI::TextureBind(textureID);
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

            printf("| ID:%u %s\n", image->ID, &image->FilePath[0]);

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