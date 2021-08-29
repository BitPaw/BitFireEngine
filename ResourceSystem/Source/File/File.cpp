#include "File.h"

#include "../Container/AsciiString.h"

BF::ResourceLoadingResult BF::File::CheckFile()
{
	if (!DoesFileExist(Path))
	{
		return ResourceLoadingResult::FileNotFound;
	}

	return ResourceLoadingResult::Successful;
}

BF::File::File(const char* filePath)
{
	_currentCursorPosition = 0;
	Data = nullptr;
	Size = 0;
	Extension = nullptr;

	if (filePath == nullptr)
	{
		return;
	}	

	strcpy(Path, filePath);

	AsciiString pp(Path);

	pp.MergeRepeatingCharacters('\\');
	pp.Replace('\\', '/');

	for (size_t i = 0; Path[i] != '\0'; i++)
	{
		if (Path[i] == '.')
		{
			Extension = &Path[i] +1;
			break;
		}
	}
}

BF::File::~File()
{
	Clear();
}


BF::ResourceLoadingResult BF::File::Read()
{
	const unsigned int elementSize = sizeof(char);
	unsigned int fullSize = -1;
	FILE* file = fopen(Path, "rb");

	if (file == nullptr)
	{
		return ResourceLoadingResult::FileNotFound;
	}

	fseek(file, 0, SEEK_END);
	Size = ftell(file);
	rewind(file);
	//fseek(file, 0, SEEK_SET);


	fullSize = Size * elementSize;
	Data = (char*)malloc(fullSize + 1);	

	if (!Data)
	{
		return ResourceLoadingResult::OutOfMemory;
	}

	Data[fullSize] = '\0';

	int readBytes = fread(Data, elementSize, Size, file);
	int overAllocatedBytes = Size - readBytes; // if overAllocatedBytes > 0 there was a reading error.	

	if (readBytes != Size)
	{
		memset(&Data[readBytes], 0, Size - readBytes);

		Size = readBytes;
	}

	int closeResult = fclose(file);

	return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::File::Read(const char* filePath, char** buffer)
{
	return Read(filePath, buffer, -1);
}

BF::ResourceLoadingResult BF::File::Read(const char* filePath, char** buffer, unsigned int maxSize)
{
	std::ifstream inputFileStream(filePath, std::ios::binary | std::ios::ate);
	unsigned int length = inputFileStream.tellg();

	if (length == -1)
	{
		return ResourceLoadingResult::FileNotFound;
	}

	if (length > maxSize && maxSize != -1)
	{
		return ResourceLoadingResult::OutOfMemory;
	}

	if ((*buffer) == nullptr)
	{
		(*buffer) = new char[length + 1];

		if ((*buffer) == 0)
		{
			return ResourceLoadingResult::OutOfMemory;
		}
	}

	inputFileStream.seekg(0, inputFileStream.beg);
	inputFileStream.read(*buffer, length);

	(*buffer)[length] = 0;

	return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::File::Write()
{
	std::ofstream fout;

	fout.open(&Path[0], std::ios::binary | std::ios::out);
	fout.write((char*)(&Path[0]), (std::streamsize)Size);

	fout.close();

	return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::File::Write(const char* filePath, const char* content)
{
	int length = 0;

	for (; content[length] != '\0'; length++);

	return Write(filePath, content, length);
}

BF::ResourceLoadingResult BF::File::Write(const char* filePath, const char* content, unsigned int length)
{
	FILE* file = fopen(filePath, "wb");

	unsigned int resultwrittenBytes = fwrite(content, sizeof(char), length, file);

	int resultCloseResult = fclose(file);

	return ResourceLoadingResult::Successful;
}

bool BF::File::ReadNextLineInto(char* exportBuffer)
{
	int length = 0;
	int index = _currentCursorPosition;
	int maxSize = Size;

	while (index < maxSize && Data[index] != '\n' && Data[index] != '\0')
	{
		index = _currentCursorPosition + length++;
	}

	if (length <= 1)
	{
		return false;
	}

	memcpy(exportBuffer, &Data[0] + _currentCursorPosition, length);
	exportBuffer[length-1] = '\0';

	_currentCursorPosition += length;

	while (Data[_currentCursorPosition] == '\n' && _currentCursorPosition < maxSize)
	{
		_currentCursorPosition++;
	}

	return true;
}

BF::ResourceLoadingResult BF::File::ReadAsLines(List<AsciiString>& lineList)
{
	if (Data == nullptr)
	{
		ResourceLoadingResult errorCode = Read();

		if (errorCode != ResourceLoadingResult::Successful)
		{
			return errorCode;
		}
	}

	AsciiString dataString; 
	unsigned int numberOfLines;
	unsigned int indexA = 0;
	unsigned int indexB = 0;
	unsigned int length = 0;

	dataString.Copy(Data, Size);

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

	return ResourceLoadingResult::Successful;
}

bool BF::File::DoesFileExist()
{
	std::ifstream file(&Path[0]);
	bool fileExists = file.good();

	file.close();

	return fileExists;
}

bool BF::File::DoesFileExist(const char* filePath)
{
	if (!filePath)
	{
		return false;
	}

    std::ifstream file(filePath);
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

	if (Data == nullptr)
	{
		return 0;
	}

	while (Data[lineCounter++] != '\0');

	return lineCounter;
}

void BF::File::CursorToBeginning()
{
	_currentCursorPosition = 0;
}

void BF::File::Remove()
{
	remove(Path);
}

void BF::File::Remove(const char* filePath)
{
	remove(filePath);
}

void BF::File::ReName(const char* name)
{
}

void BF::File::Clear()
{
	if (Data != nullptr)
	{
		free(Data);
	}

	Size = 0;
	Data = nullptr;
	Extension = nullptr;
}

void BF::File::ExtractAndSave(const char* filePath, unsigned int start, unsigned int length)
{
	const unsigned int sizeOfChar = sizeof(unsigned char);
	const char* startAdress = reinterpret_cast<char*>(&Data[0] + start);

	File::ExtractAndSave(filePath, (void*)startAdress, length);
}

void BF::File::ExtractAndSave(const char* filePath, void* data, unsigned int length)
{
	const char* startAdress = reinterpret_cast<char*>(data);

	std::fstream stream;

	stream.open(filePath, std::fstream::out); // std::fstream::app

	stream.write(startAdress, length);

	stream.close();
}
