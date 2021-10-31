#pragma once

#define KeyBoardUNKNOWN            -1

#define KeyBoardSPACE              32
#define KeyBoardAPOSTROPHE         39  /* ' */
#define KeyBoardCOMMA              44  /* , */
#define KeyBoardMINUS              45  /* - */
#define KeyBoardPERIOD             46  /* . */
#define KeyBoardSLASH              47  /* / */
#define KeyBoard0                  48
#define KeyBoard1                  49
#define KeyBoard2                  50
#define KeyBoard3                  51
#define KeyBoard4                  52
#define KeyBoard5                  53
#define KeyBoard6                  54
#define KeyBoard7                  55
#define KeyBoard8                  56
#define KeyBoard9                  57
#define KeyBoardSEMICOLON          59  /* ; */
#define KeyBoardEQUAL              61  /* = */
#define KeyBoardA                  65
#define KeyBoardB                  66
#define KeyBoardC                  67
#define KeyBoardD                  68
#define KeyBoardE                  69
#define KeyBoardF                  70
#define KeyBoardG                  71
#define KeyBoardH                  72
#define KeyBoardI                  73
#define KeyBoardJ                  74
#define KeyBoardK                  75
#define KeyBoardL                  76
#define KeyBoardM                  77
#define KeyBoardN                  78
#define KeyBoardO                  79
#define KeyBoardP                  80
#define KeyBoardQ                  81
#define KeyBoardR                  82
#define KeyBoardS                  83
#define KeyBoardT                  84
#define KeyBoardU                  85
#define KeyBoardV                  86
#define KeyBoardW                  87
#define KeyBoardX                  88
#define KeyBoardY                  89
#define KeyBoardZ                  90
#define KeyBoardLEFT_BRACKET       91  /* [ */
#define KeyBoardBACKSLASH          92  /* \ */
#define KeyBoardRIGHT_BRACKET      93  /* ] */
#define KeyBoardGRAVE_ACCENT       96  /* ` */
#define KeyBoardWORLD_1            161 /* non-US #1 */
#define KeyBoardWORLD_2            162 /* non-US #2 */

#define KeyBoardESCAPE             256
#define KeyBoardENTER              257
#define KeyBoardTAB                258
#define KeyBoardBACKSPACE          259
#define KeyBoardINSERT             260
#define KeyBoardDELETE             261
#define KeyBoardRIGHT              262
#define KeyBoardLEFT               263
#define KeyBoardDOWN               264
#define KeyBoardUP                 265
#define KeyBoardPAGE_UP            266
#define KeyBoardPAGE_DOWN          267
#define KeyBoardHOME               268
#define KeyBoardEND                269
#define KeyBoardCAPS_LOCK          280
#define KeyBoardSCROLL_LOCK        281
#define KeyBoardNUM_LOCK           282
#define KeyBoardPRINT_SCREEN       283
#define KeyBoardPAUSE              284
#define KeyBoardF1                 290
#define KeyBoardF2                 291
#define KeyBoardF3                 292
#define KeyBoardF4                 293
#define KeyBoardF5                 294
#define KeyBoardF6                 295
#define KeyBoardF7                 296
#define KeyBoardF8                 297
#define KeyBoardF9                 298
#define KeyBoardF10                299
#define KeyBoardF11                300
#define KeyBoardF12                301
#define KeyBoardF13                302
#define KeyBoardF14                303
#define KeyBoardF15                304
#define KeyBoardF16                305
#define KeyBoardF17                306
#define KeyBoardF18                307
#define KeyBoardF19                308
#define KeyBoardF20                309
#define KeyBoardF21                310
#define KeyBoardF22                311
#define KeyBoardF23                312
#define KeyBoardF24                313
#define KeyBoardF25                314
#define KeyBoardPad0               320
#define KeyBoardPad1               321
#define KeyBoardPad2               322
#define KeyBoardPad3               323
#define KeyBoardPad4               324
#define KeyBoardPad5               325
#define KeyBoardPad6               326
#define KeyBoardPad7               327
#define KeyBoardPad8               328
#define KeyBoardPad9               329
#define KeyBoardPadDECIMAL         330
#define KeyBoardPadDIVIDE          331
#define KeyBoardPadMULTIPLY        332
#define KeyBoardPadSUBTRACT        333
#define KeyBoardPadADD             334
#define KeyBoardPadENTER           335
#define KeyBoardPadEQUAL           336
#define KeyBoardSHIFTLEFT          340
#define KeyBoardCONTROLLEFT        341
#define KeyBoardALTLEFT            342
#define KeyBoardSUPERLEFT          343
#define KeyBoardSHIFTRIGHT         344
#define KeyBoardCONTROLRIGHT       345
#define KeyBoardALTRIGHT           346
#define KeyBoardSUPERRIGHT         347
#define KeyBoardMENU               348

namespace BF
{
	enum class Key
	{
		KeyUNKNOWN,

		KeySPACE              ,
		KeyAPOSTROPHE         ,  /* ' */
		KeyCOMMA              ,  /* , */
		KeyMINUS              ,  /* - */
		KeyPERIOD             ,  /* . */
		KeySLASH              ,  /* / */
		Key0                  ,
		Key1                  ,
		Key2                  ,
		Key3                  ,
		Key4                  ,
		Key5                  ,
		Key6                  ,
		Key7                  ,
		Key8                  ,
		Key9                  ,
		KeySEMICOLON          ,  /* ; */
		KeyEQUAL              ,  /* = */
		KeyA                  ,
		KeyB                  ,
		KeyC                  ,
		KeyD                  ,
		KeyE                  ,
		KeyF                  ,
		KeyG                  ,
		KeyH                  ,
		KeyI                  ,
		KeyJ                  ,
		KeyK                  ,
		KeyL                  ,
		KeyM                  ,
		KeyN                  ,
		KeyO                  ,
		KeyP                  ,
		KeyQ                  ,
		KeyR                  ,
		KeyS                  ,
		KeyT                  ,
		KeyU                  ,
		KeyV                  ,
		KeyW                  ,
		KeyX                  ,
		KeyY                  ,
		KeyZ                  ,
		KeyLEFT_BRACKET       ,  /* [ */
		KeyBACKSLASH          ,  /* \ */
		KeyRIGHT_BRACKET      ,  /* ] */
		KeyGRAVE_ACCENT       ,  /* ` */
		KeyWORLD_1            , /* non-US #1 */
		KeyWORLD_2            , /* non-US #2 */

		KeyESCAPE             ,
		KeyENTER              ,
		KeyTAB                ,
		KeyBACKSPACE          ,
		KeyINSERT             ,
		KeyDELETE             ,
		KeyRIGHT              ,
		KeyLEFT               ,
		KeyDOWN               ,
		KeyUP                 ,
		KeyPAGE_UP            ,
		KeyPAGE_DOWN          ,
		KeyHOME               ,
		KeyEND                ,
		KeyCAPS_LOCK          ,
		KeySCROLL_LOCK        ,
		KeyNUM_LOCK           ,
		KeyPRINT_SCREEN       ,
		KeyPAUSE              ,
		KeyF1                 ,
		KeyF2                 ,
		KeyF3                 ,
		KeyF4                 ,
		KeyF5                 ,
		KeyF6                 ,
		KeyF7                 ,
		KeyF8                 ,
		KeyF9                 ,
		KeyF10                ,
		KeyF11                ,
		KeyF12                ,
		KeyF13                ,
		KeyF14                ,
		KeyF15                ,
		KeyF16                ,
		KeyF17                ,
		KeyF18                ,
		KeyF19                ,
		KeyF20                ,
		KeyF21                ,
		KeyF22                ,
		KeyF23                ,
		KeyF24                ,
		KeyF25                ,
		KeyPad0               ,
		KeyPad1               ,
		KeyPad2               ,
		KeyPad3               ,
		KeyPad4               ,
		KeyPad5               ,
		KeyPad6               ,
		KeyPad7               ,
		KeyPad8               ,
		KeyPad9               ,
		KeyPadDECIMAL         ,
		KeyPadDIVIDE          ,
		KeyPadMULTIPLY        ,
		KeyPadSUBTRACT        ,
		KeyPadADD             ,
		KeyPadENTER           ,
		KeyPadEQUAL           ,
		KeySHIFTLEFT          ,
		KeyCONTROLLEFT        ,
		KeyALTLEFT            ,
		KeySUPERLEFT          ,
		KeySHIFTRIGHT         ,
		KeyCONTROLRIGHT       ,
		KeyALTRIGHT           ,
		KeySUPERRIGHT         ,
		KeyMENU               
	};

	Key ConvertKeyToChar(int key);
	int ConvertKeyToChar(Key key);
}