#pragma once

#define AxisPositionX 0
#define AxisPositionY 1
#define AxisViewX 2
#define AxisViewY 3

namespace BF
{
    struct ControllerData
    {
        public:
        unsigned int Axis[6];  // X,Y,Z,R,U,V
        unsigned int ButtonPressedBitList;           
        unsigned int ButtonAmountPressed;        // current button number pressed
        unsigned int ControlPad;
    };
}