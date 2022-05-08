#pragma once

#include <cstddef>

namespace BF
{
	enum class ProcessorVendor
	{
		Invalid,

		Unkown,

		Intel,
		AMD
	};

	struct ProcessorInfo
	{
		public:
        char VendorName[0x20];
        char BrandName[0x40];

		ProcessorVendor Vendor;

        bool SSE3;
        bool PCLMULQDQ;
        bool MONITOR;
        bool SSSE3;
        bool FMA;
        bool CMPXCHG16B;
        bool SSE41;
        bool SSE42;
        bool MOVBE;
        bool POPCNT;
        bool AES;
        bool XSAVE;
        bool OSXSAVE;
        bool AVX;
        bool F16C;
        bool RDRAND;

        bool MSR;
        bool CX8;
        bool SEP;
        bool CMOV;
        bool CLFSH;
        bool MMX;
        bool FXSR;
        bool SSE;
        bool SSE2;

        bool FSGSBASE;
        bool BMI1;
        bool IntelHLE;
        bool AVX2;
        bool BMI2;
        bool ERMS;
        bool INVPCID;
        bool IntelRTM;
        bool AVX512F;
        bool RDSEED;
        bool ADX;
        bool AVX512PF;
        bool AVX512ER;
        bool AVX512CD;
        bool SHA;

        bool PREFETCHWT1;

        bool LAHF;
        bool IntelLZCNT;
        bool AMDABM;
        bool AMDSSE4a;
        bool AMDXOP;
        bool AMDTBM;

        bool IntelSYSCALL;
        bool AMDMMXEXT;
        bool IntelRDTSCP;
        bool AMD3DNOWEXT;
        bool AMD3DNOW;
	};

	class Processor
	{
		public:
		static bool FetchInfo(ProcessorInfo& processorInfo);

		const size_t ClockCyclesSinceLastReset() const;
	};
}
