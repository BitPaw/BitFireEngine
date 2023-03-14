#ifndef KeyBoardKeyInclude
#define KeyBoardKeyInclude

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef enum VirtualKey_
	{
		KeyInvalid,
		KeyUnknown,
	
		// Command
		
		KeySpace,

		KeyMinus,  /* - */
		KeySlash,  /* / */
		KeyEscape,
		KeyEnter,
		KeyTab,
		KeyBackspace,
		KeyInsert,
		KeyDelete,
		KeyRight,
		KeyLeft,
		KeyDown,
		KeyUp,
		KeyPageUp,
		KeyPageDown,
		KeyHome,
		KeyEnd,
		KeyCapsLock,
		KeyScrollLock,
		KeyNumLock,
		KeyPrintScreen,
		KeyPause,


		// Numbers
		Key0,
		Key1,
		Key2,
		Key3,
		Key4,
		Key5,
		Key6,
		Key7,
		Key8,
		Key9,
		KeyPad0,
		KeyPad1,
		KeyPad2,
		KeyPad3,
		KeyPad4,
		KeyPad5,
		KeyPad6,
		KeyPad7,
		KeyPad8,
		KeyPad9,
		KeyPadDecimal,
		KeyPadDivide,
		KeyPadMultiply,
		KeyPadSubtract,
		KeyPadAdd,
		KeyPadEnter,
		KeyPadEqual,



		KeySemicolon,  /* ; */
		KeyEqual,  /* = */

		// Letters

		KeyA,
		KeyB,
		KeyC,
		KeyD,
		KeyE,
		KeyF,
		KeyG,
		KeyH,
		KeyI,
		KeyJ,
		KeyK,
		KeyL,
		KeyM,
		KeyN,
		KeyO,
		KeyP,
		KeyQ,
		KeyR,
		KeyS,
		KeyT,
		KeyU,
		KeyV,
		KeyW,
		KeyX,
		KeyY,
		KeyZ,

		KeyASmal,
		KeyBSmal,
		KeyCSmal,
		KeyDSmal,
		KeyESmal,
		KeyFSmal,
		KeyGSmal,
		KeyHSmal,
		KeyISmal,
		KeyJSmal,
		KeyKSmal,
		KeyLSmal,
		KeyMSmal,
		KeyNSmal,
		KeyOSmal,
		KeyPSmal,
		KeyQSmal,
		KeyRSmal,
		KeySSmal,
		KeyTSmal,
		KeyUSmal,
		KeyVSmal,
		KeyWSmal,
		KeyXSmal,
		KeyYSmal,
		KeyZSmal,
			KeyApostrophe,  /* ' */
			KeyComma,  /* , */
			KeyPeriod,  /* . */


		KeyBrackedLeft,  /* [ */
		KeyBackSlash,  /* \ */
		KeyBrackedRight,  /* ] */
		KeyGraveAccent,  /* ` */
		KeyWorld1, /* non-US #1 */
		KeyWorld2, /* non-US #2 */



		// Function
			KeyF1,
			KeyF2,
			KeyF3,
			KeyF4,
			KeyF5,
			KeyF6,
			KeyF7,
			KeyF8,
			KeyF9,
			KeyF10,
			KeyF11,
			KeyF12,
			KeyF13,
			KeyF14,
			KeyF15,
			KeyF16,
			KeyF17,
			KeyF18,
			KeyF19,
			KeyF20,
			KeyF21,
			KeyF22,
			KeyF23,
			KeyF24,
		

		KeyShiftLeft,
		KeyShiftRight,

		KeyControlLeft,
		KeyAltLeft,
		KeySuperLeft,

		KeyControlRight,
		KeyAltRight,
		KeySuperRight,
		KeyMenu
	}
	VirtualKey;

	PXPublic VirtualKey ConvertToVirtualKey(const char character);

#ifdef __cplusplus
}
#endif

#endif