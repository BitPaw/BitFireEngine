#include "VirtualKey.h"

#include <OS/OSVersion.h>

#if defined(OSUnix)
#define ButtonBackSpace  0x08
#define ButtonTab  0x09
#define ButtonReturn  0x0D

#define ButtonKeyPad0  0x60 //Numeric keypad 0 key
#define ButtonKeyPad1  0x61 //Numeric keypad 1 key
#define ButtonKeyPad2 0x62// Numeric keypad 2 key
#define ButtonKeyPad3  0x63 //Numeric keypad 3 key
#define ButtonKeyPad4  0x64 //Numeric keypad 4 key
#define ButtonKeyPad5  0x65 //Numeric keypad 5 key
#define ButtonKeyPad6  0x66 //Numeric keypad 6 key
#define ButtonKeyPad7  0x67 //Numeric keypad 7 key
#define ButtonKeyPad8  0x68 //Numeric keypad 8 key
#define ButtonKeyPad9  0x69 //Numeric keypad 9 key

#define ButtonShiftLeft  0xA0
#define ButtonShiftRight  0xA1
#define ButtonControlLeft 0xA2
#define ButtonControlRight    0xA3
#define ButtonMenuLeft  0xA4
#define ButtonMenuRight  0xA5


#elif defined(OSWindows)
#include <Windows.h>
#include <WinUser.h>
#endif

extern VirtualKey ConvertToVirtualKey(const char character)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	switch(character)
	{
		/*
		case VK_LBUTTON:
		case VK_RBUTTON:
		case VK_CANCEL:
		case VK_MBUTTON:    // NOT contiguous with L & RBUTTON

#if(_WIN32_WINNT >= 0x0500)
		case VK_XBUTTON1:    // NOT contiguous with L & RBUTTON
		case VK_XBUTTON2:    // NOT contiguous with L & RBUTTON
#endif // _WIN32_WINNT >= 0x0500


		  // 0x07 : reserved



		case VK_BACK:
		case VK_TAB: return KeyTab;


			// 0x0A - 0x0B : reserved


		case VK_CLEAR:
		case VK_RETURN:

			// 0x0E - 0x0F : unassigned

		case VK_SHIFT:
		case VK_CONTROL:
		case VK_MENU:
		case VK_PAUSE:
		case VK_CAPITAL:

		case VK_KANA:
		case VK_HANGEUL:  // old name - should be here for compatibility
		case VK_HANGUL:
		case VK_IME_ON:
		case VK_JUNJA:
		case VK_FINAL:
		case VK_HANJA:
		case VK_KANJI:
		case VK_IME_OFF:
		*/

		case VK_ESCAPE: return KeyEscape;
			/*

		case VK_CONVERT:
		case VK_NONCONVERT:
		case VK_ACCEPT:
		case VK_MODECHANGE:

		case VK_SPACE:
		case VK_PRIOR:
		case VK_NEXT:
		case VK_END:
		case VK_HOME:
		case VK_LEFT:
		case VK_UP:
		case VK_RIGHT:
		case VK_DOWN:
		case VK_SELECT:
		case VK_PRINT:
		case VK_EXECUTE:
		case VK_SNAPSHOT:
		case VK_INSERT:
		case VK_DELETE:
		case VK_HELP:
		*/

		// VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)

		case 0x30: return Key0;
		case 0x31: return Key1;
		case 0x32: return Key2;
		case 0x33: return Key3;
		case 0x34: return Key4;
		case 0x35: return Key5;
		case 0x36: return Key6;
		case 0x37: return Key7;
		case 0x38: return Key8;
		case 0x39: return Key9;

			// 0x3A - 0x40 : unassigned

			// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)

		case 0x41: return KeyA;
		case 0x42: return KeyB;
		case 0x43: return KeyC;
		case 0x44: return KeyD;
		case 0x45: return KeyE;
		case 0x46: return KeyF;
		case 0x47: return KeyG;
		case 0x48: return KeyH;
		case 0x49: return KeyI;
		case 0x4A: return KeyJ;
		case 0x4B: return KeyK;
		case 0x4C: return KeyL;
		case 0x4D: return KeyM;
		case 0x4E: return KeyN;
		case 0x4F: return KeyO;
		case 0x50: return KeyP;
		case 0x51: return KeyQ;
		case 0x52: return KeyR;
		case 0x53: return KeyS;
		case 0x54: return KeyT;
		case 0x55: return KeyU;
		case 0x56: return KeyV;
		case 0x57: return KeyW;
		case 0x58: return KeyX;
		case 0x59: return KeyY;
		case 0x5A: return KeyZ;

			//case VK_LWIN:
			//case VK_RWIN:
			//case VK_APPS:


			// 0x5E : reserved			 

			//case VK_SLEEP:

		case VK_NUMPAD0:return KeyPad0;
		case VK_NUMPAD1:return KeyPad1;
		case VK_NUMPAD2:return KeyPad2;
		case VK_NUMPAD3:return KeyPad3;
		case VK_NUMPAD4:return KeyPad4;
		case VK_NUMPAD5:return KeyPad5;
		case VK_NUMPAD6:return KeyPad6;
		case VK_NUMPAD7:return KeyPad7;
		case VK_NUMPAD8:return KeyPad8;
		case VK_NUMPAD9:return KeyPad9;
		case VK_MULTIPLY:return KeyPadMultiply;
		case VK_ADD: return KeyPadAdd;
			//case VK_SEPARATOR: return 
		case VK_SUBTRACT: return KeyPadSubtract;
		case VK_DECIMAL: return KeyPadDecimal;
		case VK_DIVIDE: return KeyPadDivide;
		case VK_F1: return KeyF1;
		case VK_F2: return KeyF2;
		case VK_F3: return KeyF3;
		case VK_F4: return KeyF4;
		case VK_F5: return KeyF5;
		case VK_F6: return KeyF6;
		case VK_F7: return KeyF7;
		case VK_F8: return KeyF8;
		case VK_F9: return KeyF9;
		case VK_F10: return KeyF10;
		case VK_F11: return KeyF11;
		case VK_F12: return KeyF12;
		case VK_F13: return KeyF13;
		case VK_F14: return KeyF14;
		case VK_F15: return KeyF15;
		case VK_F16: return KeyF16;
		case VK_F17: return KeyF17;
		case VK_F18: return KeyF18;
		case VK_F19: return KeyF19;
		case VK_F20: return KeyF20;
		case VK_F21: return KeyF21;
		case VK_F22: return KeyF22;
		case VK_F23: return KeyF23;
		case VK_F24: return KeyF24;

#if(_WIN32_WINNT >= 0x0604)

			/*
			 * 0x88 - 0x8F : UI navigation
			 */

			 //case VK_NAVIGATION_VIEW: // reserved
			 //case VK_NAVIGATION_MENU: // reserved
			 //case VK_NAVIGATION_UP: // reserved
			 //case VK_NAVIGATION_DOWN: // reserved
			 //case VK_NAVIGATION_LEFT: // reserved
			 //case VK_NAVIGATION_RIGHT: // reserved
			 //case VK_NAVIGATION_ACCEPT: // reserved
			 //case VK_NAVIGATION_CANCEL: // reserved

#endif /* _WIN32_WINNT >= 0x0604 */

		//case VK_NUMLOCK:
		//case VK_SCROLL:

			/*
			 * NEC PC-9800 kbd definitions
			 */
			 //case VK_OEM_NEC_EQUAL:   // '=' key on numpad

						/*
						 * Fujitsu/OASYS kbd definitions
						 */
						 //case VK_OEM_FJ_JISHO:   // 'Dictionary' key
		//case VK_OEM_FJ_MASSHOU:   // 'Unregister word' key
		//case VK_OEM_FJ_TOUROKU:   // 'Register word' key
		//case VK_OEM_FJ_LOYA:   // 'Left OYAYUBI' key
	//	case VK_OEM_FJ_ROYA:   // 'Right OYAYUBI' key

						 /*
						  * 0x97 - 0x9F : unassigned
						  */

						  /*
						   * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
						   * Used only as parameters to GetAsyncKeyState() and GetKeyState().
						   * No other API or message will distinguish left and right keys in this way.
						   */
						   //	case VK_LSHIFT:
	//	case VK_RSHIFT:
			//	case VK_LCONTROL:
	//	case VK_RCONTROL:
	//	case VK_LMENU:
	//	case VK_RMENU:
			/*

#if(_WIN32_WINNT >= 0x0500)
		//case VK_BROWSER_BACK:
		//case VK_BROWSER_FORWARD:
	//	case VK_BROWSER_REFRESH:
		case VK_BROWSER_STOP:
		case VK_BROWSER_SEARCH:
		case VK_BROWSER_FAVORITES:
		case VK_BROWSER_HOME:

		case VK_VOLUME_MUTE:
		case VK_VOLUME_DOWN:
		case VK_VOLUME_UP:
		case VK_MEDIA_NEXT_TRACK:
		case VK_MEDIA_PREV_TRACK:
		case VK_MEDIA_STOP:
		case VK_MEDIA_PLAY_PAUSE:
		case VK_LAUNCH_MAIL:
		case VK_LAUNCH_MEDIA_SELECT:
		case VK_LAUNCH_APP1:
		case VK_LAUNCH_APP2:

#endif // _WIN32_WINNT >= 0x0500


			 // 0xB8 - 0xB9 : reserved


		case VK_OEM_1:   // ';:' for US
		case VK_OEM_PLUS:   // '+' any country
		case VK_OEM_COMMA:   // ',' any country
		case VK_OEM_MINUS:   // '-' any country
		case VK_OEM_PERIOD:   // '.' any country
		case VK_OEM_2:   // '/?' for US
		case VK_OEM_3:   // '`~' for US


							 // 0xC1 - 0xC2 : reserved


#if(_WIN32_WINNT >= 0x0604)


							  // 0xC3 - 0xDA : Gamepad input


		case VK_GAMEPAD_A: // reserved
		case VK_GAMEPAD_B: // reserved
		case VK_GAMEPAD_X: // reserved
		case VK_GAMEPAD_Y: // reserved
		case VK_GAMEPAD_RIGHT_SHOULDER: // reserved
		case VK_GAMEPAD_LEFT_SHOULDER: // reserved
		case VK_GAMEPAD_LEFT_TRIGGER: // reserved
		case VK_GAMEPAD_RIGHT_TRIGGER: // reserved
		case VK_GAMEPAD_DPAD_UP: // reserved
		case VK_GAMEPAD_DPAD_DOWN: // reserved
		case VK_GAMEPAD_DPAD_LEFT: // reserved
		case VK_GAMEPAD_DPAD_RIGHT: // reserved
		case VK_GAMEPAD_MENU: // reserved
		case VK_GAMEPAD_VIEW: // reserved
		case VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON: // reserved
		case VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON: // reserved
		case VK_GAMEPAD_LEFT_THUMBSTICK_UP: // reserved
		case VK_GAMEPAD_LEFT_THUMBSTICK_DOWN: // reserved
		case VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT: // reserved
		case VK_GAMEPAD_LEFT_THUMBSTICK_LEFT: // reserved
		case VK_GAMEPAD_RIGHT_THUMBSTICK_UP: // reserved
		case VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN: // reserved
		case VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT: // reserved
		case VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT: // reserved

#endif // _WIN32_WINNT >= 0x0604


		case VK_OEM_4:  //  '[{' for US
		case VK_OEM_5:  //  '\|' for US
		case VK_OEM_6:  //  ']}' for US
		case VK_OEM_7:  //  ''"' for US
		case VK_OEM_8:


			 // 0xE0 : reserved



			  //Various extended or enhanced keyboards

		case VK_OEM_AX:  //  'AX' key on Japanese AX kbd
		case VK_OEM_102:  //  "<>" or "\|" on RT 102-key kbd.
		case VK_ICO_HELP:  //  Help key on ICO
		case VK_ICO_00:  //  00 key on ICO

#if(WINVER >= 0x0400)
		case VK_PROCESSKEY:
#endif // WINVER >= 0x0400

		case VK_ICO_CLEAR:


#if(_WIN32_WINNT >= 0x0500)
		case VK_PACKET:
#endif // _WIN32_WINNT >= 0x0500


			 // 0xE8 : unassigned



			  // Nokia/Ericsson definitions

		case VK_OEM_RESET:
		case VK_OEM_JUMP:
		case VK_OEM_PA1:
		case VK_OEM_PA2:
		case VK_OEM_PA3:
		case VK_OEM_WSCTRL:
		case VK_OEM_CUSEL:
		case VK_OEM_ATTN:
		case VK_OEM_FINISH:
		case VK_OEM_COPY:
		case VK_OEM_AUTO:
		case VK_OEM_ENLW:
		case VK_OEM_BACKTAB:

		case VK_ATTN:
		case VK_CRSEL:
		case VK_EXSEL:
		case VK_EREOF:
		case VK_PLAY:
		case VK_ZOOM:
		case VK_NONAME:
		case VK_PA1:
		case VK_OEM_CLEAR:*/


		case 0xFF: return KeyInvalid;
		default: return KeyUnknown;
	}

#endif
}