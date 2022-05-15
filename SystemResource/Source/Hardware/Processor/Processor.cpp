#include "Processor.h"

#include <OS/OSDefine.h>
#include <Text/Text.h>

#if defined(OSUnix)
#include <cpuid.h>
#elif defined(OSWindows)
#include <intrin.h>
#endif
#include <iostream>

#define BitIndex(data, index) (data & (1 << index)) >> index

bool BF::Processor::FetchInfo(ProcessorInfo& processorInfo)
{
    bool isIntel = false;
    bool isAMD = false;

    int nIds_ = -1;
    int nExIds_ = -1;
    std::string vendor_;
    int f_1_ECX_ = -1;
    int f_1_EDX_ = -1;
    int f_7_EBX_ = -1;
    int f_7_ECX_ = -1;
    int f_81_ECX_ = -1;
    int f_81_EDX_ = -1;
    int data_[10][4]{0};
    int extdata_[128]{ 0 };


	int cpuInfo[4]{0};

#if defined(OSUnix)
   // ????
#elif defined(OSWindows)
   for (size_t a = 0; a < 4; a++)
	{
		__cpuid(cpuInfo, a);
	}
#endif




    nIds_ = cpuInfo[0];

    for (size_t i = 0; i <= nIds_; ++i)
    {
    #if defined(OSUnix)
   // ????
#elif defined(OSWindows)
  __cpuidex(cpuInfo, i, 0);
#endif


        for (size_t j = 0; j < 4; j++)
        {
            data_[i][j] = cpuInfo[j];   // data_.push_back(cpuInfo);
        }
    }

    // Capture vendor string
    {
        Text::Clear(processorInfo.VendorName, sizeof(processorInfo.VendorName));

        *reinterpret_cast<int*>(processorInfo.VendorName) = data_[0][1];
        *reinterpret_cast<int*>(processorInfo.VendorName + 4) = data_[0][3];
        *reinterpret_cast<int*>(processorInfo.VendorName + 8) = data_[0][2];

        const char* vendorNameIntel = "GenuineIntel";
        const char* vendorNameAMD = "AuthenticAMD";

        isIntel = Text::Compare(vendorNameIntel, processorInfo.VendorName, sizeof(vendorNameIntel));
        isAMD = Text::Compare(vendorNameAMD, processorInfo.VendorName, sizeof(vendorNameAMD));

        if (isIntel)
        {
            processorInfo.Vendor = ProcessorVendor::Intel;
            isIntel = true;

        }
        else if (isAMD)
        {
            processorInfo.Vendor = ProcessorVendor::AMD;
            isAMD = true;
        }
    }


    // load bitset with flags for function 0x00000001
    if (nIds_ >= 1)
    {
        f_1_ECX_ = data_[1][2];
        f_1_EDX_ = data_[1][3];
    }

    // load bitset with flags for function 0x00000007
    if (nIds_ >= 7)
    {
        f_7_EBX_ = data_[7][1];
        f_7_ECX_ = data_[7][2];
    }

    // Calling __cpuid with 0x80000000 as the function_id argument
    // gets the number of the highest valid extended ID.


#if defined(OSUnix)
   // ????
#elif defined(OSWindows)
    __cpuid(cpuInfo, 0x80000000);
#endif



    nExIds_ = cpuInfo[0];

    // Brand Name
    {
        const size_t brandNameSize = sizeof(processorInfo.BrandName);

        for (size_t i = 0; i < brandNameSize; ++i) processorInfo.BrandName[i] = '\0';

        size_t exDataindex = 0;

        for (size_t i = 0x80000000; i <= nExIds_; ++i)
        {
        #if defined(OSUnix)
        #elif defined(OSWindows)
            __cpuidex(cpuInfo, i, 0);
            #endif // defined

            extdata_[exDataindex++] = cpuInfo[0];
            extdata_[exDataindex++] = cpuInfo[1];
            extdata_[exDataindex++] = cpuInfo[2];
            extdata_[exDataindex++] = cpuInfo[3];
        }

        if (exDataindex > 0)
        {
            const char* brandName = (const char*)extdata_ + 32;

            Text::Copy(brandName, brandNameSize, processorInfo.BrandName, brandNameSize);
        }
    }

    processorInfo.SSE3 = BitIndex(f_1_ECX_, 0);
    processorInfo.PCLMULQDQ = BitIndex(f_1_ECX_,1);
    processorInfo.MONITOR = BitIndex(f_1_ECX_ ,3);
    processorInfo.SSSE3 = BitIndex(f_1_ECX_,9);
    processorInfo.FMA = BitIndex(f_1_ECX_,12);
    processorInfo.CMPXCHG16B = BitIndex(f_1_ECX_,13);
    processorInfo.SSE41 = BitIndex(f_1_ECX_,19);
    processorInfo.SSE42 = BitIndex(f_1_ECX_,20);
    processorInfo.MOVBE = BitIndex(f_1_ECX_,22);
    processorInfo.POPCNT = BitIndex(f_1_ECX_,23);
    processorInfo.AES = BitIndex(f_1_ECX_,25);
    processorInfo.XSAVE = BitIndex(f_1_ECX_,26);
    processorInfo.OSXSAVE = BitIndex(f_1_ECX_,27);
    processorInfo.AVX = BitIndex(f_1_ECX_,28);
    processorInfo.F16C = BitIndex(f_1_ECX_,29);
    processorInfo.RDRAND = BitIndex(f_1_ECX_, 30);

    processorInfo.MSR = BitIndex(f_1_EDX_,5);
    processorInfo.CX8 = BitIndex(f_1_EDX_,8);
    processorInfo.SEP = BitIndex(f_1_EDX_,11);
    processorInfo.CMOV = BitIndex(f_1_EDX_,15);
    processorInfo.CLFSH = BitIndex(f_1_EDX_,19);
    processorInfo.MMX = BitIndex(f_1_EDX_,23);
    processorInfo.FXSR = BitIndex(f_1_EDX_,24);
    processorInfo.SSE = BitIndex(f_1_EDX_,25);
    processorInfo.SSE2 = BitIndex(f_1_EDX_,26);

    processorInfo.FSGSBASE = BitIndex(f_7_EBX_,0);
    processorInfo.BMI1 = BitIndex(f_7_EBX_,3);
    processorInfo.IntelHLE = isIntel && BitIndex(f_7_EBX_, 4);
    processorInfo.AVX2 = BitIndex(f_7_EBX_,5);
    processorInfo.BMI2 = BitIndex(f_7_EBX_,8);
    processorInfo.ERMS = BitIndex(f_7_EBX_,9);
    processorInfo.INVPCID = BitIndex(f_7_EBX_,10);
    processorInfo.IntelRTM = isIntel && BitIndex(f_7_EBX_,11);
    processorInfo.AVX512F = BitIndex(f_7_EBX_,16);
    processorInfo.RDSEED = BitIndex(f_7_EBX_,18);
    processorInfo.ADX = BitIndex(f_7_EBX_,19);
    processorInfo.AVX512PF = BitIndex(f_7_EBX_,26);
    processorInfo.AVX512ER = BitIndex(f_7_EBX_,27);
    processorInfo.AVX512CD = BitIndex(f_7_EBX_,28);
    processorInfo.SHA = BitIndex(f_7_EBX_,29);

    processorInfo.PREFETCHWT1 = BitIndex(f_7_ECX_,0);

    processorInfo.LAHF = BitIndex(f_81_ECX_, 0);
    processorInfo.IntelLZCNT = isIntel && BitIndex(f_81_ECX_, 5);
    processorInfo.AMDABM = isAMD && BitIndex(f_81_ECX_, 5);
    processorInfo.AMDSSE4a = isAMD && BitIndex(f_81_ECX_, 6);
    processorInfo.AMDXOP = isAMD && BitIndex(f_81_ECX_, 11);
    processorInfo.AMDTBM = isAMD && BitIndex(f_81_ECX_, 21);

    processorInfo.IntelSYSCALL = isIntel && BitIndex(f_81_EDX_, 11);
    processorInfo.AMDMMXEXT = isAMD && BitIndex(f_81_EDX_, 22);
    processorInfo.IntelRDTSCP = isIntel && BitIndex(f_81_EDX_, 27);
    processorInfo.AMD3DNOWEXT = isAMD && BitIndex(f_81_EDX_, 30);
    processorInfo.AMD3DNOW = isAMD && BitIndex(f_81_EDX_, 31);

	return true;
}

const size_t BF::Processor::ClockCyclesSinceLastReset() const
{
#if defined(OSUnix)
    return -1;
#elif defined(OSWindows)
	return __rdtsc();
#endif
}
