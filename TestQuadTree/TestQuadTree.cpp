#include <iostream>

#include "../SystemResource/Source/Math/Math.h"
#include "../SystemResource/Source/Math/Geometry/Vector2.hpp"
#include "../SystemResource/Source/Container/QuadTree/QuadTree.hpp"


#include "../SystemResource/Source/Container/BitStreamHusk.h"
#include "../SystemResource/Source/Image/Image.h"
using namespace BF;

int main()
{
    unsigned char bitStuff[4] = { 0b11000111, 0b001110001 ,0b10001110 ,0b00001111 };

    BitStreamHusk bitStreamHusk(bitStuff, 4);

    unsigned int nr = 1;

    for (size_t i = 0; i < 20; i++)
    {
        BitStreamHusk::PrintBinary(nr);

        nr <<= 1;        
    }

    BitStreamHusk::PrintBinary((unsigned int)bitStuff);
   
    unsigned int a = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int b = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int c = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int d = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int e = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int f = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int g = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int h = bitStreamHusk.ExtractBitsAndMove(3);
    unsigned int i = bitStreamHusk.ExtractBitsAndMove(5);
    unsigned int j = bitStreamHusk.ExtractBitsAndMove(4);
   

    printf("\n\n");


    Image image;

    image.Load((const wchar_t*)"C:/Users/BitPaw/Videos/TEST_PNG.png");
    image.Save((const wchar_t*)"C:/Users/BitPaw/Videos/__Wurst.bmp", ImageFileFormat::BitMap);


    /*
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

    std::cout << "Hello World!\n";*/
}