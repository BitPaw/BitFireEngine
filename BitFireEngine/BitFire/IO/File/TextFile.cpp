#include "TextFile.h"

BF::TextFile::TextFile()
{
}

BF::TextFile::TextFile(ASCIIString& path)
{
	Path.Copy(path);
	//FileName.Copy(lines[lines.Size() - 1]);

	GetFileExtension(path, FileExtension);
}

void BF::TextFile::GetFileExtension(ASCIIString& path, ASCIIString& extension)
{
	List<ASCIIString> lines;

	path.Splitt('/', lines);	

	if (lines.Size() > 0)
	{
		ASCIIString& fileName = lines[lines.Size() - 1];
		unsigned int position = fileName.FindLast('.');

		if (position != -1)
		{
			fileName.Cut(position + 1, extension);
		}
	}
}
