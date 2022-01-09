#include "FNT.h"
#include "FNTCommand.h"
#include "FNTLineType.h"

#include "../../File/FileStream.h"
#include "../../File/File.h"
#include "../../File/Text.h"

BF::FNTCharacter* BF::FNT::GetCharacterPosition(unsigned char character)
{
	FNTPage& page = FontPageList[0];

	for (unsigned int i = 0; i < page.CharacteListSize; i++)
	{
		FNTCharacter* bitMapFontCharacter = &page.CharacteList[i];
		unsigned char target = bitMapFontCharacter->ID;

		bool isSameCharacter = target == character;

		if (isSameCharacter)
		{
			return bitMapFontCharacter;
		}
	}

	return nullptr;
}

BF::FNT::FNT()
{
	FontPageListSize = 0;
	FontPageList = 0;
}

BF::FNT::~FNT()
{
	delete[] FontPageList;
}



BF::FileActionResult BF::FNT::Load(const wchar_t* filePath)
{
	FileStream file;
	FileActionResult fileActionResult = file.ReadFromDisk(filePath);

	if (fileActionResult != FileActionResult::Successful)
	{
		return fileActionResult;
	}

	size_t bufferSize = 512;
	char currentCursor[512];
	FNTPage* currentPage = nullptr;
	size_t characterIndex = 0;

	while (file.ReadNextLineInto(currentCursor))
	{
		const FNTLineType lineType = ConvertFNTLineType(currentCursor);
				
		switch (lineType)
		{
			case BF::FNTLineType::Info:
			{	
				const char faceText[] = "face";
				const char sizeText[] = "size";
				const char scaleWText[] = "scaleW";
				const char boldText[] = "bold";
				const char italicText[] = "italic";
				const char charsetText[] = "charset";
				const char unicodeText[] = "unicode";
				const char stretchHText[] = "stretchH";
				const char smoothText[] = "smooth";
				const char aaText[] = "aa";
				const char paddingText[] = "padding";
				const char spacingText[] = "spacing";
				const char outlineThicknessText[] = "xxxxx";


				char* face = Text::FindPosition(currentCursor, bufferSize, faceText, sizeof(faceText));
				char* size = Text::FindPosition(currentCursor, bufferSize, sizeText, sizeof(sizeText));
				char* scaleW = Text::FindPosition(currentCursor, bufferSize, scaleWText, sizeof(scaleWText));
				char* bold = Text::FindPosition(currentCursor, bufferSize, boldText, sizeof(boldText));
				char* italic = Text::FindPosition(currentCursor, bufferSize, italicText, sizeof(italicText));
				char* charset = Text::FindPosition(currentCursor, bufferSize, charsetText, sizeof(charsetText));
				char* unicode = Text::FindPosition(currentCursor, bufferSize, unicodeText, sizeof(unicodeText));
				char* stretchH = Text::FindPosition(currentCursor, bufferSize, stretchHText, sizeof(stretchHText));
				char* smooth = Text::FindPosition(currentCursor, bufferSize, smoothText, sizeof(smoothText));
				char* aa = Text::FindPosition(currentCursor, bufferSize, aaText, sizeof(aaText));
				char* padding = Text::FindPosition(currentCursor, bufferSize, paddingText, sizeof(paddingText));
				char* spacing = Text::FindPosition(currentCursor, bufferSize, spacingText, sizeof(spacingText));
				char* outlineThickness = Text::FindPosition(currentCursor, bufferSize, outlineThicknessText, sizeof(outlineThicknessText));

				Text::Copy(Info.Name, face + sizeof(faceText) + 1, FontNameSize);
				Text::ToInt(size + sizeof(sizeText), bufferSize - sizeof(sizeText), Info.Size);
				//Text::ToBool(scaleW + sizeof(scaleWText), bufferSize - sizeof(scaleWText), Info.);
				Text::ToBool(bold + sizeof(boldText), bufferSize - sizeof(boldText), Info.Bold);
				Text::ToBool(italic + sizeof(italicText), bufferSize - sizeof(italicText), Info.Italic);
				Text::Copy(Info.CharSet, charset + sizeof(charsetText) + 1, CharSetNameSize);
				Text::ToBool(unicode + sizeof(unicodeText), bufferSize - sizeof(unicodeText), Info.Unicode);
				Text::ToInt(stretchH + sizeof(stretchHText), bufferSize - sizeof(stretchHText), Info.StretchH);
				Text::ToBool(smooth + sizeof(smoothText), bufferSize - sizeof(smoothText), Info.Smooth);
				Text::ToBool(aa + sizeof(aaText), bufferSize - sizeof(aaText), Info.Supersampling);
				//Text::ToInt(padding + sizeof(paddingText), bufferSize - sizeof(paddingText), Info.CharacterPadding);
				//Text::ToInt(spacing + sizeof(spacingText), bufferSize - sizeof(spacingText), Info.SpacerOffset);
				//Text::ToInt(outlineThickness + sizeof(outlineThicknessText), bufferSize - sizeof(outlineThicknessText), Info.OutlineThickness);

				Text::TerminateBeginFromFirst(Info.Name, FontNameSize, '\"');
				Text::TerminateBeginFromFirst(Info.CharSet, CharSetNameSize, '\"');

				break;
			}	
			case BF::FNTLineType::Common:
			{
				const char lineHeightText[] = "lineHeight";
				const char baseText[] = "base";
				const char scaleWText[] = "scaleW";
				const char scaleHText[] = "scaleH";
				const char pagesText[] = "pages";
				const char packedText[] = "packed";

				char* lineHeight = Text::FindPosition(currentCursor, bufferSize, lineHeightText, sizeof(lineHeightText));
				char* base = Text::FindPosition(currentCursor, bufferSize, baseText, sizeof(baseText));
				char* scaleW = Text::FindPosition(currentCursor, bufferSize, scaleWText, sizeof(scaleWText));
				char* scaleH = Text::FindPosition(currentCursor, bufferSize, scaleHText, sizeof(scaleHText));
				char* pages	= Text::FindPosition(currentCursor, bufferSize, pagesText, sizeof(pagesText));
				char* packed = Text::FindPosition(currentCursor, bufferSize, packedText, sizeof(packedText));

				Text::ToInt(lineHeight + sizeof(lineHeightText), bufferSize - sizeof(lineHeightText), CommonData.LineHeight);
				Text::ToInt(base + sizeof(baseText), bufferSize - sizeof(baseText), CommonData.Base);
				Text::ToInt(scaleW + sizeof(scaleWText), bufferSize - sizeof(scaleWText), CommonData.ScaleWidth);
				Text::ToInt(scaleH + sizeof(scaleHText), bufferSize - sizeof(scaleHText), CommonData.ScaleHeight);
				Text::ToInt(pages + sizeof(pagesText), bufferSize - sizeof(pagesText), CommonData.AmountOfPages);
				Text::ToBool(packed + sizeof(packedText), bufferSize - sizeof(packedText), CommonData.Packed);

				FontPageListSize = CommonData.AmountOfPages;
				FontPageList = new FNTPage[FontPageListSize];

				currentPage = FontPageList;

				break;
			}
			case BF::FNTLineType::Page:
			{
				const char idText[] = "id";
				const char fileText[] = "file";

				char* id = Text::FindPosition(currentCursor, bufferSize, idText, sizeof(idText));
				char* file = Text::FindPosition(currentCursor, bufferSize, fileText, sizeof(fileText));

				Text::ToInt(id + sizeof(idText), bufferSize - sizeof(idText), currentPage->PageID);
				Text::Copy(currentPage->PageFileName, file + sizeof(fileText) + 1, FNTPageFileNameSize);

				Text::TerminateBeginFromFirst(currentPage->PageFileName, FNTPageFileNameSize, '\"');				

				break;
			}
			case BF::FNTLineType::CharacterCount:
			{
				const char countText[] = "count";
				char* count = Text::FindPosition(currentCursor, bufferSize, countText, sizeof(countText));
			
				Text::ToInt(count + sizeof(countText), bufferSize - sizeof(countText), currentPage->PageID);
	
				currentPage->CharacteListSize = currentPage->PageID;
				currentPage->CharacteList = new FNTCharacter[currentPage->CharacteListSize];

				characterIndex = 0;

				break;
			}
			case BF::FNTLineType::CharacterDefinition:
			{				
				FNTCharacter& character = currentPage->CharacteList[characterIndex++];
		
				const char idText[] = "id";
				const char xText[] = "x";
				const char yText[] = "y";
				const char widthText[] = "width";
				const char heightText[] = "height";
				const char xoffsetText[] = "xoffset";
				const char yoffsetText[] = "yoffset";
				const char xadvanceText[] = "xadvance";
				const char pageText[] = "page";
				const char chnlText[] = "chnl";

				char* id = Text::FindPosition(currentCursor, bufferSize, idText, sizeof(idText));
				char* x = Text::FindPosition(currentCursor, bufferSize, xText, sizeof(xText));
				char* y = Text::FindPosition(currentCursor, bufferSize, yText, sizeof(yText));
				char* width = Text::FindPosition(currentCursor, bufferSize, widthText, sizeof(widthText));
				char* height = Text::FindPosition(currentCursor, bufferSize, heightText, sizeof(heightText));
				char* xoffset = Text::FindPosition(currentCursor, bufferSize, xoffsetText, sizeof(xoffsetText));
				char* yoffset = Text::FindPosition(currentCursor, bufferSize, yoffsetText, sizeof(yoffsetText));
				char* xadvance = Text::FindPosition(currentCursor, bufferSize, xadvanceText, sizeof(xadvanceText));
				char* page = Text::FindPosition(currentCursor, bufferSize, pageText, sizeof(pageText));
				char* chnl = Text::FindPosition(currentCursor, bufferSize, chnlText, sizeof(chnlText));
									
				Text::ToInt(id + sizeof(idText), bufferSize - sizeof(idText), character.ID);
				Text::ToFloat(x + sizeof(xText), bufferSize - sizeof(xText), character.Position[0]);
				Text::ToFloat(y + sizeof(yText), bufferSize - sizeof(yText), character.Position[1]);
				Text::ToFloat(width + sizeof(widthText), bufferSize - sizeof(widthText), character.Size[0]);
				Text::ToFloat(height + sizeof(heightText), bufferSize - sizeof(heightText), character.Size[1]);
				Text::ToFloat(xoffset + sizeof(xoffsetText), bufferSize - sizeof(xoffsetText), character.Offset[0]);
				Text::ToFloat(yoffset + sizeof(yoffsetText), bufferSize - sizeof(yoffsetText), character.Offset[1]);
				Text::ToInt(xadvance + sizeof(xadvanceText), bufferSize - sizeof(xadvanceText), character.XAdvance);
				Text::ToInt(page + sizeof(pageText), bufferSize - sizeof(pageText), character.Page);
				Text::ToInt(chnl + sizeof(chnlText), bufferSize - sizeof(chnlText), character.Chanal);
							
				break;
			}
			case BF::FNTLineType::Unkown:
			default:
			{
				// Ignore
				break;
			}			
		}
	}

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FNT::Save(const wchar_t* filePath)
{
	int characterWritten = 0;
	
	File file;
	file.Open(filePath, FileOpenMode::Write);

	characterWritten = fprintf
	(
		file.FileMarker,
		"info face=\"%s\" size=%i bold=%i italic=%i charset=%s unicode=%i stretchH=%i smooth=%i aa=%i padding=%i,%i,%i,%i spacing=%i,%i\n",
		Info.Name,
		Info.Size,
		Info.Bold,
		Info.Italic,
		Info.CharSet,
		Info.Unicode,
		Info.StretchH,
		Info.Smooth,
		Info.Supersampling,
		Info.CharacterPadding[0],
		Info.CharacterPadding[1],
		Info.CharacterPadding[2],
		Info.CharacterPadding[3],
		Info.SpacerOffset[0],
		Info.SpacerOffset[1]
	);

	characterWritten = fprintf
	(
		file.FileMarker,
		"common lineHeight=%i base=%i scaleW=%i scaleH=%i pages=%i packed=%i\n",
		CommonData.LineHeight,
		CommonData.Base,
		CommonData.ScaleWidth,
		CommonData.ScaleHeight,
		CommonData.AmountOfPages,
		CommonData.Packed
	);

	for (unsigned int i = 0; i < FontPageListSize; i++)
	{
		FNTPage& page = FontPageList[i];

		characterWritten = fprintf
		(
			file.FileMarker,
			"page id=%i file=\"%s\"\n"
			"chars count=%zi",
			page.PageID,
			page.PageFileName,
			page.CharacteListSize
		);

		for (size_t i = 0; i < page.CharacteListSize; i++)
		{
			FNTCharacter& character = page.CharacteList[i];

			characterWritten = fprintf
			(
				file.FileMarker,
				"char id=%i x=%f y=%f width=%f height=%f xoffset=%f yoffset=%f xadvance=%i page=%i chnl=%i\n",
				character.ID,
				character.Position[0],
				character.Position[1],
				character.Size[0],
				character.Size[1],
				character.Offset[0],
				character.Offset[1],
				character.XAdvance,
				character.Page,
				character.Chanal
			);
		}
	}

	FileActionResult closingResult = file.Close();

	return closingResult;
}

BF::FileActionResult BF::FNT::ConvertTo(Font& font)
{
	unsigned int amountOfResources = FontPageListSize;

	Text::Copy(font.Name, Info.Name, FNTPageFileNameSize);

	font.BitMapFont = this;
	font.AdditionalResourceListSize = amountOfResources;
	font.CharacterSize = Info.Size;
	font.SizeBetweenLines = CommonData.LineHeight;
	font.AdditionalResourceList = (char**)malloc(amountOfResources * sizeof(char*));

	for (size_t i = 0; i < amountOfResources; i++)
	{
		FNTPage& page = FontPageList[i];
		char* pageFileName = page.PageFileName;
		char* string = (char*)malloc(FNTPageFileNameSize * sizeof(char));

		font.AdditionalResourceList[i] = string;

		Text::Copy(string, pageFileName, FNTPageFileNameSize);
	}

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FNT::ConvertFrom(Font& font)
{
	return BF::FileActionResult::Successful;
}

void BF::FNT::PrintData()
{
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Font (%s) : %s\n", &Info.CharSet[0], &Info.Name[0]);
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Size     : %4u | Smooth  : %3u |\n", Info.Size, Info.Smooth);
	printf(" | Bold     : %4s | AA      : %3u |\n", Info.Bold ? "Yes" : "No", Info.Supersampling);
	printf
	(
		" | Italic   : %4s | Padding : %u,%u,%u,%u |\n",
		Info.Italic ? "Yes" : "No",
		Info.CharacterPadding[0],
		Info.CharacterPadding[1],
		Info.CharacterPadding[2],
		Info.CharacterPadding[3]

	);
	printf(" | unicode  : %4s | Spacing : %u,%u |\n", Info.Unicode ? "Yes" : "No", Info.SpacerOffset[0], Info.SpacerOffset[1]);
	printf(" | stretchH : %4u | Outline : %3u |\n", Info.StretchH, Info.OutlineThickness);


	for (unsigned int pageIndex = 0; pageIndex < FontPageListSize; pageIndex++)
	{
		FNTPage& page = FontPageList[pageIndex];

		//printf(" |          |       |       |       |       |       |       |       |\n");
		printf("\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Page <%zu/%zu> %s\n", pageIndex + 1, FontPageListSize, page.PageFileName);
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Letter   | X-Pos | Y-Pos | Width | Height| X-Off | Y-Off | X-Step|\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");

		for (unsigned int characterIndex = 0; characterIndex < page.CharacteListSize; characterIndex++)
		{
			FNTCharacter& character = page.CharacteList[characterIndex];

			printf
			(
				" | %3i -> %c | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5c |\n",
				character.ID,
				character.ID,
				character.Position[0],
				character.Position[1],
				character.Size[0],
				character.Size[1],
				character.Offset[0],
				character.Offset[1],
				character.XAdvance
			);
		}

		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
	}
}