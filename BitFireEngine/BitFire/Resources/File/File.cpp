#include "File.h"

BF::ErrorCode BF::File::CheckFile()
{
	if (Path.Empty())
	{
		return ErrorCode::EmptyFileName;
	}

	if (!DoesFileExist(Path))
	{
		return ErrorCode::FileNotFound;
	}

	return ErrorCode::NoError;
}

BF::File::File(AsciiString& filePath)
{
	Path.SetAsReference(filePath);

	GetFileExtension(filePath, Extension);
}

BF::ErrorCode BF::File::Read()
{
	ErrorCode errorCode = CheckFile();

	if (errorCode != ErrorCode::NoError)
	{
		return errorCode;
	}

	try
	{
		std::ifstream inputFileStream(&Path[0], std::ios::binary | std::ios::ate);
		unsigned int length = inputFileStream.tellg();

		Data.ReSize(length);

		inputFileStream.seekg(0, inputFileStream.beg);
		inputFileStream.read((char*)&Data[0], length);
	}
	catch (const std::exception&)
	{
		return ErrorCode::LoadingFailed;
	}

	return ErrorCode::NoError;
}

BF::ErrorCode BF::File::Write()
{
	std::ofstream fout;

	fout.open(&Path[0], std::ios::binary | std::ios::out);
	fout.write((char*)(&Path[0]), (std::streamsize)Data.Size());

	fout.close();

	return ErrorCode::NoError;
}

BF::ErrorCode BF::File::ReadAsLines(List<AsciiString>& lineList)
{
	if (Data.IsEmpty())
	{
		ErrorCode errorCode = Read();

		if (errorCode != ErrorCode::NoError)
		{
			return errorCode;
		}
	}

	AsciiString dataString; 
	unsigned int numberOfLines;
	unsigned int indexA = 0;
	unsigned int indexB = 0;
	unsigned int length = 0;

	dataString.Copy((char*)&Data[0], Data.Size());

	dataString.MergeRepeatingWhiteSpace();
	dataString.Remove('\r');
	dataString.MergeRepeatingCharacters('\n');	

	numberOfLines = dataString.Count('\n');
	
	lineList.ReSize(numberOfLines);

	for (size_t i = 0; i < numberOfLines; i++)
	{
		AsciiString& string = lineList[i];

		indexB = dataString.FindFirst('\n', indexA);

		length = indexB - indexA;

		string.Copy(&dataString[indexA], length);

		indexA = indexB+1;
	}

	return ErrorCode::NoError;
}

bool BF::File::DoesFileExist()
{
	std::ifstream file(&Path[0]);
	bool fileExists = file.good();

	file.close();

	return fileExists;
}

bool BF::File::DoesFileExist(AsciiString& filePath)
{
    std::ifstream file(&filePath[0]);
    bool fileExists = file.good();

    file.close();

    return fileExists;
}

void BF::File::GetFileExtension(AsciiString& path, AsciiString& extension)
{
    if (!path.Empty())
    {
        int position = path.FindLast('.');

        if (position != -1)
        {
			char* adress = &path[position + 1];
			unsigned int size = path.Size() - (position);
		
			extension.SetAsReference(adress, size);
        }
    }
}