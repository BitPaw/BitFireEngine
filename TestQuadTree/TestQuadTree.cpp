#include <iostream>

#include "../SystemResource/Source/Math/Math.h"
#include "../SystemResource/Source/Math/Geometry/Vector2.hpp"
#include "../SystemResource/Source/Container/QuadTree/QuadTree.hpp"

using namespace BF;

int main()
{
    const int amountOfPoints = 10;

    struct ImaginaryGameObject
    {
        char ID = 0;
        Vector2<float> Position;
    };

    ImaginaryGameObject objects[amountOfPoints];
    QuadTree<float, Vector2<float>> quadTree;

    for (size_t i = 0; i < amountOfPoints; i++)
    {
        objects[i].ID = i;
        objects[i].Position.Set(Math::RandomeNumber() % 100, Math::RandomeNumber() % 100);
    }

    quadTree.MemoryReserve(amountOfPoints);
    quadTree.NodeRootSetField(100,100);

    for (size_t i = 0; i < amountOfPoints; i++)
    {
        ImaginaryGameObject& obj = objects[i];

        quadTree.Add(obj.Position.X, obj.Position.Y, 1, 1, &obj.Position);
    }

    std::cout << "Hello World!\n";
}