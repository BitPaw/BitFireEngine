#include "KeyBoardKey.h"

BF::KeyBoardKey BF::ConvertKeyBoardKey(wchar_t character)
{
	switch (character)
	{
		case L'A': return KeyBoardKey::KeyA;
		case L'B': return KeyBoardKey::KeyB;
		case L'C': return KeyBoardKey::KeyC;
		case L'D': return KeyBoardKey::KeyD;
		case L'E': return KeyBoardKey::KeyE;
		case L'F': return KeyBoardKey::KeyF;
		case L'G': return KeyBoardKey::KeyG;
		case L'H': return KeyBoardKey::KeyH;
		case L'I': return KeyBoardKey::KeyI;
		case L'J': return KeyBoardKey::KeyJ;
		case L'K': return KeyBoardKey::KeyK;
		case L'L': return KeyBoardKey::KeyL;
		case L'M': return KeyBoardKey::KeyM;
		case L'N': return KeyBoardKey::KeyN;
		case L'O': return KeyBoardKey::KeyO;
		case L'P': return KeyBoardKey::KeyP;
		case L'Q': return KeyBoardKey::KeyQ;
		case L'R': return KeyBoardKey::KeyR;
		case L'S': return KeyBoardKey::KeyS;
		case L'T': return KeyBoardKey::KeyT;
		case L'U': return KeyBoardKey::KeyU;
		case L'V': return KeyBoardKey::KeyV;
		case L'W': return KeyBoardKey::KeyW;
		case L'X': return KeyBoardKey::KeyX;
		case L'Y': return KeyBoardKey::KeyY;
		case L'Z': return KeyBoardKey::KeyZ;			

		default:
			break;
	}

    return KeyBoardKey::KeyUnknown;
}
