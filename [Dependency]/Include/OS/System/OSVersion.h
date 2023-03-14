#ifndef OSVersionINCLUDE
#define OSVersionINCLUDE

/*
#define OSUnixCheck (defined(unix) || defined(__unix) || defined(__unix__))
#define OSLinuxCheck (defined(linux) || defined(__linux) || defined(__linux__))
#define OSAppleCheck (defined(__APPLE__) || defined(__MACH__))
#define OSAndroidCheck (defined(__ANDROID__))

#define OSWindows64BCheck (defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__))
#define OSWindows32BCheck !OSWindows64B && (defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__))

#define OSWindows (OSWindows64B || OSWindows32B)

*/

//---<Detect OS version>----------------------------------------------------
#if defined(unix) || defined(__unix) || defined(__unix__)
    #ifndef OSUnix
        #define OSUnix 1u
    #endif
#else
    #ifndef OSUnix
        #define OSUnix 0u
    #endif
#endif
//-----------------------------------------------------------------------------
#if defined(linux) || defined(__linux) || defined(__linux__)
    #ifndef OSLinux
        #define OSLinux 1u
    #endif
#else
    #ifndef OSLinux
        #define OSLinux 0u
    #endif
#endif
//-----------------------------------------------------------------------------
#if defined(__APPLE__) || defined(__MACH__)
    #ifndef OSApple
        #define OSApple 1u
    #endif
#else
    #ifndef OSApple
        #define OSApple 0u
    #endif
#endif
//-----------------------------------------------------------------------------
#if defined(__ANDROID__)
    #ifndef OSAndroid
        #define OSAndroid 1u
    #endif
#else
    #ifndef OSAndroid
        #define OSAndroid 0u
    #endif
#endif
//-----------------------------------------------------------------------------
#if defined(__x86_64__ ) || defined(__ppc64__) // Linux 64-Bit
#ifndef OSLinux64B
#define OSLinux64B 1u
#endif

#ifndef OSLinux32B
#define OSLinux32B 0u
#endif
#elif  defined(__x86__ ) || defined(__ppc86__)
#ifndef OSLinux64B
#define OSLinux64B 1u
#endif

#ifndef OSLinux64B
#define OSLinux64B 0u
#endif
#else
#define OSLinux64B 0u
#define OSLinux32B 0u
#endif



#if defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)
    #ifndef OSWindows64B
        #define OSWindows64B 1u
    #endif

    #ifndef OSWindows32B
        #define OSWindows32B 0u
    #endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
    #ifndef OSWindows64B
        #define OSWindows64B 0u // Cant be 64-Bit, as this is 32-Bit
    #endif

    #ifndef OSWindows32B
        #define OSWindows32B 1u
    #endif
#else
#define OSWindows64B 0u
#define OSWindows32B 0u
#endif

#if (OSWindows64B || OSWindows32B)
    #ifndef OSWindows
        #define OSWindows 1u
    #endif
#else
    #ifndef OSWindows
        #define OSWindows 0u
    #endif
#endif

// Bit
#if (OSWindows64B || OSLinux64B)
    #ifndef OS32Bit
        #define OS32Bit 0u
    #endif
    #ifndef OS64Bit
        #define OS64Bit 1u
    #endif
#elif (OSWindows32B || OSLinux32B)
    #ifndef OS32Bit
        #define OS32Bit 1u
    #endif
    #ifndef OS64Bit
        #define OS64Bit 0u
    #endif
#endif
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
#define OSVersionOutput 0u

#if OSVersionOutput
#if OSUnix
    #pragma message("[PX] Operating system: UNIX")
#elif OSLinux
    #pragma message("[PX] Operating system: Linux")
#elif OSApple
    #pragma message("[PX] Operating system: Apple")
#elif OSAndroid
    #pragma message("[PX] Operating system: Android")
#elif OSWindows64B
    #pragma message("[PX] Operating system: Windows 64-Bit detected")
#elif OSWindows32B
    #pragma message("[PX] Operating system: Windows 32-Bit detected")
#else
    #error [PX] Operating system could not be detected!
#endif
#endif
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
#if OSWindows // Detect which windows version is used

    #include <Windows.h>
    #include <SdkDdkVer.h>

    #define Version_Windows WINVER

    #define Version_Windows_NT 0x0400
    #define Version_Windows_2000 0x0500
    #define Version_Windows_XP 0x0501
    #define Version_Windows_Server_2003 0x0502
    #define Version_Windows_Vista 0x0600
    #define Version_Windows_Server_2008 0x0600
    #define Version_Windows_7 0x0601
    #define Version_Windows_8 0x0602
    #define Version_Windows_8_1 0x0603
    #define Version_Windows_10 0x0A00

    #if Version_Windows >= Version_Windows_NT
        #define WindowsAtleastNT 1u
    #else
        #define WindowsAtleastNT 0u
    #endif

    #if Version_Windows >= Version_Windows_2000
        #define WindowsAtleast2000 1u
    #else
        #define WindowsAtleast2000 0u
    #endif

    #if Version_Windows >= Version_Windows_XP
        #define WindowsAtleastXP 1u
    #else
        #define WindowsAtleastXP 0u
    #endif

    #if Version_Windows >= Version_Windows_Vista
        #define WindowsAtleastVista 1u
    #else
        #define WindowsAtleastVista 0u
    #endif

    #if Version_Windows >= Version_Windows_7
        #define WindowsAtleast7 1u
    #else
        #define WindowsAtleast7 0u
    #endif

    #if Version_Windows >= Version_Windows_8
        #define WindowsAtleast8 1u
    #else
        #define WindowsAtleast8 0u
    #endif

    #if Version_Windows >= Version_Windows_10
        #define WindowsAtleast10 1u
    #else
        #define WindowsAtleast10 0u
    #endif

    #if Version_Windows == Version_Windows_XP
        #define OSWindowsXP 1u
        typedef struct IUnknown IUnknown;
    #else
        #define OSWindowsXP 0u
    #endif

    #if Version_Windows == Version_Windows_7
        #define OSWindows7 1u
    #else
        #define OSWindows7 0u
    #endif

    #if Version_Windows == Version_Windows_10
        #define OSWindows10 1u
    #else
        #define OSWindows10 0u
    #endif
//-----------------------------------------------------------------------------
#endif

#endif
