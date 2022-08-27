#ifndef KeyBoardInclude
#define KeyBoardInclude

#include "VirtualKey.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define KeyBoardIDCommandEscape (1 << 0)
#define KeyBoardIDCommandEnter (1 << 1)
#define KeyBoardIDCommandTab (1 << 2)
#define KeyBoardIDCommandShift (1 << 3)
#define KeyBoardIDBACKSPACE (1 << 4)
#define KeyBoardIDINSERT (1 << 5)
#define KeyBoardIDDELETE (1 << 6)
#define KeyBoardIDRIGHT (1 << 7)
#define KeyBoardIDLEFT (1 << 8)
#define KeyBoardIDDOWN (1 << 9)
#define KeyBoardIDUP (1 << 10)
#define KeyBoardIDPAGE_UP (1 << 11)
#define KeyBoardIDPAGE_DOWN (1 << 12)
#define KeyBoardIDHOME (1 << 13)
#define KeyBoardIDEND (1 << 14)
#define KeyBoardIDCAPS_LOCK (1 << 15)
#define KeyBoardIDSCROLL_LOCK (1 << 16)
#define KeyBoardIDNUM_LOCK (1 << 17)
#define KeyBoardIDPRINT_SCREEN (1 << 18)
#define KeyBoardIDPAUSE (1 << 19)
#define KeyBoardIDPadENTER (1 << 20)
#define KeyBoardIDShiftLeft (1 << 21)
#define KeyBoardIDShiftRight (1 << 22)
#define KeyBoardIDCONTROLLEFT (1 << 23)
#define KeyBoardIDALTLEFT (1 << 24)
#define KeyBoardIDSUPERLEFT (1 << 25)
#define KeyBoardIDCONTROLRIGHT (1 << 26)
#define KeyBoardIDALTRIGHT (1 << 27)
#define KeyBoardIDSUPERRIGHT (1 << 28)
#define KeyBoardIDMENU (1 << 29)
#define KeyBoardIDWORLD_1  (1 << 30)
#define KeyBoardIDWORLD_2  (1 << 31)


#define KeyBoardIDF01 (1u << 0u)
#define KeyBoardIDF02 (1u << 1u)
#define KeyBoardIDF03 (1u << 2u)
#define KeyBoardIDF04 (1u << 3u)
#define KeyBoardIDF05 (1u << 4u)
#define KeyBoardIDF06 (1u << 5u)
#define KeyBoardIDF07 (1u << 6u)
#define KeyBoardIDF08 (1u << 7u)
#define KeyBoardIDF09 (1u << 8u)
#define KeyBoardIDF10 (1u << 9u)
#define KeyBoardIDF11 (1u << 10u)
#define KeyBoardIDF12 (1u << 11u)
#define KeyBoardIDF13 (1u << 12u)
#define KeyBoardIDF14 (1u << 13u)
#define KeyBoardIDF15 (1u << 14u)
#define KeyBoardIDF16 (1u << 15u)
#define KeyBoardIDF17 (1u << 16u)
#define KeyBoardIDF18 (1u << 17u)
#define KeyBoardIDF19 (1u << 18u)
#define KeyBoardIDF20 (1u << 19u)
#define KeyBoardIDF21 (1u << 20u)
#define KeyBoardIDF22 (1u << 21u)
#define KeyBoardIDF23 (1u << 22u)
#define KeyBoardIDF24 (1u << 23u)
#define KeyBoardIDF25 (1u << 24u)


#define KeyBoardIDLetterA (1u << 0)
#define KeyBoardIDLetterB (1u << 1)
#define KeyBoardIDLetterC (1u << 2)
#define KeyBoardIDLetterD (1u << 3)
#define KeyBoardIDLetterE (1u << 4)
#define KeyBoardIDLetterF (1u << 5)
#define KeyBoardIDLetterG (1u << 6)
#define KeyBoardIDLetterH (1u << 7)
#define KeyBoardIDLetterI (1u << 8)
#define KeyBoardIDLetterJ (1u << 9)
#define KeyBoardIDLetterK (1u << 10)
#define KeyBoardIDLetterL (1u << 11)
#define KeyBoardIDLetterM (1u << 12)
#define KeyBoardIDLetterN (1u << 13)
#define KeyBoardIDLetterO (1u << 14)
#define KeyBoardIDLetterP (1u << 15)
#define KeyBoardIDLetterQ (1u << 16)
#define KeyBoardIDLetterR (1u << 17)
#define KeyBoardIDLetterS (1u << 18)
#define KeyBoardIDLetterT (1u << 19)
#define KeyBoardIDLetterU (1u << 20)
#define KeyBoardIDLetterV (1u << 21)
#define KeyBoardIDLetterW (1u << 22)
#define KeyBoardIDLetterX (1u << 23)
#define KeyBoardIDLetterY (1u << 24)
#define KeyBoardIDLetterZ (1u << 25)
#define KeyBoardIDSpace	  (1u << 26)
#define KeyBoardIDAPOSTROPHE  (1u << 27)  /* ' */
#define KeyBoardIDComma       (1u << 28)  /* , */
#define KeyBoardIDGRAVE_ACCENT (1u << 29)  /* ` */
#define KeyBoardIDSemicolon   (1u << 30)  /* ; */
#define KeyBoardIDDECIMAL (1u << 31)


#define KeyBoardIDNumber0 (1 << 0)
#define KeyBoardIDNumber1 (1 << 1)
#define KeyBoardIDNumber2 (1 << 2)
#define KeyBoardIDNumber3 (1 << 3)
#define KeyBoardIDNumber4 (1 << 4)
#define KeyBoardIDNumber5 (1 << 5)
#define KeyBoardIDNumber6 (1 << 6)
#define KeyBoardIDNumber7 (1 << 7)
#define KeyBoardIDNumber8 (1 << 8)
#define KeyBoardIDNumber9 (1 << 9)
#define KeyBoardIDNumberBlock0 (1 << 10)
#define KeyBoardIDNumberBlock1 (1 << 11)
#define KeyBoardIDNumberBlock2 (1 << 12)
#define KeyBoardIDNumberBlock3 (1 << 13)
#define KeyBoardIDNumberBlock4 (1 << 14)
#define KeyBoardIDNumberBlock5 (1 << 15)
#define KeyBoardIDNumberBlock6 (1 << 16)
#define KeyBoardIDNumberBlock7 (1 << 17)
#define KeyBoardIDNumberBlock8 (1 << 18)
#define KeyBoardIDNumberBlock9 (1 << 19)
#define KeyBoardIDNumberKeyMinus (1 << 20) 
#define KeyBoardIDNumberKeyPeriod (1 << 21) 
#define KeyBoardIDNumberKeySlash (1 << 22) 
#define KeyBoardIDNumberKeyEqual (1 << 23) 
#define KeyBoardIDNumberKeyLEFT_BRACKET (1 << 24)  
#define KeyBoardIDNumberKeyBACKSLASH (1 << 25)  
#define KeyBoardIDNumberKeyRIGHT_BRACKET (1 << 26) 
#define KeyBoardIDNumberKeyPadDIVIDE (1 << 27)
#define KeyBoardIDNumberKeyPadMULTIPLY (1 << 28)
#define KeyBoardIDNumberKeyPadSUBTRACT (1 << 29)
#define KeyBoardIDNumberKeyPadADD (1 << 30)		
#define KeyBoardIDNumberKeyPadEQUAL (1 << 31)

	typedef struct KeyBoard_
	{
		unsigned int Letters; // A, B, C, D, ...
		unsigned int Numbers; // 0,1,2... and +, -, /, ...
		unsigned int Commands; // Enter, Escape, ect..
		unsigned int Actions; // F-01 to F-xx
	}
	KeyBoard;

	extern void KeyBoardInputReset(KeyBoard* keyBoard);

	extern unsigned char KeyBoardKeyPressedGet(KeyBoard* keyBoard, const VirtualKey virtualKey);
	extern unsigned char KeyBoardKeyPressedSet(KeyBoard* keyBoard, const VirtualKey virtualKey, const unsigned char isPressed);

	extern void KeyBoardInputPrint(KeyBoard* keyBoard);

#ifdef __cplusplus
}
#endif

#endif
