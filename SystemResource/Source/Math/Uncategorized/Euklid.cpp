#include "Euklid.h"
#include <iostream>

Euklid::Euklid(int a, int b)
{
   int maxEntries = a < b ? log2(a) + 1 : log2(b) + 1;
   liste = (Euklid_element*)malloc(maxEntries * sizeof(Euklid_element));
   Euklid_element element;
   for(int i=0;b!=0;i++) 
   {   
		element.a = a;
		element.b = b;
		element.times = a / b;
		element.remainder = a % b;
		element.x = 0;
		element.y = 0;
		liste[i]=element;
		a = b;
		b = element.remainder;
        ggt = a;
   }
}

void Euklid::Advanced()
{
    int size = 0;
    while(liste[size].remainder!=0) size++;
    Euklid_element element = liste[size];
    element.y = 1;
    element.x = 0;
    liste[size] = element;
    int prevx = 0,y=1,x=1;
    for (int i = size-1; i >= 0; i--) 
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

void Euklid::print()
{
    /*
    std::cout << "Int a = " << liste.get(0).a << " und Int b = " << liste.get(0).b << " bildet sich wie folgt.\n";
    std::cout << "| a | b | mal | rest | x | y |\n";
    for (int j = 0; j < liste.size(); j++) {
        std::cout << "| " << liste.get(j).a << " | " << liste.get(j).b << " | " << liste.get(j).times << " | " << liste.get(j).remainder << " | ";
        std::cout << liste.get(j).x << " | " << liste.get(j).y << " |\n";
    }
    */
    std::cout << "Int a = " << liste[0].a << " und Int b = " << liste[0].b << " bildet sich wie folgt.\n";
    std::cout << "| a | b | mal | rest | x | y |\n";
    int limit = ((int)(log2(liste[0].b) + 1));
    for (int i = 0; i < limit&&(liste[i-1].remainder!=0||i==0); i++)
    {
        std::cout << "| " << liste[i].a << " | " << liste[i].b << " | " << liste[i].times << " | " << liste[i].remainder << " | " << liste[i].x << " | " << liste[i].y << " |\n" ;
    }
}



