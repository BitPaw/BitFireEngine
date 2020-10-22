#include "TextFile.h"

BF::TextFile::TextFile()
{
}

BF::TextFile::TextFile(std::string path)
{
	StringSplitter splittedString = StringSplitter::Split(path, '/');

	FileName = splittedString.Lines[splittedString.Lines.Size.Value - 1];

	Path = path;
}

std::string BF::TextFile::GetFileExtension()
{
	std::string result = "";

	if (!FileName.empty())
	{
		int position = FileName.find_last_of('.');

		if (position != -1)
		{
			result = FileName.substr(position +1);
		}
	}

	return result;
}
