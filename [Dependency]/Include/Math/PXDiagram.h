#ifndef PXDiagramINCLUDE
#define PXDiagramINCLUDE

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif
   

    typedef struct PXBoxPlot_
    {
        int Size;
        float Sum;
        float Minimum;
        float Maximum;
        float Avrage;
        float IQR;

        float HigherWhisker;
        float HigherQuartial;
        float Median;
        float LowerQuartial;
        float LowerWhisker;

        float OutOfBounceList;
        PXSize OutOfBounceListSize;
    }
    PXBoxPlot;
    
    
    PXPublic void PXBoxPlotConstruct(PXBoxPlot* const boxPlot);    

    PXPublic void PXBoxPlotCalculate(PXBoxPlot* const boxPlot, const float* const inputData, const PXSize inputDataSize);

#ifdef __cplusplus
}
#endif

#endif