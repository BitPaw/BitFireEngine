#include "CursorIcon.h"

#include <OS/OSDefine.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <winuser.rh>
#define CursorIconNormal OCR_NORMAL
#define CursorIconIBeam OCR_IBEAM           
#define CursorIconWait OCR_WAIT            
#define CursorIconCross OCR_CROSS           
#define CursorIconUp OCR_UP              
#define CursorIconSize OCR_SIZE               // OBSOLETE: use OCR_SIZEALL
#define CursorIconIcon OCR_ICON               // OBSOLETE: use OCR_NORMAL
#define CursorIconResizeClockwiseCounter OCR_SIZENWSE        
#define CursorIconResizeClockwise OCR_SIZENESW        
#define CursorIconResizeHorizontal OCR_SIZEWE          
#define CursorIconResizeVertical OCR_SIZENS          
#define CursorIconResizeAll OCR_SIZEALL         
#define CursorIconCursor OCR_ICOCUR             // OBSOLETE: use OIC_WINLOGO
#define CursorIconNoAllowed OCR_NO   

#if defined(WindowsAtleast2000)
	#define CursorIconHand OCR_HAND
#else
	#define CursorIconHand 32649
#endif

#if defined(WindowsAtleastNT)
	#define CursorIconAppStarting OCR_APPSTARTING
#else 
	#defined CursorIconAppStarting 32650
#endif

#endif


unsigned int BF::ToCursorIcon(const CursorIcon cursorIcon)
{
	switch (cursorIcon)
	{
		case BF::CursorIcon::Invalid:
			return -1;

		case BF::CursorIcon::Normal:
			return CursorIconNormal;

		case BF::CursorIcon::IBeam:
			return CursorIconIBeam;

		case BF::CursorIcon::Wait:
			return CursorIconWait;

		case BF::CursorIcon::Cross:
			return CursorIconCross;

		case BF::CursorIcon::Up:
			return CursorIconUp;

		case BF::CursorIcon::Hand:
			return CursorIconHand;

		case BF::CursorIcon::NotAllowed:
			return CursorIconNoAllowed;

		case BF::CursorIcon::AppStarting:
			return CursorIconAppStarting;

		case BF::CursorIcon::ResizeHorizontal:
			return CursorIconResizeHorizontal;

		case BF::CursorIcon::ResizeVertical:
			return CursorIconResizeVertical;

		case BF::CursorIcon::ResizeClockwise:
			return CursorIconResizeClockwise;

		case BF::CursorIcon::ResizeClockwiseCounter:
			return CursorIconResizeClockwiseCounter;

		case BF::CursorIcon::ResizeAll:
			return CursorIconResizeAll;
	}
}