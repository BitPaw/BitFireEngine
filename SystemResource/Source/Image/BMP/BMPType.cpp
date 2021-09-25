#include "BMPType.h"

BF::BMPType BF::ConvertBMPType(unsigned char typeTag[2])
{
    switch (typeTag[0])
    {
        case 'B':
        {
            switch (typeTag[1])
            {
                case 'A':
                    return BMPType::OS2StructBitmapArray;

                case 'M':
                    return BMPType::Windows;
            }

            break;
        }
        case 'C':
        {
            switch (typeTag[1])
            {
                case 'I':
                    return BMPType::OS2StructColorIcon;

                case 'P':
                    return BMPType::OS2ConstColorPointer;
            }

            break;
        }
        case 'I':
        {
            if ('C' == typeTag[1])
            {
                return BMPType::OS2StructIcon;
            }

            break;
        }
        case 'P':
        {
            if ('C' == typeTag[1])
            {
                return BMPType::OS2Pointer;
            }

            break;
        }

        default:
            return BMPType::UnkownOrInavlid;
    }
}

void BF::ConvertBMPType(unsigned char typeTag[2], BMPType type)
{
    switch (type)
    {
        default:
        case BF::BMPType::UnkownOrInavlid:
            typeTag[0] = '?';
            typeTag[1] = '?';
            break;

        case BF::BMPType::Windows:
            typeTag[0] = 'B';
            typeTag[1] = 'M';
            break;

        case BF::BMPType::OS2StructBitmapArray:
            typeTag[0] = 'B';
            typeTag[1] = 'A';
            break;

        case BF::BMPType::OS2StructColorIcon:
            typeTag[0] = 'C';
            typeTag[1] = 'I';
            break;

        case BF::BMPType::OS2ConstColorPointer:
            typeTag[0] = 'C';
            typeTag[1] = 'P';
            break;

        case BF::BMPType::OS2StructIcon:
            typeTag[0] = 'I';
            typeTag[1] = 'C';
            break;

        case BF::BMPType::OS2Pointer:
            typeTag[0] = 'P';
            typeTag[1] = 'T';
            break; 
    }
}