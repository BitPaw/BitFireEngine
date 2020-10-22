#include "Interpolate.h"

float BF::Interpolate::Liniar(const float yMinimum, const float yMaximum, const float xMinimum, const float xMaximum, float xValue)
{
    // Cap Value
    xValue = xValue > xMaximum ? xMaximum : xValue;
    xValue = xValue < xMinimum ? xMinimum : xValue;

    // ((ydelta * xValueDelta) / xdelta) + yMinimum;

    return (((yMaximum - yMinimum) * (xValue - xMinimum)) / (xMaximum - xMinimum)) + yMinimum;
}

float BF::Interpolate::LiniarClampBetweenZeroAndOne(const float minimum, const float maximum, const float value)
{
    return Interpolate::Liniar(0, 1, minimum, maximum, value);
}

unsigned int BF::Interpolate::LiniarClampAsRGBColor(const float minimum, const float maximum, const float value)
{
    float result = Interpolate::Liniar(0, 255, minimum, maximum, value);
    unsigned int convertedResult = static_cast<unsigned int>(result);
    
    return convertedResult;
}