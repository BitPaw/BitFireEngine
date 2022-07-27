#ifndef FNTInclude
#define FNTInclude

#define FontNameSize 30u
#define CharSetNameSize 30u
#define FNTPageFileNameSize 50

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct FNTInfo_
	{
		char Name[FontNameSize]; // Name of this font. (synonym: face)
		int Size;// Size of the Letters int Pixel as height.
		unsigned char Bold;// Is the text fat?
		unsigned char Italic;// Is the text cursive?
		char CharSet[CharSetNameSize];// The name of the OEM charset used (when not unicode). Like 'ANSI'.
		unsigned char Unicode;// Is the charset in the unicode format?
		int StretchH;
		unsigned char Smooth;// Set to 1 if smoothing was turned on.
		unsigned char Supersampling; // Supersampling level used. 1 means no supersampling was used. (AA)
		unsigned int CharacterPadding[4]; // Padding for each character.
		unsigned int SpacerOffset[2];
		unsigned int OutlineThickness;// How thick is the line arount the Letter?
	}
	FNTInfo;

	typedef enum FNTChanalMode_
	{
		FNTChanalInvalid,
		FNTChanalGlyphData,		// 0 if the channel holds the glyph data
		FNTChanalOutline, 		// 1 if it holds the outline		
		FNTChanalGlyphAndOutline,// 2 if it holds the glyphand the outline		
		FNTChanalSetToZero,		// 3 if its set to zero		
		FNTChanalSetToOne		// 4 if its set to one.
	}
	FNTChanalMode;

	typedef struct FNTCommonData_
	{
		int LineHeight;	// This is the distance in pixels between each line of text.		
		int Base;// The number of pixels from the absolute top of the line to the base of the characters.		
		int ScaleWidth; // The width of the texture, normally used to scale the x pos of the character image.	
		int ScaleHeight;	// The height of the texture, normally used to scale the y pos of the character image.	
		int AmountOfPages;	// The number of texture pages included in the font.	
		unsigned char Packed; // Set to 1 if the monochrome characters have been packed into each of the texture channels.In this case alphaChnl describes what is stored in each channel.

		FNTChanalMode AlphaChanal;
		FNTChanalMode RedChanal;
		FNTChanalMode GreenChanal;
		FNTChanalMode BlueChanal;
	}
	FNTCommonData;

	typedef struct FNTCharacter_
	{
		int ID;
		float Position[2]; // Position of the character image in the texture.
		float Size[2];	// Size of the character image in the texture.		
		float Offset[2];// Offset from the position-center.				
		int XAdvance; // How much the current position should be advanced after drawing the character.		
		int Page; // The texture page where the character image is found.		
		int Chanal;// The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).
	}
	FNTCharacter;


	typedef struct FNTPage_
	{
		int PageID;
		char PageFileName[FNTPageFileNameSize];
		size_t CharacteListSize;
		FNTCharacter* CharacteList;
	}
	FNTPage;


	typedef enum FNTLineType_
	{
		FNTLineUnkown,
		FNTLineInfo,
		FNTLineCommon,
		FNTLinePage,
		FNTLineCharacterCount,
		FNTLineCharacterDefinition
	}
	FNTLineType;


	typedef struct FNT_
	{
		FNTInfo Info;
		FNTCommonData CommonData;
		size_t FontPageListSize;
		FNTPage* FontPageList;
	}
	FNT;

	extern FNTCharacter* FNTGetCharacter(FNT* fnt, const char character);

	extern ActionResult FNTParse(FNT* fnt, const void* fileData, const size_t fileDataSize);

	static FNTLineType PeekLineType(const void* line, const size_t fileDataSize);

	extern void FNTPrtinf(const FNT* fnt);

#ifdef __cplusplus
}
#endif

#endif