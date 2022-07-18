#include "KeyBoardKey.h"

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

#define ButtonBackSpace VK_BACK // 0x08
#define ButtonTab VK_TAB // 0x09
#define ButtonReturn VK_RETURN // 0x0D

#define ButtonKeyPad0 VK_NUMPAD0 // 0x60 Numeric keypad 0 key
#define ButtonKeyPad1 VK_NUMPAD1 // 0x61 Numeric keypad 1 key
#define ButtonKeyPad2 VK_NUMPAD2 // 0x62 Numeric keypad 2 key
#define ButtonKeyPad3 VK_NUMPAD3 // 0x63 Numeric keypad 3 key
#define ButtonKeyPad4 VK_NUMPAD4 // 0x64 Numeric keypad 4 key
#define ButtonKeyPad5 VK_NUMPAD5 // 0x65 Numeric keypad 5 key
#define ButtonKeyPad6 VK_NUMPAD6 // 0x66 Numeric keypad 6 key
#define ButtonKeyPad7 VK_NUMPAD7 // 0x67 Numeric keypad 7 key
#define ButtonKeyPad8 VK_NUMPAD8 // 0x68 Numeric keypad 8 key
#define ButtonKeyPad9 VK_NUMPAD9 // 0x69 Numeric keypad 9 key

#define ButtonShiftLeft VK_SHIFT// VK_LSHIFT // 0xA0
#define ButtonShiftRight VK_RSHIFT // 0xA1
#define ButtonControlLeft VK_LCONTROL    // 0xA2
#define ButtonControlRight VK_RCONTROL    //   0xA3
#define ButtonMenuLeft VK_LMENU         // 0xA4
#define ButtonMenuRight VK_RMENU         // 0xA5


// unused
/*
VK_LBUTTON 	0x01 	//Left mouse button
VK_RBUTTON 	0x02 	Right mouse button
VK_CANCEL 	0x03 	Control - break processing
VK_MBUTTON 	0x04 	Middle mouse button(three - button mouse)
VK_XBUTTON1 	0x05 	X1 mouse button
VK_XBUTTON2 	0x06 	X2 mouse button
- 0x07 	Undefined
- 0x0A - 0B 	Reserved
VK_CLEAR 	0x0C 	CLEAR key
- 0x0E - 0F 	Undefined
VK_SHIFT 	0x10 	SHIFT key
* /



VK_MENU 	0x12 	ALT key
VK_PAUSE 	0x13 	PAUSE key
VK_CAPITAL 	0x14 	CAPS LOCK key
VK_KANA 	0x15 	IME Kana mode
VK_HANGUEL 	0x15 	IME Hanguel mode(maintained for compatibility; use VK_HANGUL)
VK_HANGUL 	0x15 	IME Hangul mode
VK_IME_ON 	0x16 	IME On
VK_JUNJA 	0x17 	IME Junja mode
VK_FINAL 	0x18 	IME final mode
VK_HANJA 	0x19 	IME Hanja mode
VK_KANJI 	0x19 	IME Kanji mode
VK_IME_OFF 	0x1A 	IME Off
VK_ESCAPE 	0x1B 	ESC key
VK_CONVERT 	0x1C 	IME convert
VK_NONCONVERT 	0x1D 	IME nonconvert
VK_ACCEPT 	0x1E 	IME accept
VK_MODECHANGE 	0x1F 	IME mode change request
VK_SPACE 	0x20 	SPACEBAR
VK_PRIOR 	0x21 	PAGE UP key
VK_NEXT 	0x22 	PAGE DOWN key
VK_END 	0x23 	END key
VK_HOME 	0x24 	HOME key
VK_LEFT 	0x25 	LEFT ARROW key
VK_UP 	0x26 	UP ARROW key
VK_RIGHT 	0x27 	RIGHT ARROW key
VK_DOWN 	0x28 	DOWN ARROW key
VK_SELECT 	0x29 	SELECT key
VK_PRINT 	0x2A 	PRINT key
VK_EXECUTE 	0x2B 	EXECUTE key
VK_SNAPSHOT 	0x2C 	PRINT SCREEN key
VK_INSERT 	0x2D 	INS key
VK_DELETE 	0x2E 	DEL key
VK_HELP 	0x2F 	HELP key





-0x3A - 40 	Undefined
- 0x5E 	Reserved
- 0x88 - 8F 	Unassigned
0x92 - 96 	OEM specific
- 0x97 - 9F 	Unassigned

VK_LWIN 	0x5B 	Left Windows key(Natural keyboard)
VK_RWIN 	0x5C 	Right Windows key(Natural keyboard)
VK_APPS 	0x5D 	Applications key(Natural keyboard)
VK_SLEEP 	0x5F 	Computer Sleep key

VK_MULTIPLY 	0x6A 	Multiply key
VK_ADD 	0x6B 	Add key
VK_SEPARATOR 	0x6C 	Separator key
VK_SUBTRACT 	0x6D 	Subtract key
VK_DECIMAL 	0x6E 	Decimal key
VK_DIVIDE 	0x6F 	Divide key
VK_NUMLOCK 	0x90 	NUM LOCK key
VK_SCROLL 	0x91 	SCROLL LOCK key
VK_LSHIFT 	0xA0 	Left SHIFT key
VK_RSHIFT 	0xA1 	Right SHIFT key
VK_LCONTROL 	0xA2 	Left CONTROL key
VK_RCONTROL 	0xA3 	Right CONTROL key
VK_LMENU 	0xA4 	Left MENU key
VK_RMENU 	0xA5 	Right MENU key
VK_BROWSER_BACK 	0xA6 	Browser Back key
VK_BROWSER_FORWARD 	0xA7 	Browser Forward key
VK_BROWSER_REFRESH 	0xA8 	Browser Refresh key
VK_BROWSER_STOP 	0xA9 	Browser Stop key
VK_BROWSER_SEARCH 	0xAA 	Browser Search key
VK_BROWSER_FAVORITES 	0xAB 	Browser Favorites key
VK_BROWSER_HOME 	0xAC 	Browser Start and Home key
VK_VOLUME_MUTE 	0xAD 	Volume Mute key
VK_VOLUME_DOWN 	0xAE 	Volume Down key
VK_VOLUME_UP 	0xAF 	Volume Up key
VK_MEDIA_NEXT_TRACK 	0xB0 	Next Track key
VK_MEDIA_PREV_TRACK 	0xB1 	Previous Track key
VK_MEDIA_STOP 	0xB2 	Stop Media key
VK_MEDIA_PLAY_PAUSE 	0xB3 	Play / Pause Media key
VK_LAUNCH_MAIL 	0xB4 	Start Mail key
VK_LAUNCH_MEDIA_SELECT 	0xB5 	Select Media key
VK_LAUNCH_APP1 	0xB6 	Start Application 1 key
VK_LAUNCH_APP2 	0xB7 	Start Application 2 key
- 0xB8 - B9 	Reserved
VK_OEM_1 	0xBA 	Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the ';:' key
VK_OEM_PLUS 	0xBB 	For any country / region, the '+' key
VK_OEM_COMMA 	0xBC 	For any country / region, the ',' key
VK_OEM_MINUS 	0xBD 	For any country / region, the '-' key
VK_OEM_PERIOD 	0xBE 	For any country / region, the '.' key
VK_OEM_2 	0xBF 	Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '/?' key
VK_OEM_3 	0xC0 	Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '`~' key
- 0xC1 - D7 	Reserved
- 0xD8 - DA 	Unassigned
VK_OEM_4 	0xDB 	Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '[{' key
VK_OEM_5 	0xDC 	Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '\|' key
VK_OEM_6 	0xDD 	Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the ']}' key
VK_OEM_7 	0xDE 	Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the 'single-quote/double-quote' key
VK_OEM_8 	0xDF 	Used for miscellaneous characters; it can vary by keyboard.
- 0xE0 	Reserved
0xE1 	OEM specific
VK_OEM_102 	0xE2 	The <> keys on the US standard keyboard, or the \\ | key on the non - US 102 - key keyboard
0xE3 - E4 	OEM specific
VK_PROCESSKEY 	0xE5 	IME PROCESS key
0xE6 	OEM specific
VK_PACKET 	0xE7 	Used to pass Unicode characters as if they were keystrokes.The VK_PACKET key is the low word of a 32 - bit Virtual Key value used for non - keyboard input methods.For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
- 0xE8 	Unassigned
0xE9 - F5 	OEM specific
VK_ATTN 	0xF6 	Attn key
VK_CRSEL 	0xF7 	CrSel key
VK_EXSEL 	0xF8 	ExSel key
VK_EREOF 	0xF9 	Erase EOF key
VK_PLAY 	0xFA 	Play key
VK_ZOOM 	0xFB 	Zoom key
VK_NONAME 	0xFC 	Reserved
VK_PA1 	0xFD 	PA1 key
VK_OEM_CLEAR 	0xFE 	Clear key*/
#endif

KeyBoardKey ConvertKeyBoardKey(const char character)
{
	switch(character)
	{
		case 0x20: return KeySpace;

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
		case 0xAB: return KeyK;
		case 0xAC: return KeyL;
		case 0xAD: return KeyM;
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

		case 0x61: return KeyASmal;
		case 0x62: return KeyBSmal;
		case 0x63: return KeyCSmal;
		case 0x64: return KeyDSmal;
		case 0x65: return KeyESmal;
		case 0x66: return KeyFSmal;
		case 0x67: return KeyGSmal;
		case 0x68: return KeyHSmal;
		case 0x69: return KeyISmal;
		case 0x6A: return KeyJSmal;
		case 0x6B: return KeyKSmal;
		case 0x6C: return KeyLSmal;
		case 0x6D: return KeyMSmal;
		case 0x6E: return KeyNSmal;
		case 0x6F: return KeyOSmal;
		case 0x70: return KeyPSmal;
		case 0x71: return KeyQSmal;
		case 0x72: return KeyRSmal;
		case 0x73: return KeySSmal;
		case 0x74: return KeyTSmal;
		case 0x75: return KeyUSmal;
		case 0x76: return KeyVSmal;
		case 0x77: return KeyWSmal;
		case 0x78: return KeyXSmal;
		case 0x79: return KeyYSmal;
		case 0x7A: return KeyZSmal;

			/*
					/case 0x70: return KeyF1;
					//case 0x71: return KeyF2;
					//case 0x72: return KeyF3;
					//case 0x73: return KeyF4;
					case 0x74: return KeyF5;
					case 0x75: return KeyF6;
					case 0x76: return KeyF7;
					case 0x77: return KeyF8;
					case 0x78: return KeyF9;
					case 0x79: return KeyF10;
					case 0x7A: return KeyF11;*/
		case 0x7B: return KeyF12;
		case 0x7C: return KeyF13;
		case 0x7D: return KeyF14;
		case 0x7E: return KeyF15;
		case 0x7F: return KeyF16;
		case 0x80: return KeyF17;
		case 0x81: return KeyF18;
		case 0x82: return KeyF19;
		case 0x83: return KeyF20;
		case 0x84: return KeyF21;
		case 0x85: return KeyF22;
		case 0x86: return KeyF23;
		case 0x87: return KeyF24;

		case ButtonShiftLeft: return KeyShiftLeft;
		case ButtonShiftRight: return KeyShiftRight;
		case ButtonControlLeft: return KeyCONTROLLEFT;
		case ButtonControlRight: return KeyCONTROLRIGHT;
			// case ButtonMenuLeft: return ;
			// case ButtonMenuRight: return KeyShiftLeft;

		case ButtonBackSpace: return KeyBACKSPACE;
		case ButtonTab: return KeyTAB;
		case ButtonReturn: return KeyENTER;

			/*
			case ButtonKeyPad0: return KeyPad0;
			case ButtonKeyPad1: return KeyPad1;
			case ButtonKeyPad2: return KeyPad2;
			case ButtonKeyPad3: return KeyPad3;
			case ButtonKeyPad4: return KeyPad4;
			case ButtonKeyPad5: return KeyPad5;
			case ButtonKeyPad6: return KeyPad6;
			case ButtonKeyPad7: return KeyPad7;
			case ButtonKeyPad8: return KeyPad8;
			case ButtonKeyPad9: return KeyPad9;*/

		default:
			return KeyUnknown;
	}
}