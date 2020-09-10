#include "TextFile.h"

TextFile::TextFile()
{

}

TextFile::TextFile(std::string path)
{
	StringSplitter splittedString = StringSplitter::Split(path, '/');

	FileName = splittedString.Lines[splittedString.NumberOfLines - 1];

	Path = path;
}
/*
void TextFile::SplitContentIntoLines()
{
	if (AmountOfLines == 0)
	{
		StringSplitter splittedString = StringSplitter::Split(Content, '\n');

		Lines = splittedString.Lines;
		AmountOfLines = splittedString.NumberOfLines;
	}
}*/