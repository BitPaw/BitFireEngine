#include "Restklassen.h"

#include <stdio.h>
#include <math.h>
#include <map>



int Restklasse::set_Generator(int mod)
{
    int* all = new int[mod];
    for (int z = 0; z <= mod - 1; z++)
    {
        all[z] = -1;
    }
    for (int i = 0; i <= mod - 1; i++)
    {
        for (int j = 0; j <= mod - 1; j++)
        {
            if (all[((int)pow((double)i, (double)j) % mod)] == -1)
            {
                all[j] = i;
            }
        }
    }
    for (int x = 1; x <= mod - 1; x++)
    {
        if (all[x - 1] != all[x])
        {
            return -1;
        }
    }
    return all[0];
}

bool Restklasse::Zyklisch()
{
    int length = restklasse[0][0];
    int* rest = new int[length];
    for (int z = 0; z < length; z++)
    {
        rest[z] = -1;
    }
    for (int x = 1; x <= length; x++)
    {
        for (int y = 1; y <= length; y++)
        {
            if (restklasse[x][y] < length)
            {
                rest[restklasse[x][y]] = restklasse[x][y];
            }
        }
    }
    for (int x = 0; x < length; x++)
    {
        if (rest[x] != x)
        {
            return false;
        }
    }
    return true;
}

int Restklasse::neutralElement()
{
    int length = Restklasse::restklasse[0][0];
    for (int x = 1; x <= length; x++)
    {
        for (int y = 1; y <= length; y++)
        {
            int reset;
            if (restklasse[x][y] == x - 1)
            {
                reset = y;
                while (y <= length && y != -1)
                {
                    if (restklasse[x][y] != y - 1)
                    {
                        y = -1;
                    }
                    else
                    {
                        y++;
                    }
                }
                if (y == length + 1)
                {
                    return x - 1;
                }
                y = reset;
            }
            else if (restklasse[x][y] == y - 1)
            {
                reset = x;
                while (x < length && x != -1)
                {
                    if (restklasse[x][y] != x - 1)
                    {
                        x = -1;
                    }
                    else
                    {
                        x++;
                    }
                }
                if (x == length + 1)
                {
                    return y - 1;
                }
                x = reset;
            }
        }
    }
    return -1;
}
int Restklasse::inverse(int number)
{
    return 0;
}
void Restklasse::print()
{
    if (restklasse == nullptr)
    {
        printf("nicht Initialisierte Restklasse");
        return;
    }
    for (int x = 0; x <= restklasse[0][0]; x++)
    {
        for (int y = 0; y <= restklasse[0][0]; y++)
        {
            /*if (x == 0 && y == 0)
            {
                printf(" | %s | ", operation);
            }
            else
            {*/
            printf(" | %d | ", restklasse[x][y]);
            //}
        }
        printf("\n");
    }
    printf("der Zahlenraum ist %d\n", restklasse[0][0]);
}
Restklasse::Restklasse(int mod, int(*function)(int, int))
{
    int** rest = new int* [mod + 1];
    for (int i = 0; i < mod + 1; i++) {
        rest[i] = new int[mod + 1];
    }
    for (int x = 0; x <= mod; x++) {
        for (int y = 0; y <= mod; y++) {
            if (x == 0 && y == 0) {
                rest[x][y] = mod;
            }
            else if (x == 0) {
                rest[x][y] = y - 1;
            }
            else if (y == 0) {
                rest[x][y] = x - 1;
            }
            else {
                rest[x][y] = function((x - 1), (y - 1)) % mod;
            }
        }
    }
    restklasse = rest;
    generator = set_Generator(mod);
    hat_generator = generator >= 0 ? true : false;
    neutralelement = neutralElement();
    hat_neutralElement = neutralelement >= 0 ? true : false;
    zyklisch = Zyklisch();
    operation = function;
}

Restklasse::Restklasse()
{
    Restklasse::restklasse = new int* [2];
    for (int i = 0; i <= 2; i++)
    {
        Restklasse::restklasse[i] = new int[2];
        for (int j = 0; j <= 2; j++)
        {
            if (i == 0)
            {
                Restklasse::restklasse[i][j] = j;
            }
            else if (j == 0)
            {
                Restklasse::restklasse[i][j] = i;
            }
            else
            {
                Restklasse::restklasse[i][j] = ((i - 1) + (j - 1)) % 2;
            }
        }
    }
    restklasse[0][0] = 2;
   // Operation = "Initialisiert"; //TODO: ERROR: NOT FOUND
    generator = set_Generator(0);
    hat_generator = generator >= 0 ? true : false;
    neutralelement = neutralElement();
    hat_neutralElement = neutralelement >= 0 ? true : false;
    zyklisch = Zyklisch();
}
/*TODO:
    * controll all edgecases:
        - Modulo 0
        - ...
    * implement Algorithim
*/
unsigned int Restklasse::chineseRemainder(unsigned int* remainderset, unsigned int* moduloset)
{
    unsigned int remaindercount = sizeof(remainderset) / sizeof(unsigned int);
    unsigned int modulocount = sizeof(moduloset) / sizeof(unsigned int);

    if (remaindercount != modulocount)
    {
        return 0;
    }
    std::map<unsigned int, unsigned int> doublecheck;
    for (int i = 0; i < remaindercount; i++)
    {
        if (doublecheck.count(moduloset[i]) != 0)
        {
            return -1;
        }
        doublecheck[moduloset[i]] = remainderset[i];
    }


    unsigned int productModulo = 1;
    for (int i = 0; i < modulocount; i++)
    {
        productModulo *= moduloset[i];
    }

    if (productModulo <= 1)
    {
        return 0;
    }

    return 0;
}