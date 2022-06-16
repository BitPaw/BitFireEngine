#include "BMPType.h"

#include <Container/ClusterShort.h>

#define BMPHeaderIDOS2StructBitmapArray     MakeShort('B', 'M')
#define BMPHeaderIDWindows                  MakeShort('B', 'A')
#define BMPHeaderIDOS2StructColorIcon       MakeShort('C', 'I')
#define BMPHeaderIDOS2ConstColorPointer     MakeShort('C', 'P')
#define BMPHeaderIDOS2StructIcon            MakeShort('I', 'C')
#define BMPHeaderIDOS2Pointer               MakeShort('P', 'C')

const BF::BMPType BF::ConvertBMPType(const ClusterInt byteCluster)
{
    switch(byteCluster.Value)
    {
        case BMPHeaderIDOS2StructBitmapArray:
            return BMPType::OS2StructBitmapArray;

        case BMPHeaderIDWindows:
            return BMPType::Windows;

        case BMPHeaderIDOS2StructColorIcon:
            return BMPType::OS2StructColorIcon;

        case BMPHeaderIDOS2ConstColorPointer:
            return BMPType::OS2ConstColorPointer;

        case BMPHeaderIDOS2StructIcon:
            return BMPType::OS2StructIcon;

        case BMPHeaderIDOS2Pointer:
            return BMPType::OS2Pointer;

        default:
            return BMPType::Invalid;
    }
}

const ClusterInt BF::ConvertBMPType(const BMPType type)
{
    ClusterInt byteCluster;

    switch(type)
    {
        default:
        case BF::BMPType::Invalid:
            byteCluster.Value = 0;
            break;

        case BF::BMPType::Windows:
            byteCluster.Value = BMPHeaderIDWindows;
            break;

        case BF::BMPType::OS2StructBitmapArray:
            byteCluster.Value = BMPHeaderIDOS2StructBitmapArray;
            break;

        case BF::BMPType::OS2StructColorIcon:
            byteCluster.Value = BMPHeaderIDOS2StructColorIcon;
            break;

        case BF::BMPType::OS2ConstColorPointer:
            byteCluster.Value = BMPHeaderIDOS2ConstColorPointer;
            break;

        case BF::BMPType::OS2StructIcon:
            byteCluster.Value = BMPHeaderIDOS2StructIcon;
            break;

        case BF::BMPType::OS2Pointer:
            byteCluster.Value = BMPHeaderIDOS2Pointer;
            break;
    }

    return byteCluster;
}