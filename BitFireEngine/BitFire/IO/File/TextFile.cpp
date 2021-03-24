#include "TextFile.h"

BF::TextFile::TextFile()
{
}

BF::TextFile::TextFile(AsciiString& path)
{
	Path.Copy(path);
	//FileName.Copy(lines[lines.Size() - 1]);

	GetFileExtension(path, FileExtension);
}

void BF::TextFile::GetFileExtension(AsciiString& path, AsciiString& extension)
{
	List<AsciiString> lines;

	path.Splitt('/', lines);	

	if (lines.Size() > 0)
	{
		AsciiString& fileName = lines[lines.Size() - 1];
		unsigned int position = fileName.FindLast('.');

		if (position != -1)
		{
			fileName.Cut(position + 1, extension);
		}
	}
}
