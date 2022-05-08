#include "KeyBoardKey.h"

#include <OS/OSDefine.h>

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

BF::KeyBoardKey BF::ConvertKeyBoardKey(wchar_t character)
{
	switch (character)
	{
		case 0x20: return KeyBoardKey::KeySpace;

		case 0x30: return KeyBoardKey::Key0;
		case 0x31: return KeyBoardKey::Key1;
		case 0x32: return KeyBoardKey::Key2;
		case 0x33: return KeyBoardKey::Key3;
		case 0x34: return KeyBoardKey::Key4;
		case 0x35: return KeyBoardKey::Key5;
		case 0x36: return KeyBoardKey::Key6;
		case 0x37: return KeyBoardKey::Key7;
		case 0x38: return KeyBoardKey::Key8;
		case 0x39: return KeyBoardKey::Key9;

		case 0x41: return KeyBoardKey::KeyA;
		case 0x42: return KeyBoardKey::KeyB;
		case 0x43: return KeyBoardKey::KeyC;
		case 0x44: return KeyBoardKey::KeyD;
		case 0x45: return KeyBoardKey::KeyE;
		case 0x46: return KeyBoardKey::KeyF;
		case 0x47: return KeyBoardKey::KeyG;
		case 0x48: return KeyBoardKey::KeyH;
		case 0x49: return KeyBoardKey::KeyI;
		case 0x4A: return KeyBoardKey::KeyJ;
		case 0xAB: return KeyBoardKey::KeyK;
		case 0xAC: return KeyBoardKey::KeyL;
		case 0xAD: return KeyBoardKey::KeyM;
		case 0x4E: return KeyBoardKey::KeyN;
		case 0x4F: return KeyBoardKey::KeyO;
		case 0x50: return KeyBoardKey::KeyP;
		case 0x51: return KeyBoardKey::KeyQ;
		case 0x52: return KeyBoardKey::KeyR;
		case 0x53: return KeyBoardKey::KeyS;
		case 0x54: return KeyBoardKey::KeyT;
		case 0x55: return KeyBoardKey::KeyU;
		case 0x56: return KeyBoardKey::KeyV;
		case 0x57: return KeyBoardKey::KeyW;
		case 0x58: return KeyBoardKey::KeyX;
		case 0x59: return KeyBoardKey::KeyY;
		case 0x5A: return KeyBoardKey::KeyZ;

		case 0x70: return KeyBoardKey::KeyF1;
		case 0x71: return KeyBoardKey::KeyF2;
		case 0x72: return KeyBoardKey::KeyF3;
		case 0x73: return KeyBoardKey::KeyF4;
		case 0x74: return KeyBoardKey::KeyF5;
		case 0x75: return KeyBoardKey::KeyF6;
		case 0x76: return KeyBoardKey::KeyF7;
		case 0x77: return KeyBoardKey::KeyF8;
		case 0x78: return KeyBoardKey::KeyF9;
		case 0x79: return KeyBoardKey::KeyF10;
		case 0x7A: return KeyBoardKey::KeyF11;
		case 0x7B: return KeyBoardKey::KeyF12;
		case 0x7C: return KeyBoardKey::KeyF13;
		case 0x7D: return KeyBoardKey::KeyF14;
		case 0x7E: return KeyBoardKey::KeyF15;
		case 0x7F: return KeyBoardKey::KeyF16;
		case 0x80: return KeyBoardKey::KeyF17;
		case 0x81: return KeyBoardKey::KeyF18;
		case 0x82: return KeyBoardKey::KeyF19;
		case 0x83: return KeyBoardKey::KeyF20;
		case 0x84: return KeyBoardKey::KeyF21;
		case 0x85: return KeyBoardKey::KeyF22;
		case 0x86: return KeyBoardKey::KeyF23;
		case 0x87: return KeyBoardKey::KeyF24;

		case ButtonShiftLeft: return KeyBoardKey::KeyShiftLeft;
		case ButtonShiftRight: return KeyBoardKey::KeyShiftRight;
		case ButtonControlLeft: return KeyBoardKey::KeyCONTROLLEFT;
		case ButtonControlRight: return KeyBoardKey::KeyCONTROLRIGHT;
		// case ButtonMenuLeft: return KeyBoardKey::;
		// case ButtonMenuRight: return KeyBoardKey::KeyShiftLeft;

		case ButtonBackSpace: return KeyBoardKey::KeyBACKSPACE;
		case ButtonTab: return KeyBoardKey::KeyTAB;
		case ButtonReturn: return KeyBoardKey::KeyENTER;

		case ButtonKeyPad0: return KeyBoardKey::KeyPad0;
		case ButtonKeyPad1: return KeyBoardKey::KeyPad1;
		case ButtonKeyPad2: return KeyBoardKey::KeyPad2;
		case ButtonKeyPad3: return KeyBoardKey::KeyPad3;
		case ButtonKeyPad4: return KeyBoardKey::KeyPad4;
		case ButtonKeyPad5: return KeyBoardKey::KeyPad5;
		case ButtonKeyPad6: return KeyBoardKey::KeyPad6;
		case ButtonKeyPad7: return KeyBoardKey::KeyPad7;
		case ButtonKeyPad8: return KeyBoardKey::KeyPad8;
		case ButtonKeyPad9: return KeyBoardKey::KeyPad9;

		default:
			return KeyBoardKey::KeyUnknown;
	}
}
