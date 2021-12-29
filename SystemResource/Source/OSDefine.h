#ifndef OSWindows	
	#if defined(_WIN32) || defined(_WIN64)
		#define OSWindows
		#include <SdkDdkVer.h>

		typedef struct IUnknown IUnknown;

		#if WINVER == _WIN32_WINNT_WINXP
			#define OSWindowsXP
		#elif WINVER == _WIN32_WINNT_WIN7
			#define OSWindows7
		#elif WINVER == _WIN32_WINNT_WIN10
			#define OSWindows10
		#endif
	#endif	
#endif

#ifndef OSUnix
	#if defined(linux) || defined(__APPLE__)
		#define OSUnix
	#endif
#endif