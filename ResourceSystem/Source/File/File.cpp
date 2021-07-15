#include "File.h"

#include "../Container/AsciiString.h"

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

BF::File::File(char* filePath)
{
	Path.SetAsReference(filePath);

	_currentCursorPosition = 0;

	GetFileExtension(Path, Extension);
}

BF::File::File(AsciiString& filePath)
{
	Path.SetAsReference(filePath);

	_currentCursorPosition = 0;

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

BF::ErrorCode BF::File::Read(char* filePath, char** buffer)
{
	return Read(filePath, buffer, -1);
}

BF::ErrorCode BF::File::Read(char* filePath, char** buffer, unsigned int maxSize)
{
	std::ifstream inputFileStream(filePath, std::ios::binary | std::ios::ate);
	unsigned int length = inputFileStream.tellg();

	if (length == -1)
	{
		return ErrorCode::FileNotFound;
	}

	if (length > maxSize && maxSize != -1)
	{
		return ErrorCode::OutOfMemory;
	}

	if ((*buffer) == nullptr)
	{
		(*buffer) = new char[length + 1];

		if ((*buffer) == 0)
		{
			return ErrorCode::OutOfMemory;
		}
	}

	inputFileStream.seekg(0, inputFileStream.beg);
	inputFileStream.read(*buffer, length);

	(*buffer)[length] = 0;

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

BF::ErrorCode BF::File::Write(char* filePath, char* content)
{
	std::ofstream fout;
	int length = 0;

	for ( ; content[length] != '\0'; length++){}

	FILE* file = fopen(filePath, "w");

	fwrite(content, sizeof(char), length, file);

	fclose(file);

	return ErrorCode::NoError;
}

BF::ErrorCode BF::File::ReadNextLineInto(char* exportBuffer)
{
	int length = 0;
	int index = _currentCursorPosition;
	int maxSize = Data.Size();

	while (Data[index] != '\n' && index < maxSize)
	{
		index = _currentCursorPosition + length++;
	}


	if (length <= 1)
	{
		return ErrorCode::Empty;
	}

	memcpy(exportBuffer, &Data[0] + _currentCursorPosition, length);
	exportBuffer[length-1] = '\0';

	_currentCursorPosition += length;

	while (Data[_currentCursorPosition] == '\n' && _currentCursorPosition < maxSize)
	{
		_currentCursorPosition++;
	}


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

	numberOfLines = dataString.Count('\n') + 1;
	
	lineList.ReSize(numberOfLines);

	for (size_t i = 0; i < numberOfLines; i++)
	{
		AsciiString& string = lineList[i];

		indexB = dataString.FindFirst('\n', indexA);

		if (indexB == -1)
		{
			indexB = dataString.Size();
		}

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
			unsigned int size = path.Size() + 1 - (position);
		
			extension.SetAsReference(adress, size);
        }
    }
}

int BF::File::CountAmountOfLines()
{
	int lineCounter = 0;

	while (Data[lineCounter++] != '\0')
	{

	}

	return lineCounter;
}

void BF::File::CursorToBeginning()
{
	_currentCursorPosition = 0;
}

void BF::File::Remove()
{
	remove(&Path[0]);
}

void BF::File::Remove(AsciiString& filePath)
{
	remove(&filePath[0]);
}

void BF::File::ReName(AsciiString& name)
{
}

void BF::File::ExtractAndSave(AsciiString& filePath, unsigned int start, unsigned int length)
{
	const unsigned int sizeOfChar = sizeof(unsigned char);
	const char* startAdress = reinterpret_cast<char*>(&Data[0] + start);

	File::ExtractAndSave(filePath, (void*)startAdress, length);
}

void BF::File::ExtractAndSave(AsciiString& filePath, void* data, unsigned int length)
{
	const char* startAdress = reinterpret_cast<char*>(data);

	std::fstream stream;

	stream.open(&filePath[0], std::fstream::out); // std::fstream::app

	stream.write(startAdress, length);

	stream.close();
}
