#include "Model.h"
#include "../../Mathematic/Geometry/Shape/Triangle.h"
#include "../../Mathematic/Geometry/Shape/Rectangle.h"



BF::Model::Model()
{
    RenderInformation.RenderType = RenderMode::Unkown;
}

BF::Model::Model(AsciiString& name)
{   
    RenderInformation.RenderType = RenderMode::Unkown; 
    ModelName.Copy(name);
}

void BF::Model::Move(float x, float y, float z)
{
    Move(Position<float>(x, y, z));
}

void BF::Model::Move(Position<float> position)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
    {
        GlobalMesh.VertexList[i]->CurrentPosition.Add(position);
    }

    _currentPosition += position;
}

void BF::Model::MoveTo(float x, float y, float z)
{
    MoveTo(Position<float>(x, y, z));
}

void BF::Model::MoveTo(Position<float> position)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];

        vertex->CurrentPosition.Substract(_currentPosition);
        vertex->CurrentPosition.Add(position);
    }

    _currentPosition = position;
}

void BF::Model::Rotate(float x, float y, float z)
{
    Rotate(Position<float>(x, y, z));
}

void BF::Model::Rotate(Position<float> rotation)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];
        Position<float>* currentPosition = &vertex->CurrentPosition;

        currentPosition->Substract(_currentPosition);
        currentPosition->Rotate(rotation);
        currentPosition->Add(_currentPosition);
    }

    _currentRotation += rotation;

    if (_currentRotation.X > 360)
    {
        _currentRotation.X -= 360;
    }

    if (_currentRotation.Y > 360)
    {
        _currentRotation.Y -= 360;
    }

    if (_currentRotation.Z > 360)
    {
        _currentRotation.Z -= 360;
    }
}

void BF::Model::RotateTo(float x, float y, float z)
{

}

void BF::Model::RotateTo(Position<float> rotation)
{

}



void BF::Model::Orbit(float x, float y, float z)
{
    Orbit(Position<float>(x, y, z));
}

void BF::Model::Orbit(Position<float> rotation)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];

        vertex->CurrentPosition.Rotate(rotation);
    }
}

void BF::Model::Orbit(Position<float> rotation, Position<float> ancerPosition)
{
}


void BF::Model::Scale(float x, float y, float z)
{
    Scale(Position<float>(x, y, z));
}

void BF::Model::Scale(Position<float> scaleFactor)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];

        vertex->CurrentPosition.Multiply(scaleFactor);
    }
}


BF::Position<float> BF::Model::CurrentPosition()
{
    return _currentPosition;
}

BF::Position<float> BF::Model::CurrentRotation()
{
    return _currentRotation;
}

void BF::Model::CalculateNormalVectors()
{
    for (unsigned int i = 0; i < MeshList.Size(); i++)
    {
        Mesh* mesh = &MeshList[i];
        List<MeshIndexData>* indexList = &mesh->IndexList;
        List<Vertex>* vertexList = &mesh->VertexList;
        unsigned int indexListSize = mesh->IndexList.Size();

        switch (indexListSize)
        {
            case 0:
                // Poligon has no points, there cant be a normal verctor.
                break;

            case 1:
                // Poligon has only one Point, normal will be teh point itself.

                break;

            case 2:
                // There are only 2 points, you cant render something like this. Or can it?
                break;

            case 3:                
            default:     
                switch (RenderInformation.RenderType)
                {
                    case RenderMode::Triangle:
                    {
                        unsigned int i = 0;
                        unsigned int normalPointIndex = 0;
                        float normals = indexListSize / 3.0f;
                        unsigned int normalSaveVectorSize = Math::Floor(normals);
                        unsigned int normalExactVectorSize = Math::Ceiling(normals);
                        mesh->NormalPointList.ReSize(normalExactVectorSize);

                        while (normalPointIndex < normalSaveVectorSize)
                        {
                            MeshIndexData* mIndexA = &(*indexList)[i++];
                            MeshIndexData* mIndexB = &(*indexList)[i++];
                            MeshIndexData* mIndexC = &(*indexList)[i++];

                            Vertex* vertexA = &(*vertexList)[mIndexA->VertexPositionID];
                            Vertex* vertexB = &(*vertexList)[mIndexB->VertexPositionID];
                            Vertex* vertexC = &(*vertexList)[mIndexC->VertexPositionID];

                            Triangle triangle
                            (
                                vertexA->CurrentPosition,
                                vertexB->CurrentPosition,
                                vertexC->CurrentPosition
                            );

                            mIndexA->NormalVectorID = normalPointIndex;
                            mIndexB->NormalVectorID = normalPointIndex;
                            mIndexC->NormalVectorID = normalPointIndex;

                            mesh->NormalPointList[normalPointIndex++] = triangle.NormalDirection();
                        }

                        if (normalSaveVectorSize < normalExactVectorSize)
                        {
                            MeshIndexData* mIndexA = &(*indexList)[i - 1];
                            MeshIndexData* mIndexB = &(*indexList)[i];
                            MeshIndexData* mIndexC = &(*indexList)[0];

                            Vertex* vertexA = &(*vertexList)[mIndexA->VertexPositionID];
                            Vertex* vertexB = &(*vertexList)[mIndexB->VertexPositionID];
                            Vertex* vertexC = &(*vertexList)[mIndexC->VertexPositionID];

                            Triangle triangle
                            (
                                vertexA->CurrentPosition,
                                vertexB->CurrentPosition,
                                vertexC->CurrentPosition
                            );

                            mIndexA->NormalVectorID = normalPointIndex;
                            mIndexB->NormalVectorID = normalPointIndex;
                            mIndexC->NormalVectorID = normalPointIndex;

                            mesh->NormalPointList[normalPointIndex++] = triangle.NormalDirection();
                        }
                }
                        break;

                    case RenderMode::Square:
                    {
                        unsigned int i = 0;
                        unsigned int normalPointIndex = 0;
                        float normals = indexListSize / 4.0f;
                        unsigned int normalSaveVectorSize = Math::Floor(normals);
                        unsigned int normalExactVectorSize = Math::Ceiling(normals);
                        mesh->NormalPointList.ReSize(normalExactVectorSize);

                        while (normalPointIndex < normalSaveVectorSize)
                        {
                            MeshIndexData* mIndexA = &(*indexList)[i];
                            MeshIndexData* mIndexB = &(*indexList)[i + 1];
                            MeshIndexData* mIndexC = &(*indexList)[i + 2];
                            MeshIndexData* mIndexD = &(*indexList)[i + 3];

                            Vertex* vertexA = &(*vertexList)[mIndexA->VertexPositionID];
                            Vertex* vertexB = &(*vertexList)[mIndexB->VertexPositionID];
                            Vertex* vertexC = &(*vertexList)[mIndexC->VertexPositionID];
                            Vertex* vertexD = &(*vertexList)[mIndexD->VertexPositionID];

                            Rectangle rectangle
                            (
                                vertexA->CurrentPosition,
                                vertexB->CurrentPosition,
                                vertexC->CurrentPosition,
                                vertexD->CurrentPosition
                            );

                            mIndexA->NormalVectorID = normalPointIndex;
                            mIndexB->NormalVectorID = normalPointIndex;
                            mIndexC->NormalVectorID = normalPointIndex;
                            mIndexD->NormalVectorID = normalPointIndex;

                            mesh->NormalPointList[normalPointIndex++] = rectangle.NormalDirection();
                        }

                        if (normalSaveVectorSize < normalExactVectorSize)
                        {
                            printf("Error");
                        }



              

                    }
                        break;


                }
                break;
        }



        /*

                for (unsigned int i = 0; i < size; i += 3)
                {
                    unsigned int indexA = (*indexList)[i].VertexPositionID;
                    unsigned int indexB = (*indexList)[i + 1].VertexPositionID;
                    unsigned int indexC = (*indexList)[i + 2].VertexPositionID;

                    Vertex* vertexA = &(*vertexList)[indexA];
                    Vertex* vertexB = &(*vertexList)[indexB];
                    Vertex* vertexC = &(*vertexList)[indexC];

                    Position<float>* aPos = &vertexA->CurrentPosition;
                    Position<float>* bPos = &vertexB->CurrentPosition;
                    Position<float>* cPos = &vertexC->CurrentPosition;

                    // BAd code, this memory waste
                    (*indexList)[i].NormalVectorID = normalPointIndex;
                    mesh->NormalPointList[normalPointIndex++] = aPos->CrossProduct(*bPos);

                    (*indexList)[i + 1].NormalVectorID = normalPointIndex;
                    mesh->NormalPointList[normalPointIndex++] = bPos->CrossProduct(*cPos);

                    (*indexList)[i + 2].NormalVectorID = normalPointIndex;
                    mesh->NormalPointList[normalPointIndex++] = cPos->CrossProduct(*aPos);
                }

                */
                
        



    }   
}

void BF::Model::UseTexturePointAsColor()
{
    const unsigned int indexListLength = GlobalMesh.IndexList.Size();

    GlobalMesh.ColorList.ReSize(indexListLength);
    
    /*MeshList[0].ColorList.ReSize(indexListLength);

    // Link
    for (unsigned int i = 0; i < indexListLength; i++)
    {
        GlobalMesh.ColorList[i] = &MeshList[0].ColorList[i];
    }
    */

    // Color
    for (unsigned int i = 0; i < indexListLength; i++)
    {
        MeshIndexData* meshIndexData = GlobalMesh.IndexList[i];
        
        Vertex* vertex = GlobalMesh.VertexList[meshIndexData->VertexPositionID];
        Point<float>* texturepoint = GlobalMesh.TexturePointList[meshIndexData->TexturePointID];

        vertex->ColorID = i;
        GlobalMesh.ColorList[i]->SetColor(texturepoint->X, texturepoint->Y, 0);
    }
}

void BF::Model::PrintModelData()
{
    printf("Meshes %u\n", MeshList.Size());

    for (unsigned int i = 0; i < MeshList.Size(); i++)
    {
        Mesh* mesh = &MeshList[i];

        printf("M: %5u %5u %5u\n", mesh->VertexList.Size(), mesh->NormalPointList.Size(), mesh->TexturePointList.Size());

        
    }
}

void BF::Model::PrintCurrentPosition()
{
    printf("ID:  Position: X:%5.2f Y:%5.2f Z:%5.2f\n", _currentPosition.X, _currentPosition.Y, _currentPosition.Z);
}

void BF::Model::PrintCurrentRotation()
{
    printf("ID:  Rotation: X:%5.2f Y:%5.2f Z:%5.2f\n", _currentRotation.X, _currentRotation.Y, _currentRotation.Z);
}

void BF::Model::UpdateGlobalMesh()
{
    const unsigned int length = MeshList.Size();
    unsigned int vertexListLength = 0;
    unsigned int texturePointListLength = 0;
    unsigned int normalPointListLength = 0;
    unsigned int colorListLength = ColorList.Size();
    unsigned int indexListLength = 0;

    unsigned int vertexIndex = 0;
    unsigned int textureIndex = 0;
    unsigned int normalIndex = 0;
    unsigned int colorIndex = 0;
    unsigned int indexIndex = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];

        vertexListLength += mesh->VertexList.Size();
        texturePointListLength += mesh->TexturePointList.Size();
        normalPointListLength += mesh->NormalPointList.Size();
        indexListLength += mesh->IndexList.Size();
    }

    GlobalMesh.VertexList.ReSize(vertexListLength);
    GlobalMesh.TexturePointList.ReSize(texturePointListLength);
    GlobalMesh.NormalPointList.ReSize(normalPointListLength);
    GlobalMesh.ColorList.ReSize(colorListLength);
    GlobalMesh.IndexList.ReSize(indexListLength); 

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];        

        vertexListLength = mesh->VertexList.Size();
        texturePointListLength = mesh->TexturePointList.Size();
        normalPointListLength = mesh->NormalPointList.Size();
        indexListLength = mesh->IndexList.Size();

        for (unsigned int i = 0; i < vertexListLength; i++)
        {
            GlobalMesh.VertexList[vertexIndex++] = &mesh->VertexList[i];
        }

        for (unsigned int i = 0; i < texturePointListLength; i++)
        {
            GlobalMesh.TexturePointList[textureIndex++] = &mesh->TexturePointList[i];
        }

        for (unsigned int i = 0; i < normalPointListLength; i++)
        {
            GlobalMesh.NormalPointList[normalIndex++] = &mesh->NormalPointList[i];
        }

        for (unsigned int i = 0; i < colorListLength; i++)
        {
            GlobalMesh.ColorList[colorIndex++] = &ColorList[i];
        }

        for (unsigned int i = 0; i < indexListLength; i++)
        {
            GlobalMesh.IndexList[indexIndex++] = &mesh->IndexList[i];
        }
    }
}

void BF::Model::ScaleTexturePoints(float x, float y)
{
    ScaleTexturePoints(Point<float>(x, y));
}

void BF::Model::ScaleTexturePoints(Point<float> scale)
{
    for (unsigned int i = 0; i < GlobalMesh.TexturePointList.Size(); i++)
    {
        GlobalMesh.TexturePointList[i]->Multiply(scale);
    }
}