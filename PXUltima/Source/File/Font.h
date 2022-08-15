#ifndef FontInclude
#define FontInclude

#include <stddef.h>

#include <File/Image.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum FontFileFormat_
	{
		FontFileFormatUnkown,
		FontFileFormatFNT,
		FontFileFormatOFT,
		FontFileFormatTTF
	}
	FontFileFormat;

	typedef struct CFont_
	{
		unsigned short CharacterSize;
		unsigned short SizeBetweenCharacters;
		unsigned short SizeBetweenLines;
		size_t AdditionalResourceListSize;
		char** AdditionalResourceList;
		Image* Texture;
		void* BitMapFont;
	}
	CFont;

	//---[ Public-Functions ]----------------------------------------------

	extern void FontConstruct(CFont* font);
	extern void FontDestruct(CFont* font);

	extern FontFileFormat FontGuessFormat(const wchar_t* filePath);

	extern ActionResult FontLoadA(CFont* font, const char* filePath);
	extern ActionResult FontLoadW(CFont* font, const wchar_t* filePath);
	extern ActionResult FontLoadD(CFont* font, const FontFileFormat guessedFormat, const void* data, const size_t dataSize);


#ifdef __cplusplus
}
#endif

#endif



