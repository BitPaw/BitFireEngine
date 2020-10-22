#pragma once

#include <limits>

#include "../../Utility/List.hpp"

namespace BF
{
    class BoxPlot
    {
    public:
        int Size;
        double Sum;
        double Minimum;
        double Maximum;
        double Avrage;
        double IQR;
    
        double HigherWhisker;
        double HigherQuartial;   
        double Median;
        double LowerQuartial;
        double LowerWhisker;

        List<double> OutOfBounce;

        BoxPlot(List<double> values);
    };
}