#include "OBJLoader.h"

BF::OBJ* BF::OBJLoader::LoadFromFile(ASCIIString filePath)
{
    StopWatch stopWatch;
    OBJ* waveFront = new OBJ();
    bool isFirstVertex = true;   

    stopWatch.Start();

    TextFile textFile(filePath);
    FileLoader::ReadTextFile(textFile, true);
    unsigned int numberOfLines = textFile.Lines.Size();
    List<OBJLineCommand> commandList(numberOfLines);

    //waveFront->Name.Copy(textFile.FileName);

    printf("  Loading File  : %lf\n", stopWatch.Reset());   

   // Translate to enum commands
   {
       bool usedFacesBefore = false;
       bool newMeshKey = false;
       bool checkedRenderType = false;
       unsigned int elementListSize = 1; // We will have at least one mesh.
    
       for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
       {
           OBJLineCommand* currentCommand = &commandList[lineIndex];
           ASCIIString* line = &textFile.Lines[lineIndex];
           unsigned int functionChar = (line->Size() <= 0 ? _characterNone : (*line)[0]);

           switch (functionChar)
           {
               case 'm':
                   *currentCommand = OBJLineCommand::MaterialLibraryInclude;
                   break;

               case 'u':
                   *currentCommand = OBJLineCommand::MaterialLibraryUse;

                   if (usedFacesBefore)
                   {
                       newMeshKey = true;
                       usedFacesBefore = false;
                   }

                   break;

               case _characterComment:
                   *currentCommand = OBJLineCommand::Comment;
                   break;

               case _characterObjectName:
                   *currentCommand = OBJLineCommand::ObjectName;
                   newMeshKey = true;
                   break;

               case _characterSmoothShading:
                   *currentCommand = OBJLineCommand::SmoothShading;
                   break;

               case _characterFace:
                   *currentCommand = OBJLineCommand::FaceElement;
                   usedFacesBefore = true;

                   if (!checkedRenderType)
                   {
                       waveFront->VertexStructureSize = line->Count('/') / 2;

                       checkedRenderType = true;
                   }

                   break;

               case _characterVertex:
               {
                   functionChar = (*line)[1];

                   switch (functionChar)
                   {
                       case _characterNone:
                           *currentCommand = OBJLineCommand::VertexGeometric;
                           break;

                       case _characterVertexTexture:
                           *currentCommand = OBJLineCommand::VertexTexture;
                           break;

                       case _characterVertexNormal:
                           *currentCommand = OBJLineCommand::VertexNormal;
                           break;

                       case _characterParameter:
                           *currentCommand = OBJLineCommand::VertexParameter;
                           break;

                       default:
                           *currentCommand = OBJLineCommand::Invalid;
                           break;
                   }

                   break;
               }

               case _characterNone:
                   *currentCommand = OBJLineCommand::None;
                   break;

               default:
                   *currentCommand = OBJLineCommand::Invalid;
                   break;
           }

           if (newMeshKey)
           {
               newMeshKey = false;
               elementListSize++;
           }
       }

       waveFront->ElementList.ReSize(elementListSize-1);
   }       

   printf("  Command lookup: %lf\n", stopWatch.Reset());

    // Space lookup
    {
       bool usedFacesBefore = false;
       bool newMeshKey = false;

        unsigned int elementIndex = 0;
        unsigned int materialsCounter = 0;

        unsigned int vertexPositionListSize = 0;
        unsigned int textureCoordinateListSize = 0;
        unsigned int vertexNormalPositionListSize = 0;
        unsigned int vertexParameterListSize = 0;
        unsigned int faceElementListSize = 0;

        OBJElement* elemtent = &waveFront->ElementList[elementIndex++];

        // How many data do i need?
        for (unsigned int i = 0; i < numberOfLines; i++)
        {
            switch (commandList[i])
            {
                case OBJLineCommand::Invalid:
                    break;

                case OBJLineCommand::None:
                    break;

                case OBJLineCommand::Comment:
                    break;

                case OBJLineCommand::MaterialLibraryInclude:
                    materialsCounter++;
                    break;

                case OBJLineCommand::MaterialLibraryUse:
                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }
                  
                    break;

                case OBJLineCommand::ObjectName:
                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }

                    break;

                case OBJLineCommand::VertexGeometric:
                    vertexPositionListSize++;
                    break;

                case OBJLineCommand::VertexTexture:
                    textureCoordinateListSize++;
                    break;

                case OBJLineCommand::VertexNormal:
                    vertexNormalPositionListSize++;
                    break;

                case OBJLineCommand::VertexParameter:
                    vertexParameterListSize++;
                    break;

                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                    faceElementListSize++;

                    usedFacesBefore = true;
                    break;
            }

            if (newMeshKey && (elementIndex <= waveFront->ElementList.Size()))
            {
                newMeshKey = false;

                faceElementListSize *= 3;

                elemtent->VertexPositionList.ReSize(vertexPositionListSize);
                elemtent->TextureCoordinateList.ReSize(textureCoordinateListSize);
                elemtent->VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
                elemtent->VertexParameterList.ReSize(vertexParameterListSize);
                elemtent->FaceElementList.ReSize(faceElementListSize);

                elemtent = &waveFront->ElementList[elementIndex++];

                vertexPositionListSize = 0;
                textureCoordinateListSize = 0;
                vertexNormalPositionListSize = 0;
                vertexParameterListSize = 0;
                faceElementListSize = 0;
            }
        }

        // Register Memory
        {

            faceElementListSize *= waveFront->VertexStructureSize;                   

            elemtent->VertexPositionList.ReSize(vertexPositionListSize);
            elemtent->TextureCoordinateList.ReSize(textureCoordinateListSize);
            elemtent->VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
            elemtent->VertexParameterList.ReSize(vertexParameterListSize);
            elemtent->FaceElementList.ReSize(faceElementListSize);

            waveFront->Materials.ReSize(materialsCounter);
        }    
    }

    printf("  Raw Parse     : %lf\n", stopWatch.Reset());

    // Exact Parse
    {
        bool usedFacesBefore = false;
        bool newMeshKey = false;

        unsigned int elementIndex = 0;
        unsigned int currentPositionElement = 0;
        unsigned int currentTextureElement = 0;
        unsigned int currentNormalElement = 0;
        unsigned int currentParameterElement = 0;
        unsigned int currentFaceElement = 0;
        unsigned int materialIndex = 0;
        OBJElement* elemtent = &waveFront->ElementList[elementIndex++];
        //List<Position<unsigned int>> indexPositionCache(waveFront->VertexStructureSize); // 36 Byte alloc
        unsigned int faceStructureSize = waveFront->VertexStructureSize;


        printf("Struc´tursize <%u>\n", faceStructureSize);
        List<ASCIIString> faceTextCache(faceStructureSize);
        List<ASCIIString> dupTextCache(2);
        List<ASCIIString> trippelTextCache(3); // X, Y [28 Byte alloc]
        List<ASCIIString> quadTextCache(4); // v X, Y, Z [36 Byte alloc]
        Position<float>* currentVectorValue;       

        // Parse
        for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
        {
            ASCIIString* line = &textFile.Lines[lineIndex];
            OBJLineCommand command = commandList[lineIndex];

            switch (command)
            {
                case OBJLineCommand::Invalid:
                    break;

                case OBJLineCommand::None:
                    break;

                case OBJLineCommand::Comment:
                    break;

                case OBJLineCommand::MaterialLibraryInclude:
                {
                    try
                    {                 
                        line->Splitt(' ', trippelTextCache);

                        ASCIIString& mtlfilePath = trippelTextCache[1]; //[20 Byte]

                        // Merge File Path
                        
                        int position = filePath.FindFirst('/');
                        bool hasSlash = position != -1;

                        if (hasSlash)
                        {
                            //ASCIIString rootFolder;

                            //filePath.Cut(position, rootFolder);

                            // mtlfilePath.Copy(rootFolder + "/" + mtlfilePath);
                        }                        

                        bool doesFileExist = FileLoader::DoesFileExist(mtlfilePath);

                        if (doesFileExist)
                        {
                            MTL* materialFile = MTLLoader::LoadFromFile(mtlfilePath);

                            waveFront->Materials[materialIndex++] = *materialFile;
                        }                      

                        //delete materialFile;
                    }
                    catch (FileNotFound fileNotFound)
                    {
                        printf("[!] Could not load File @ %s\n", fileNotFound.FilePath);
                        //Log::Write(LogMessageType::Warning, "Could not load File");
                    }    
                }
                break;

                case OBJLineCommand::MaterialLibraryUse:
                {
                   
                    line->Splitt(' ', dupTextCache);
                    ASCIIString& materialName = line[1];
                    unsigned int materialID = -1;

                    for (unsigned int i = 0; i < waveFront->Materials.Size(); i++)
                    {
                        MTL* mtl = &waveFront->Materials[i];

                        for (unsigned int j = 0; j < mtl->MaterialList.Size(); j++)
                        {
                            Material* material = &mtl->MaterialList[j];

                            if (material->Name.Compare(materialName))
                            {
                                materialID = j;
                                j = -1;
                                i = -1;

                                //printf("%s == %s >> %i\n", material->Name.c_str(), materialName.c_str(), materialID);
                                //break;
                            }
                        }
                    }

                    elemtent->MaterialID = materialID;

                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }

                    break;
                }
             

                case OBJLineCommand::ObjectName:
                     line->Cut(2, elemtent->Name);

                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }
                    break;
                    
            
                case OBJLineCommand::VertexParameter:
                case OBJLineCommand::VertexNormal:                 
                case OBJLineCommand::VertexGeometric:
                {
                    switch (command)
                    {
                    case OBJLineCommand::VertexParameter:
                        currentVectorValue = &elemtent->VertexParameterList[currentParameterElement++];
                        break;

                    case OBJLineCommand::VertexNormal:
                        currentVectorValue = &elemtent->VertexNormalPositionList[currentNormalElement++];
                        break;

                    case OBJLineCommand::VertexGeometric:
                        currentVectorValue = &elemtent->VertexPositionList[currentPositionElement++];
                        break;

                    default:
                        throw "Error";
                    }

                    line->Splitt(' ', quadTextCache);

                    currentVectorValue->Set
                    (
                        quadTextCache[1].ToFloat(), // X
                        quadTextCache[2].ToFloat(), // Y
                        quadTextCache[3].ToFloat() // Z
                    );
                }
                    break;

                case OBJLineCommand::VertexTexture:
                {
                    Point<float>& point = elemtent->TextureCoordinateList[currentTextureElement++];
               
                    line->Splitt(' ', trippelTextCache);

                    point.Set
                    (
                        trippelTextCache[1].ToFloat(),
                        trippelTextCache[2].ToFloat()
                    );
                }                     
                    break;
      

                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:                    
                    line->Splitt(' ', faceTextCache);

                    for (unsigned int i = 1; i <= faceStructureSize; i++)
                    {
                        faceTextCache[i].Splitt('/', trippelTextCache);
                        // Possiple error if char is '/'

                        elemtent->FaceElementList[currentFaceElement++].Set
                        (
                            trippelTextCache[0].ToInt(),
                            trippelTextCache[1].ToInt(),
                            trippelTextCache[2].ToInt()
                        );
                    }

                    usedFacesBefore = true;

                    break;
            }

            if (newMeshKey) // && elementIndex < waveFront->ElementList.Size.Value
            {
                newMeshKey = false;

                elemtent = &waveFront->ElementList[elementIndex++];

                currentPositionElement = 0;
                currentTextureElement = 0;
                currentNormalElement = 0;
                currentParameterElement = 0;
                currentFaceElement = 0;
            }
        }
    }

    printf("  Exact Parse   : %lf\n", stopWatch.Reset());

    return waveFront;
}

void BF::OBJLoader::SaveToFile(ASCIIString filePath, BF::OBJ& waveFont)
{

}

void BF::OBJLoader::PrintObjectDataToConsole(BF::OBJ& waveFont)
{
    printf(" +-------+-------+-------+-------+-------+-------\n");
    printf(" | Object: %s\n", &waveFont.Name[0]);
    printf(" +-------+-------+-------+-------+-------+-------\n");
    printf(" | %5s | %5s | %5s | %5s | %5s | %s\n", "Vert", "Norm", "Text", "Para", "Face", "Name");
    printf(" +-------+-------+-------+-------+-------+-------\n");

    for (unsigned int i = 0; i < waveFont.ElementList.Size(); i++)
    {
        OBJElement* waveFrontElement = &waveFont.ElementList[i];

        unsigned int sizePos = waveFrontElement->VertexPositionList.Size();
        unsigned int sizeNormal = waveFrontElement->VertexNormalPositionList.Size();
        unsigned int sizeText = waveFrontElement->TextureCoordinateList.Size();
        unsigned int sizePara = waveFrontElement->VertexParameterList.Size();
        unsigned int sizeFace = waveFrontElement->FaceElementList.Size();

        printf(" | %5u | %5u | %5u | %5u | %5u | %s\n", sizePos, sizeNormal, sizeText, sizePara, sizeFace, &waveFrontElement->Name[0]);
    }

    printf(" +-------+-------+-------+-------+-------+-------\n");
        
    for (unsigned int i = 0; i < waveFont.Materials.Size(); i++)
    {
        MTL* mtl = &waveFont.Materials[i];

        for (unsigned int j = 0; j < mtl->MaterialList.Size(); j++)
        {
            Material* material = &mtl->MaterialList[j];

            printf(" Material: %s\n", &material->Name[0]);
            printf(" - Ambient  [%4.4f|%4.4f|%4.4f]\n", material->Ambient.X, material->Ambient.Y, material->Ambient.Z);
            printf(" - Diffuse  [%4.4f|%4.4f|%4.4f]\n", material->Diffuse.X, material->Ambient.Y, material->Ambient.Z);
            printf(" - Specular [%4.4f|%4.4f|%4.4f]\n", material->Specular.X, material->Ambient.Y, material->Ambient.Z);
        }

        printf(" +-------+-------+-------+-------+-------+-------\n");
    }
}  