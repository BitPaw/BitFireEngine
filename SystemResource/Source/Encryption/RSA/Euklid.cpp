#include "Euklid.h"
#include <Math/Math.h>
#include <Memory/MemoryX.h>
#include "Euklid_element.h"

#if Eukliddebug
#include <iostream>
#endif

Euklid::Euklid(int a, int b)
{
    int maxEntries = a < b ? MathLogarithmusBase2(a) + 1 : MathLogarithmusBase2(b) + 1;
    liste = BF::Memory::Allocate<Euklid_element>(maxEntries);
    Euklid_element element;

    // TODO: "liste" can be null, unhandled possible null pointer

    for (int i = 0; b != 0; i++)
    {
        element.a = a;
        element.b = b;
        element.times = a / b;
        element.remainder = a % b;
        element.x = 0;
        element.y = 0;
        liste[i] = element;
        a = b;
        b = element.remainder;
        ggt = a;
    }
}

void Euklid::Advanced()
{
    int size = 0;
    while (liste[size].remainder != 0) size++;
    Euklid_element element = liste[size];
    element.y = 1;
    element.x = 0;
    liste[size] = element;
    int prevx = 0, y = 1, x = 1;
    for (int i = size - 1; i >= 0; i--)
    {
        element = liste[i];
        y = (y * (element.times * -1) + prevx);
        element.x = x;
        prevx = x;
        element.y = y;
        x = y;
        liste[i] = element;
    }
}
#if Eukliddebug
void Euklid::print()
{
    std::cout << "Int a = " << liste[0].a << " und Int b = " << liste[0].b << " bildet sich wie folgt.\n";
    std::cout << "| a | b | mal | rest | x | y |\n";
    int limit = ((int)(BF::MathLogarithmusBase2(liste[0].b) + 1));
    for (int i = 0; i < limit && (liste[i - 1].remainder != 0 || i == 0); i++)
    {
        std::cout << "| " << liste[i].a << " | " << liste[i].b << " | " << liste[i].times << " | " << liste[i].remainder << " | " << liste[i].x << " | " << liste[i].y << " |\n";
    }
}
#endif 
