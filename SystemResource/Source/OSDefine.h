#ifndef OSWindows
	#if defined(_WIN32) || defined(_WIN64)
		#define OSWindows
	#endif
#endif

#ifndef OSUnix
	#if defined(linux) || defined(__APPLE__)
		#define OSUnix
	#endif
#endif