#ifndef OSWindows	
	#if defined(_WIN32)
		#define System32Bit
	#endif

	#if defined(_WIN64)
		#define System64Bit
	#endif

	#if defined(_WIN32) || defined(_WIN64)
		#define OSWindows
		#include <SdkDdkVer.h>

		typedef struct IUnknown IUnknown;

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
			#define WindowsAtleastNT
		#endif

		#if Version_Windows >= Version_Windows_2000
			#define WindowsAtleast2000
		#endif
	
		#if Version_Windows >= Version_Windows_10
			#define WindowsAtleast10
		#endif
	
		#if Version_Windows == Version_Windows_XP
			#define OSWindowsXP
		#elif Version_Windows == Version_Windows_7
			#define OSWindows7
		#elif Version_Windows == Version_Windows_10
			#define OSWindows10
		#endif
	#endif	
#endif

#ifndef OSUnix
	#if defined(linux) || defined(__APPLE__)
		#define OSUnix
	#endif
#endif