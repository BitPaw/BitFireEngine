#ifndef PXProcessorINCLUDE
#define PXProcessorINCLUDE

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum PXProcessorBrand_
    {
        ProcessorBrandInvalid,
        ProcessorBrandAMD,
        ProcessorBrandIntel,
        ProcessorBrandWinChip,
        ProcessorBrandCyrix,
        ProcessorBrandTransmeta,
        ProcessorBrandNationalSemiconductor,
        ProcessorBrandNexGen,
        ProcessorBrandRise,
        ProcessorBrandSiS,
        ProcessorBrandUMC,
        ProcessorBrandVIA,
        ProcessorBrandDMAndPVortex,
        ProcessorBrandZhaoxin,
        ProcessorBrandHygon,
        ProcessorBrandMCSTElbrus,
        ProcessorBrandao486,
        ProcessorBrandbhyve,
        ProcessorBrandKVM,
        ProcessorBrandQEMU,
        ProcessorBrandMicrosoftHyperVOrVirtualPC,
        ProcessorBrandMicrosoftx86ToARM,
        ProcessorBrandParallels,
        ProcessorBrandVMware,
        ProcessorBrandXenHVM,
        ProcessorBrandProjectACRN,
        ProcessorBrandQNXHypervisor,
        ProcessorBrandAppleRosetta
    }
    PXProcessorBrand;

    typedef enum PXProcessorModelName_
    {
        ProcessorModelNameInvalid,

        Intel486DX25x33,
        Intel486DX50,
        Intel486SX,
        Intel486DX2,
        Intel486SL,
        Intel486SX2,
        Intel486DX2WB,
        Intel486DX4,
        Intel486DX4WB,
        IntelPentium60x66AStep,
        IntelPentium60x66,
        IntelPentium75x200,
        IntelOverDrivePODP5V83,
        IntelPentiumMMX,
        IntelMobilePentium75x200,
        IntelMobilePentiumMMX,
        IntelPentiumProAStep,
        IntelPentiumPro,
        IntelPentiumIIKlamath,
        IntelPentiumIIDeschutes,
        IntelCeleronMendocino,
        IntelPentiumIIIKatmai,
        IntelPentiumIIICoppermine,
        IntelMobilePentiumIII,
        IntelPentiumIII0x18um,
        IntelPentiumIII0x13um,
        IntelItanium,
        IntelPentiumIV0x18um,
        IntelPentiumIV0x13um,
        IntelPentiumIV0x09um,
        IntelItanium2,

        AMD486DX2,
        AMD486DX2WB,
        AMD486DX4,
        AMD486DX4WB,
        AMDAm5x86WT,
        AMDAm5x86WB,
        AMDK5SSA5,
        AMDK5,
        AMDK6,
        AMDK62,
        AMDK63,
        AMDK63P,
        AMDAthlon0x25um,
        AMDAthlon0x18um,
        AMDDuron,
        AMDAthlonThunderbird,
        AMDAthlonPalamino,
        AMDDuronMorgan,
        AMDAthlonThoroughbred,
        AMDAthlonBarton,
        AMDAthlon64,
        AMDAthlon64FXOperon

    }
    PXProcessorModelName;

    PXPrivate void PXProcessorModelNameGet(const PXProcessorModelName processorModelName, char* const name);
    PXPrivate PXProcessorBrand PXProcessorBrandDetect(const char* name);
    PXPrivate PXProcessorModelName PXProcessorModelNameDetect(const PXProcessorBrand processorBrand, const unsigned char famliy, const unsigned char model);

	typedef struct Processor_
	{
        PXProcessorBrand BrandID;
        PXProcessorModelName ModelNameID;

		char IdentityString[13];

		char NumberOfProcessors;
		char BrandName[64];  // string includes manufacturer, model and clockspeed



        // eax 
        unsigned char SteppingID;
        unsigned char Model;
        unsigned char Family;
        unsigned char ProcessorType; // Intel Only
        unsigned char ReservedBitsA;
        unsigned char ExtendedModel;
        unsigned char ExtendedFamily;
        unsigned char ReservedBitsB;

        // EBX
        unsigned char BrandIndex;
        unsigned char CLflushCacheLineSize;
        unsigned char logicalProcessors;
        unsigned char initialApicID;


        // ecx
        unsigned char  SSE3Instructions;
        unsigned char  ReservedBitsAAB;
        unsigned char  MonitorMWait;
        unsigned char cplQualifiedDebugStore;// Intel Only
        unsigned char VirtualmachineExtensions; // Intel Only
        unsigned char saferModeExtensions; // Intel Only
        unsigned char enhancedIntelSpeedstepExtensions;// Intel Only
        unsigned char thermalMonitor;// Intel Only
        unsigned char supplementalSSE3;
        unsigned char L1ContextID; // Intel Only
        unsigned char ReservedBitsAAC;
        unsigned char FMAExtensions;// Intel Only
        unsigned char  CompareExchange16XSupport;// Intel Only
        unsigned char  xTPRUpdateControl;
        unsigned char  performanceDebugCapabilityMSR;
        unsigned char  ReservedBitsAAF;
        unsigned char DirectCacheAccess; // Intel Only
        unsigned char SSE4x1Extensions;
        unsigned char SSE4x2Extensions;
        unsigned char x2APICSupport; // Intel Only
        unsigned char MOVBEInstructionSupport; // Intel Only
        unsigned char POPCNTInstructionSupport;
        unsigned char ReservedBitsAAE;
        unsigned char AESInstructionSupport; // Intel Only
        unsigned char XSAVEInstructionSupport; // Intel Only
        unsigned char OSXSAVEInstructionSupport; // Intel Only
        unsigned char AdvancedVectorExtensions;// Intel Only
        unsigned char ReservedBitsAAA;

        // EDX
        unsigned char  FPU;// -x87 FPU on chip : % d\n", cpuinfo[3] >> 0 & 1;
        unsigned char  VME;//Virtual-8086 mode enhancement: %d\n", cpuinfo[3] >> 1 & 1;
        unsigned char  DE;//Debugging extensions: %d\n", cpuinfo[3] >> 2 & 1;
        unsigned char  PSE;//Page size extensions: %d\n", cpuinfo[3] >> 3 & 1;
        unsigned char  TSC;//Time stamp counter: %d\n", cpuinfo[3] >> 4 & 1;
        unsigned char  MSR;//RDMSR and WRMSR support: %d\n", cpuinfo[3] >> 5 & 1;
        unsigned char  PAE;//Physical address extensions: %d\n", cpuinfo[3] >> 6 & 1;
        unsigned char  MCE;//Machine check exception: %d\n", cpuinfo[3] >> 7 & 1;
        unsigned char  CX8;//CMPXCHG8B instruction: %d\n", cpuinfo[3] >> 8 & 1;
        unsigned char  APIC;//APIC on chip: %d\n", cpuinfo[3] >> 9 & 1;
        unsigned char  nAAaAAAAA;//Reserved: %d\n", cpuinfo[3] >> 10 & 1;
        unsigned char  SEP;//SYSENTER and SYSEXIT: %d\n", cpuinfo[3] >> 11 & 1;
        unsigned char  MTRR;//Memory type range registers: %d\n", cpuinfo[3] >> 12 & 1;
        unsigned char  PGE;//PTE global bit: %d\n", cpuinfo[3] >> 13 & 1;
        unsigned char  MCA;//Machine check architecture: %d\n", cpuinfo[3] >> 14 & 1;
        unsigned char  CMOV;//Conditional move/compare instruction: %d\n", cpuinfo[3] >> 15 & 1;
        unsigned char  PAT;//Page Attribute Table: %d\n", cpuinfo[3] >> 16 & 1;
        unsigned char  PSEE;//-36 - 36-bit page size extension: %d\n", cpuinfo[3] >> 17 & 1;
        unsigned char  PSN;// Processor serial number: %d\n", cpuinfo[3] >> 18 & 1;
        unsigned char  CLFSH;// CFLUSH instruction: %d\n", cpuinfo[3] >> 19 & 1;
        unsigned char  nAA;// -/ a Reserved : % d\n", cpuinfo[3] >> 20 & 1;
        unsigned char  DS;// Debug store: %d\n", cpuinfo[3] >> 21 & 1;
        unsigned char  ACPI;// Thermal monitor and clock control: %d\n", cpuinfo[3] >> 22 & 1;
        unsigned char  MMX;// MMX technology: %d\n", cpuinfo[3] >> 23 & 1;
        unsigned char  FXSR;// FXSAVE/FXRSTOR: %d\n", cpuinfo[3] >> 24 & 1;
        unsigned char  SSE;// SSE extensions: %d\n", cpuinfo[3] >> 25 & 1;
        unsigned char  SSE2;// SSE2 extensions: %d\n", cpuinfo[3] >> 26 & 1;
        unsigned char  SS;// Self snoop: %d\n", cpuinfo[3] >> 27 & 1;
        unsigned char  HTT;// Multithreading: %d\n", cpuinfo[3] >> 28 & 1;
        unsigned char  TM;// Thermal monitor: %d\n", cpuinfo[3] >> 29 & 1;
        unsigned char  nAAAABB;// Reserved: %d\n", cpuinfo[3] >> 30 & 1;
        unsigned char  PBE;// Pending break enable: %d\n", cpuinfo[3] >> 31 & 1;

	}
	Processor;

	PXPublic void PXProcessorFetchInfo(Processor* const processor);

	PXPublic unsigned int PXProcessorFrequencyCurrent();
	PXPublic unsigned int PXProcessorTimeReal();



#ifdef __cplusplus
}
#endif

#endif
