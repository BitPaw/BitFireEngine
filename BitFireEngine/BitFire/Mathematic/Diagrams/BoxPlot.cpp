#include "BoxPlot.h"

BF::BoxPlot::BoxPlot(List<double> values)
{
    const int iqrFactor = 1;
    bool hasEvenLengh = false;
    int medianIndex = -1;
    int lowerQuartialIndex = -1;
    int higherQuartialIndex = -1;

    Size = values.Size();
    Sum = -1;
    Minimum = std::numeric_limits<double>::min();
    Maximum = std::numeric_limits<double>::max();
    Avrage = -1;
    IQR = -1;

    HigherWhisker = -1;
    HigherQuartial = -1;
    Median = -1;
    LowerQuartial = -1;
    LowerWhisker = -1;

    // Calc
    {    
        hasEvenLengh = (Size % 2) == 0;
        medianIndex = Size / 2;
        lowerQuartialIndex = medianIndex / 2;
        higherQuartialIndex = medianIndex + lowerQuartialIndex;
    }

    //values.Sort();

    for (int i = 0; i < Size; i++)
    {
        double value = values[i];
        bool isBigger = Maximum < value;
        bool isSmaler = Minimum > value;

        if (isBigger)
        {
            Maximum = value;
        }

        if (isSmaler)
        {
            Minimum = value;
        }

        Sum += value;
    }

    Avrage = Sum / Size;

    if (hasEvenLengh)
    {
        double a, b;

        a = values[medianIndex - 1];
        b = values[medianIndex];
        Median = (a + b) / 2.0;

        a = values[lowerQuartialIndex - 1];
        b = values[lowerQuartialIndex];
        LowerQuartial = (a + b) / 2.0;

        a = values[higherQuartialIndex - 1];
        b = values[higherQuartialIndex];
        HigherQuartial = (a + b) / 2.0;
    }
    else
    {
        Median = values[medianIndex];
        LowerQuartial = values[lowerQuartialIndex];
        HigherQuartial = values[higherQuartialIndex];
    }

    IQR = HigherQuartial - LowerQuartial;

    HigherWhisker = Median + IQR * iqrFactor;
    LowerWhisker = Median - IQR * iqrFactor;

    // OutOfBounce
    {
        unsigned int counter = 0;
        unsigned int index = 0;

        for (int i = 0; i < Size; i++)
        {
            double value = values[i];
            bool isStrayBullet = value > HigherWhisker || value < LowerWhisker;

            if (isStrayBullet)
            {
                counter++;
            }
        }

        OutOfBounce.ReSize(counter);

        for (int i = 0; i < Size; i++)
        {
            double value = values[i];
            bool isStrayBullet = value > HigherWhisker || value < LowerWhisker;

            if (isStrayBullet)
            {
                OutOfBounce[index++] = value;
            }
        }
    }
}