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


	typedef struct Font_
	{
		unsigned short CharacterSize;
		unsigned short SizeBetweenCharacters;
		unsigned short SizeBetweenLines;
		size_t AdditionalResourceListSize;
		char** AdditionalResourceList;
		Image* Texture;
		void* BitMapFont;
	}
	Font;

	//---[ Public-Functions ]----------------------------------------------

	extern void FontConstruct(Font* font);
	extern void FontDestruct(Font* font);

	extern FontFileFormat FontGuessFormat(const wchar_t* filePath);

	extern ActionResult FontLoadA(Font* font, const char* filePath);
	extern ActionResult FontLoadW(Font* font, const wchar_t* filePath);
	extern ActionResult FontLoadD(Font* font, const FontFileFormat guessedFormat, const void* data, const size_t dataSize);


#ifdef __cplusplus
}
#endif

#endif



