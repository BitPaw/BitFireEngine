#include "TextFile.h"

#include "../../Utility/StringSplitter.h"

TextFile::TextFile() : TextFile("", "")
{

}

TextFile::TextFile(std::string path, std::string content)
{
	AmountOfLines = 0;
	Path = path;
	Content = content;
}

void TextFile::SplitContentIntoLines()
{
	if (AmountOfLines == 0)
	{
		StringSplitter splittedString = StringSplitter::Split(Content, '\n');

		Lines = splittedString.Lines;
		AmountOfLines = splittedString.NumberOfLines;
	}
}