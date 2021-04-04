#include "ResouceManager.h"
#include "Font/FNT/FNTPage.h"
#include "File/File.h"

int BF::ResourceManager::ImageWrapToOpenGLFormat(ImageWrap imageWrap)
{
    switch (imageWrap)
    {
    case ImageWrap::NoModification:
        return GL_CLAMP_TO_BORDER;

    case ImageWrap::StrechEdges:
        return GL_CLAMP_TO_EDGE;

    case ImageWrap::StrechEdgesAndMirror:
        return GL_MIRROR_CLAMP_TO_EDGE;

    case ImageWrap::Repeat:
        return GL_REPEAT;

    case ImageWrap::RepeatAndMirror:
        return GL_MIRRORED_REPEAT;
    }
}

int BF::ResourceManager::ImageLayoutToOpenGLFormat(ImageLayout layout)
{
    switch (layout)
    {
    case ImageLayout::Nearest:
        return GL_NEAREST;

    case ImageLayout::Linear:
        return GL_LINEAR;

    case ImageLayout::MipMapNearestNearest:
        return GL_NEAREST_MIPMAP_NEAREST;

    case ImageLayout::MipMapLinearNearest:
        return GL_LINEAR_MIPMAP_NEAREST;

    case ImageLayout::MipMapNNearestLinear:
        return GL_NEAREST_MIPMAP_LINEAR;

    case ImageLayout::MipMapLinearLinear:
        return GL_LINEAR_MIPMAP_LINEAR;
    }
}

void BF::ResourceManager::UpdateVBOData(Model& model)
{
    LinkedMesh& mesh = model.GlobalMesh;
    List<float>& vertexData = model.RenderInformation.VertexData;
    List<unsigned int>& indexData = model.RenderInformation.IndexData;

    unsigned int dataIndex = 0;// renderInformation->VertexDataPosition;
    //unsigned int indiceIndex = renderInformation->IndiceIndex;

   // printf("Update: <%p> <%.2u> %s\n", renderInformation, renderInformation->RenderID, &(renderInformation->RenderModel->ModelName[0]));

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

unsigned int BF::ResourceManager::CompileShader(unsigned int type, AsciiString& shaderString)
{
    unsigned int id = glCreateShader(type);
    const char* src = &shaderString[0];   

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    {
        int result;

        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int lengh;

            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengh);
            char* message = new char[lengh];

            glGetShaderInfoLog(id, lengh, &lengh, message);

            printf("Failed to compile Shader ID:%u!\nReason: %s", id, message);

            delete[] message;

            glDeleteShader(id);

            return -1;
        }
    }

    return id;
}

BF::ResourceManager::ResourceManager()
{
    _defaultShaderID = 0;
    _defaultTextureID = 0;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&_maximalAmountOfTexturesInOneCall);;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, (GLint*)&_maximalAmountOfTexturesLoaded);
}

void BF::ResourceManager::PushToGPU(Model& model)
{
    unsigned int& modelID = model.ID;
    bool isAlreadyLinked = modelID != -1;
    ModelRenderInformation& renderInfo = model.RenderInformation;

    if (isAlreadyLinked)
    {
        UpdateVBOData(model);

        GLsizeiptr vArraySize = renderInfo.VertexData.SizeInBytes();

        glBindVertexArray(renderInfo.VertexArrayID);
        glBindBuffer(GL_ARRAY_BUFFER, renderInfo.VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vArraySize, &renderInfo.VertexData[0]);
    }
    else
    {       
        modelID = _modelList.Size();        

        renderInfo.VertexData.ReSize(model.GlobalMesh.IndexList.Size() * (3 + 3 + 4 + 2));
        renderInfo.IndexData.ReSize(model.GlobalMesh.IndexList.Size());

        UpdateVBOData(model);

        // Allocate GPU Buffer
        const unsigned int vertexSize = 3;
        const unsigned int normalSize = 3;
        const unsigned int colorSize = 4;
        const unsigned int textureSize = 2;
        unsigned int blockSize = sizeof(float) * (3 + 3 + 4 + 2);
        unsigned int vertexDataSize = renderInfo.VertexData.SizeInBytes();
        unsigned int indexDataSize = renderInfo.IndexData.SizeInBytes();

        glGenVertexArrays(1, &renderInfo.VertexArrayID);
        glBindVertexArray(renderInfo.VertexArrayID);

        unsigned int sizzze = sizeof(float) * renderInfo.VertexData.Size();

        glGenBuffers(1, &renderInfo.VertexBufferID); // Get BufferID
        glBindBuffer(GL_ARRAY_BUFFER, renderInfo.VertexBufferID); // Select Buffer
        glBufferData(GL_ARRAY_BUFFER, sizzze, &renderInfo.VertexData[0], GL_DYNAMIC_DRAW);

        const unsigned int sizeOfFloat = sizeof(float);
        const unsigned int type = GL_FLOAT;

        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, vertexSize, type, GL_FALSE, blockSize, 0);

        // Normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, normalSize, type, GL_FALSE, blockSize, (void*)(sizeOfFloat * (vertexSize)));

        // Color
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, colorSize, type, GL_FALSE, blockSize, (void*)(sizeOfFloat * (vertexSize + normalSize)));

        // TextureCoordinate
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, textureSize, type, GL_FALSE, blockSize, (void*)(sizeOfFloat * (vertexSize + normalSize + colorSize)));

        glGenBuffers(1, &renderInfo.IndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderInfo.IndexBufferID); // Select
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderInfo.IndexData.SizeInBytes(), &renderInfo.IndexData[0], GL_STATIC_DRAW);
    }
}

void BF::ResourceManager::PushToGPU(Image& image)
{
    unsigned int& imageID = image.ID;
    unsigned int format;

    switch (image.Format)
    {
        case BF::ImageFormat::RGB:
            format = GL_RGB;
            break;

        case BF::ImageFormat::RGBA:
            format = GL_RGBA;
            break;

        case BF::ImageFormat::BlackAndWhite:
        default:
            throw "Invalid ImageFormat";
    }

    glGenTextures(1, &imageID);

    glBindTexture(GL_TEXTURE_2D, imageID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ImageWrapToOpenGLFormat(image.WrapWidth));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ImageWrapToOpenGLFormat(image.WrapHeight));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ImageLayoutToOpenGLFormat(image.LayoutNear));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ImageLayoutToOpenGLFormat(image.LayoutFar));

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, &image.PixelData[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void BF::ResourceManager::PushToGPU(ShaderProgram& shaderProgram)
{
    unsigned int type;

    shaderProgram.ID = glCreateProgram();

    for (unsigned int i = 0; i < shaderProgram.ShaderList.Size(); i++)
    {
        Shader& shader = shaderProgram.ShaderList[i];

        switch (shader.Type)
        {
        case ShaderType::Vertex:
            type = GL_VERTEX_SHADER;
            break;

        case   ShaderType::TessellationControl:
            type = -1; // ???
            break;

        case   ShaderType::TessellationEvaluation:
            type = -1; // ???
            break;

        case   ShaderType::Geometry:
            type = GL_GEOMETRY_SHADER;
            break;

        case   ShaderType::Fragment:
            type = GL_FRAGMENT_SHADER;
            break;

        case  ShaderType::Compute:
            type = GL_COMPUTE_SHADER;
            break;

        case ShaderType::Unkown:
        default:
            type = -1;       
            break;
        }

        shader.ID = CompileShader(type, shader.Content);

        if (shader.ID != -1)
        {
            glAttachShader(shaderProgram.ID, shader.ID);
        }
    }

    glLinkProgram(shaderProgram.ID);
    glValidateProgram(shaderProgram.ID);

    // We used the Shaders above to compile, these elements are not used anymore.
    for (unsigned int i = 0; i < shaderProgram.ShaderList.Size(); i++)
    {
        Shader* shader = &shaderProgram.ShaderList[i];

        if (shader->ID != -1)
        {
            glDeleteShader(shader->ID);
        }
    }
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
    AsciiString& fileExtension = file.Extension;
    bool doesFileExist = file.DoesFileExist();
    ErrorCode errorCode = doesFileExist ? ErrorCode::Undefined : ErrorCode::FileNotFound;

    if (doesFileExist)
    {
        {
            bool isModel = ModelLoader::IsModelFile(fileExtension);
            bool isImage = ImageLoader::IsImageFileExtension(fileExtension);
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

                if(errorCode == ErrorCode::NoError)
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
                    font->FilePath.Copy(filePath);

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
                errorCode = ImageLoader::LoadFromFile(filePath, *image);

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
                        char character = line.GetFirstNonEmpty();
                        List<AsciiString> lines;

                        line.Splitt(' ', lines);

                        switch (character)
                        {
                        case _modelToken:
                        {
                            AsciiString path;
                            AsciiString positionText;
                            AsciiString rotationText;
                            AsciiString scaleText;
                            Position<float> position;
                            Position<float> rotation;
                            Position<float> scale;

                            // Get raw Data-------------------------
                            path.Copy(lines[1]);
                            positionText.Copy(lines[2]);
                            rotationText.Copy(lines[3]);
                            scaleText.Copy(lines[4]);

                            positionText.Splitt('|', lines);

                            position.Set
                            (
                                lines[0].ToFloat(),
                                lines[1].ToFloat(),
                                lines[2].ToFloat()
                            );

                            rotationText.Splitt('|', lines);

                            rotation.Set
                            (
                                lines[0].ToFloat(),
                                lines[1].ToFloat(),
                                lines[2].ToFloat()
                            );

                            scaleText.Splitt('|', lines);

                            scale.Set
                            (
                                lines[0].ToFloat(),
                                lines[1].ToFloat(),
                                lines[2].ToFloat()
                            );
                            //------------------------------------------------

                            // Load Model----------------
                            Model* loadedModel = reinterpret_cast<Model*>(Load(path));

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
                            Image* image = reinterpret_cast<Image*>(Load(lines[1]));
                            level->ImageList[imageCounter++] = &image;
                            break;
                        }
                        case _musicToken:
                        {
                            Sound* sound = reinterpret_cast<Sound*>(Load(lines[1]));
                            level->SoundList[soundCounter++] = &sound;
                            break;
                        }
                        case _fontToken:
                        {
                            Font* font = reinterpret_cast<Font*>(Load(lines[1]));
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
                
                errorCode = ModelLoader::LoadFromFile(filePath, *model);

                if (errorCode == ErrorCode::NoError)
                {
                    for (unsigned int i = 0; i < model->MaterialList.Size(); i++)
                    {
                        Material& material = model->MaterialList[i];
                        AsciiString& imageFilePath = material.TextureFilePath;
                        Image* image = (Image*)(Load(imageFilePath));

                        material.Texture = image;

                        Add(*image);
                    }

                    Add(*model);

                    loadedResource = model;
                }    
                break;
            }      

            case ResourceType::Shader:
                break;

            case ResourceType::Sound:
                break;
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

unsigned int BF::ResourceManager::AddShaderProgram(const char* vertexShader, const char* fragmentShader)
{
    AsciiString vertexShaderString(vertexShader);
    AsciiString fragmentShaderString(fragmentShader);

    return AddShaderProgram(vertexShaderString, fragmentShaderString);
}

unsigned int BF::ResourceManager::AddShaderProgram(AsciiString& vertexShader, AsciiString& fragmentShader)
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    bool firstShaderProgram = _shaderProgramList.Size() == 0;

    shaderProgram->AddShader(vertexShader, fragmentShader);

    _shaderProgramList.Add(shaderProgram);

    PushToGPU(*shaderProgram);

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

        glBindVertexArray(renderInfo.VertexArrayID);

        //-----[Shader Lookup]--------------------------------------------------------------------
        if (changeShader)
        {
            glUseProgram(shaderProgramID);         

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
            glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
            glBindTexture(GL_TEXTURE_2D, textureID);
            //-------------------------------------------------

                 //---RenderStyle-------------------------
            if (renderInfo.RenderType != RenderMode::Unkown)
            {
                unsigned int renderMode = -1;

                switch (renderInfo.RenderType)
                {
                    case RenderMode::Point:
                        renderMode = GL_POINTS;
                        break;

                    case RenderMode::Line:
                        renderMode = GL_LINE_LOOP;
                        break;

                    case RenderMode::Triangle:
                        renderMode = GL_TRIANGLES;
                        break;

                    case RenderMode::Square:
                        renderMode = GL_QUADS;
                        break;
                }

                amountToRender = mesh.IndexList.Size();

                glDrawArrays(renderMode, currentIndex, amountToRender);

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

            for (size_t i = 0; i < shaderProgram->ShaderList.Size(); i++)
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