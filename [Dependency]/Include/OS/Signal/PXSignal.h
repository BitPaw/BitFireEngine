#ifndef OSSignalINCLUDE
#define OSSignalINCLUDE

#include <OS/System/OSVersion.h>
#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /*

#if OSUnix
   // void OSSystemSignalCallBack(const int signalID);
#elif OSWindows
    //void __CRTDECL OSSystemSignalCallBack(const int signalID);
#endif*/

    PXPublic PXBool PXSignalCallBackRegister();

#ifdef __cplusplus
}
#endif

#endif
