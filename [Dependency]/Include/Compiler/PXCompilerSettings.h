#ifndef PXCompilerSettingsINCLUDE
#define PXCompilerSettingsINCLUDE

#include <OS/System/OSVersion.h>


#define _PX_FILEPATH_ __FILE__

#if OSUnix
#define _PX_FILENAME_ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#elif OSWindows
#define _PX_FILENAME_ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

#define _PX_FUNCTION_ __FUNCTION__
#define _PX_LINE_ __LINE__

#if defined(_DEBUG)
#define _PX_DEBUG 1u
#else 
#define _PX_DEBUG 0u
#endif

#endif