#pragma once

namespace BF
{
	enum class KeyBoardKey
	{
		KeyUnknown,

		KeySpace,
		KeyAPOSTROPHE,  /* ' */
		KeyComma,  /* , */
		KeyMinus,  /* - */
		KeyPeriod,  /* . */
		KeySlash,  /* / */
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
		KeySemicolon,  /* ; */
		KeyEqual,  /* = */
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
		KeyLEFT_BRACKET,  /* [ */
		KeyBACKSLASH,  /* \ */
		KeyRIGHT_BRACKET,  /* ] */
		KeyGRAVE_ACCENT,  /* ` */
		KeyWORLD_1, /* non-US #1 */
		KeyWORLD_2, /* non-US #2 */

		KeyESCAPE,
		KeyENTER,
		KeyTAB,
		KeyBACKSPACE,
		KeyINSERT,
		KeyDELETE,
		KeyRIGHT,
		KeyLEFT,
		KeyDOWN,
		KeyUP,
		KeyPAGE_UP,
		KeyPAGE_DOWN,
		KeyHOME,
		KeyEND,
		KeyCAPS_LOCK,
		KeySCROLL_LOCK,
		KeyNUM_LOCK,
		KeyPRINT_SCREEN,
		KeyPAUSE,
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
		KeyF25,
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
		KeyPadDECIMAL,
		KeyPadDIVIDE,
		KeyPadMULTIPLY,
		KeyPadSUBTRACT,
		KeyPadADD,
		KeyPadENTER,
		KeyPadEQUAL,

		KeyShiftLeft,
		KeyShiftRight,

		KeyCONTROLLEFT,
		KeyALTLEFT,
		KeySUPERLEFT,
	
		KeyCONTROLRIGHT,
		KeyALTRIGHT,
		KeySUPERRIGHT,
		KeyMENU
	};

	KeyBoardKey ConvertKeyBoardKey(wchar_t character);
}